#include "BencodeParser.hpp"

#include <stack>
#include <utility>

#include "Logger.hpp"

void BencodeParser::parse(const std::string& data)
{
    try
    {
        parse(data.cbegin(), data.cend());
    }
    catch (const std::exception& ex)
    {
        LOGE(Core, "Got exception during parse: {}", ex.what());
    }
}

void BencodeParser::parse(std::string::const_iterator begin, std::string::const_iterator end)
{
    BencodeItem::BencodeString dictionaryKey;
    std::stack<BencodeItem*> state;

    const auto insertItem = [&](BencodeItem&& item) -> BencodeItem*
    {
        if (state.empty())
        {
            // Bencode have one <Root> object that contains all other objects
            m_bencodeItems = std::move(item);
            return &m_bencodeItems;
        }

        auto& lastState = state.top();
        if (std::holds_alternative<BencodeItem::BencodeList>(lastState->item))
        {
            auto& object = std::get<BencodeParser::BencodeItem::BencodeList>(lastState->item);
            object.push_back(std::move(item));
            return &object.back();
        }
        if (std::holds_alternative<BencodeItem::BencodeDictionary>(lastState->item))
        {
            auto& object = std::get<BencodeParser::BencodeItem::BencodeDictionary>(lastState->item);
            const auto i = object.emplace(std::move(dictionaryKey), std::move(item));
            return &i.first->second;
        }
        throw std::runtime_error{"Expected root object, list or dictionary"};
        return {};
    };

    auto it = begin;
    while (it != end)
    {
        if ((*it) == kBencodeEndIndicator)
        {
            ++it;
            state.pop();
        }
        else
        {
            if (!state.empty() && std::holds_alternative<BencodeItem::BencodeDictionary>(state.top()->item))
            {
                if (!std::isdigit(*it))
                {
                    throw std::runtime_error{"Expected string begin"};
                }
                dictionaryKey = std::get<BencodeParser::BencodeItem::BencodeString>(parseString(it, end).item);
                if (it == end)
                {
                    throw std::runtime_error{"Not expected end of data"};
                }
            }

            if ((*it) == kBencodeIntegerBegin)
            {
                insertItem(parseInteger(it, end));
            }
            else if (std::isdigit(*it))  // detect string length
            {
                insertItem(parseString(it, end));
            }
            else if ((*it) == kBencodeListBegin)
            {
                ++it;
                state.push(insertItem(BencodeItem{BencodeItem::BencodeList{}}));
            }
            else if ((*it) == kBencodeDictionaryBegin)
            {
                ++it;
                state.push(insertItem(BencodeItem{BencodeItem::BencodeDictionary{}}));
            }
            else
            {
                throw std::runtime_error{"Unexpected lexem"};
            }
        }
    }
}

const std::reference_wrapper<const BencodeParser::BencodeItem> BencodeParser::get() const noexcept
{
    return std::cref(m_bencodeItems);
}

BencodeParser::BencodeItem BencodeParser::parseInteger(
    std::string::const_iterator& currentPos, std::string::const_iterator& end, char integerEndIndicator)
{
    return BencodeItem{parseIntegerImpl(currentPos, end, integerEndIndicator)};
}

BencodeParser::BencodeItem BencodeParser::parseString(std::string::const_iterator& currentPos, std::string::const_iterator& end)
{
    const auto length = parseIntegerImpl(currentPos, end, kBencodeSeparatorIndicator);

    const auto remainingSize = std::distance(currentPos, end);
    if (remainingSize < 0)
    {
        LOGE(Core, "Cannot parse string. Dropped. Something went very wrong...");
        throw std::runtime_error{"Cannot parse. Incorrect size"};
    }
    if (std::cmp_less(remainingSize, length))
    {
        LOGE(Core, "Cannot parse string. Dropped. String length more than remaining size");
        throw std::runtime_error{"Cannot parse. Incorrect string length"};
    }

    const auto strBegin = currentPos;
    std::advance(currentPos, length);
    return BencodeItem{BencodeItem::BencodeString{std::string{strBegin, currentPos}}};
}

BencodeParser::BencodeItem::BencodeInteger BencodeParser::parseIntegerImpl(
    std::string::const_iterator& currentPos, std::string::const_iterator& end, char integerEndIndicator)
{
    std::string integerString;
    for (; currentPos != end; ++currentPos)
    {
        if ((*currentPos) == integerEndIndicator)
        {
            ++currentPos;
            break;
        }

        if (!std::isdigit(*currentPos) && (*currentPos) != kBencodeIntegerMinus)
        {
            continue;
        }

        integerString.push_back(*currentPos);
    }

    return std::stoll(integerString);
}
