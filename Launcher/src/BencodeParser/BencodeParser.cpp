#include "BencodeParser.hpp"

#include "Logger.hpp"

void BencodeParser::parse(const std::string& data)
{
    for (auto it = data.cbegin(); it != data.cend();)
    {
        const char symbol = (*it);
        if (symbol == 'i')
        {
            parseInteger(data, it);
        }
        else if (std::isdigit(symbol) != 0)  // detect string length
        {
            const auto stringSize = parseIntegerImpl(data, it, ':');
            if (!stringSize.has_value())
            {
                LOGE(Core, "Cannot get string size from data. Dropped");
                continue;
            }

            parseString(data, it, stringSize.value());
        }
        else if (symbol == 'l')
        {
            parseList(data, it);
        }
        else if (symbol == 'd')
        {
            parseDictionary(data, it);
        }
    }
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

void BencodeParser::parseInteger(const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator)
{
    const auto integerOpt = parseIntegerImpl(data, currentPos, integerEndIndicator);
    if (!integerOpt.has_value())
    {
        LOGE(Core, "Something went wrong in parseIntegerImpl. Dropped");
        return;
    }
    m_bencodeItems.push_back(BencodeItem{BencodeItem::BencodeInteger{integerOpt.value()}});
}

void BencodeParser::parseString(const std::string& data, std::string::const_iterator& currentPos, size_t stringLength)
{
    std::string bencodeString;
    bencodeString.reserve(stringLength);
    for (size_t i = 0; i < stringLength && currentPos != data.end(); ++i, ++currentPos)
    {
        bencodeString.push_back(*currentPos);
    }
    m_bencodeItems.push_back(BencodeItem{BencodeItem::BencodeString{std::move(bencodeString)}});
}

void BencodeParser::parseList(const std::string& data, std::string::const_iterator& currentPos) {}

void BencodeParser::parseDictionary(const std::string& data, std::string::const_iterator& currentPos) {}

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
        return std::nullopt;
    }
}
