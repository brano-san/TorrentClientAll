#include "BencodeParser.hpp"

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
    if (symbol == 'i')
    {
        return parseInteger(data, currentPos);
    }

    if (std::isdigit(symbol) != 0)  // detect string length
    {
        const auto stringSize = parseIntegerImpl(data, currentPos, ':');
        if (!stringSize.has_value())
        {
            LOGE(Core, "Cannot get string size from data. Dropped");
            return std::nullopt;
        }

        return parseString(data, currentPos, stringSize.value());
    }

    if (symbol == 'l')
    {
        ++currentPos;
        return parseList(data, currentPos);
    }

    if (symbol == 'd')
    {
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
    std::string bencodeString;
    bencodeString.reserve(stringLength);
    for (size_t i = 0; i < stringLength && currentPos != data.end(); ++i, ++currentPos)
    {
        bencodeString.push_back(*currentPos);
    }
    return BencodeItem{BencodeItem::BencodeString{std::move(bencodeString)}};
}

BencodeParser::BencodeItem BencodeParser::parseList(const std::string& data, std::string::const_iterator& currentPos)
{
    auto list = BencodeParser::BencodeItem::BencodeList{};
    while (currentPos != data.cend())
    {
        if (*currentPos == 'e')
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
    for (auto it = data.cbegin(); it != data.cend();)
    {
        auto item = parse(data, it);
        if (!item.has_value())
        {
            continue;
        }
        // dictionary.push_back(std::move(item.value()));
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

        if (std::isdigit(symbol) == 0 && symbol != '-')
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
