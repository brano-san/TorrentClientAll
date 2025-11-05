#include "BencodeParser.hpp"

#include <stack>
#include <utility>

#include "Logger.hpp"

void BencodeParser::parse(const std::string& data)
{
    std::optional<BencodeItem::BencodeString> dictionaryKey;
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
        else if (std::holds_alternative<BencodeItem::BencodeDictionary>(lastState->item))
        {
            if (!dictionaryKey.has_value())
            {
                LOGE(Core, "Expected key for dictionary");
                throw std::runtime_error{"Expected key for dictionary"};
            }

            auto& object = std::get<BencodeParser::BencodeItem::BencodeDictionary>(lastState->item);
            const auto i = object.emplace(std::move(dictionaryKey.value()), std::move(item));
            dictionaryKey.reset();
            return &i.first->second;
        }
        LOGC(Core, "Something went very wrong");
        return {};
    };

    auto it = data.cbegin();
    while (it != data.cend())
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
                auto strOpt = parseString(data, it);
                if (strOpt.has_value())
                {
                    dictionaryKey = std::get<BencodeParser::BencodeItem::BencodeString>(strOpt.value().item);
                }
            }

            if ((*it) == kBencodeIntegerBegin)
            {
                auto intOpt = parseInteger(data, it);
                if (intOpt.has_value())
                {
                    insertItem(std::move(intOpt.value()));
                }
            }
            else if (std::isdigit(*it))  // detect string length
            {
                auto strOpt = parseString(data, it);
                if (strOpt.has_value())
                {
                    insertItem(std::move(strOpt.value()));
                }
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
                // Something went wrong here. Skip one pos to prevent endless cycle
                ++it;
            }
        }
    }
}

const std::reference_wrapper<const BencodeParser::BencodeItem> BencodeParser::get() const noexcept
{
    return std::cref(m_bencodeItems);
}

std::optional<BencodeParser::BencodeItem> BencodeParser::parseInteger(
    const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator)
{
    const auto integerOpt = parseIntegerImpl(data, currentPos, integerEndIndicator);
    if (!integerOpt.has_value())
    {
        LOGE(Core, "Something went wrong in parseIntegerImpl. Dropped");
        return std::nullopt;
    }
    return BencodeItem{BencodeItem::BencodeInteger{integerOpt.value()}};
}

std::optional<BencodeParser::BencodeItem> BencodeParser::parseString(
    const std::string& data, std::string::const_iterator& currentPos)
{
    const auto lengthOpt = parseIntegerImpl(data, currentPos, kBencodeSeparatorIndicator);
    if (!lengthOpt.has_value())
    {
        LOGE(Core, "Cannot get string size from data. Dropped");
        return std::nullopt;
    }

    const auto remainingSize = std::distance(currentPos, data.cend());
    if (remainingSize < 0)
    {
        LOGE(Core, "Cannot parse string. Dropped. Something went very wrong...");
        return std::nullopt;
    }
    if (std::cmp_less(remainingSize, lengthOpt.value()))
    {
        LOGE(Core, "Cannot parse string. Dropped. String length more than remaining size");
        return std::nullopt;
    }

    const auto strBegin = currentPos;
    std::advance(currentPos, lengthOpt.value());
    return BencodeItem{BencodeItem::BencodeString{std::string{strBegin, currentPos}}};
}

std::optional<BencodeParser::BencodeItem::BencodeInteger> BencodeParser::parseIntegerImpl(
    const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator)
{
    std::string integerString;
    for (; currentPos != data.cend(); ++currentPos)
    {
        const auto& symbol = (*currentPos);
        if (symbol == integerEndIndicator)
        {
            ++currentPos;
            break;
        }

        if (!isdigit(symbol) && symbol != kBencodeIntegerMinus)
        {
            continue;
        }

        integerString.push_back(symbol);
    }

    try
    {
        return std::stoll(integerString);
    }
    catch (const std::exception& ex)
    {
        LOGE(Core, "Something went wrong on parse integer. integerString[{1}]. Skipped. Exception message {0}", ex.what(),
            integerString);
    }
    return std::nullopt;
}
