#include "BencodeParser.hpp"

#include "Logger.hpp"

void BencodeParser::parse(const std::string& data)
{
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
        const auto& symbol = (*it);
        if (symbol == 'i')
        {
            parseInteger(data, it);
        }
        else if (std::isdigit(symbol) != 0)  // detect string length
        {
            parseString(data, it);
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

void BencodeParser::parseInteger(const std::string& data, std::string::const_iterator& currentPos)
{
    std::string integerString;
    for (auto it = currentPos; it != data.cend(); ++it)
    {
        const auto& symbol = (*it);
        if (symbol == 'e')
        {
            break;
        }

        if (std::isdigit(symbol) == 0 && symbol != '-')
        {
            continue;
        }

        integerString.push_back(symbol);
    }

    int64_t integer{};
    try
    {
        integer = std::stoll(integerString);
        m_bencodeItems.push_back(BencodeItem{BencodeItem::BencodeInteger{integer}});
    }
    catch (const std::exception& ex)
    {
        LOGE(Core, "Something went wrong on parse integer. integerString[{1}]. Skipped. Exception message {0}", ex.what(),
            integerString);
    }
}

void BencodeParser::parseString(const std::string& data, std::string::const_iterator& currentPos) {}

void BencodeParser::parseList(const std::string& data, std::string::const_iterator& currentPos) {}

void BencodeParser::parseDictionary(const std::string& data, std::string::const_iterator& currentPos) {}
