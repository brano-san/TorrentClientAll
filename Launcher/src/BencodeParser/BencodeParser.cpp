#include "BencodeParser.hpp"

#include <utility>

#include "Logger.hpp"

void BencodeParser::parse(const std::string& data)
{
    for (auto it = data.cbegin(); it != data.cend();)
    {
        auto item = parse(data, it);
        if (!item.has_value())
        {
            continue;
        }
        m_bencodeItems.push_back(std::move(item.value()));
    }
}

std::optional<BencodeParser::BencodeItem> BencodeParser::parse(const std::string& data, std::string::const_iterator& currentPos)
{
    const char symbol = (*currentPos);
    if (symbol == kBencodeIntegerBegin)
    {
        return parseInteger(data, currentPos);
    }

    if (isdigit(symbol))  // detect string length
    {
        const auto stringSize = parseIntegerImpl(data, currentPos, ':');
        if (!stringSize.has_value())
        {
            LOGE(Core, "Cannot get string size from data. Dropped");
            return std::nullopt;
        }

        return parseString(data, currentPos, stringSize.value());
    }

    if (symbol == kBencodeListBegin)
    {
        ++currentPos;
        return parseList(data, currentPos);
    }

    if (symbol == kBencodeDictionaryBegin)
    {
        ++currentPos;
        return parseDictionary(data, currentPos);
    }

    // Something went wrong here. Skip one pos to prevent endless cycle
    ++currentPos;
    return std::nullopt;
}

size_t BencodeParser::size()
{
    return m_bencodeItems.size();
}

void BencodeParser::clear()
{
    m_bencodeItems.clear();
}

bool BencodeParser::isdigit(auto sym)
{
    return std::isdigit(sym) != 0;
}

std::optional<const std::reference_wrapper<const BencodeParser::BencodeItem>> BencodeParser::get() const noexcept
{
    if (m_bencodeItems.empty())
    {
        return std::nullopt;
    }
    return std::cref(m_bencodeItems.back());
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
    const std::string& data, std::string::const_iterator& currentPos, size_t stringLength)
{
    const auto remainingSize = std::distance(currentPos, data.cend());
    if (remainingSize < 0)
    {
        LOGE(Core, "Cannot parse string. Dropped. Something went very wrong...");
        return std::nullopt;
    }
    if (std::cmp_less(remainingSize, stringLength))
    {
        LOGE(Core, "Cannot parse string. Dropped. String length more than remaining size");
        return std::nullopt;
    }
    std::string bencodeString{currentPos, currentPos + static_cast<std::ptrdiff_t>(stringLength)};
    currentPos += static_cast<std::ptrdiff_t>(stringLength);
    return BencodeItem{BencodeItem::BencodeString{std::move(bencodeString)}};
}

BencodeParser::BencodeItem BencodeParser::parseList(const std::string& data, std::string::const_iterator& currentPos)
{
    auto list = BencodeParser::BencodeItem::BencodeList{};
    while (currentPos != data.cend())
    {
        if (*currentPos == kBencodeEndIndicator)
        {
            ++currentPos;
            break;
        }

        auto item = parse(data, currentPos);
        if (!item.has_value())
        {
            continue;
        }
        list.push_back(std::move(item.value()));
    }
    return BencodeParser::BencodeItem{list};
}

BencodeParser::BencodeItem BencodeParser::parseDictionary(const std::string& data, std::string::const_iterator& currentPos)
{
    auto dictionary = BencodeParser::BencodeItem::BencodeDictionary{};
    while (currentPos != data.cend())
    {
        if (*currentPos == kBencodeEndIndicator)
        {
            ++currentPos;
            break;
        }

        auto key = parse(data, currentPos);
        if (!key.has_value())
        {
            continue;
        }

        // Only strings as key in dictionary
        if (!std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(key.value().item))
        {
            continue;
        }
        auto& stringKey = std::get<BencodeParser::BencodeItem::BencodeString>(key.value().item);

        auto value = parse(data, currentPos);
        if (!value.has_value())
        {
            continue;
        }
        dictionary.insert_or_assign(std::move(stringKey), std::move(value.value()));
    }
    return BencodeParser::BencodeItem{dictionary};
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
