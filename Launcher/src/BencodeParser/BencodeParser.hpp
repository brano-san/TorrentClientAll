#pragma once

#include <vector>
#include <string>
#include <variant>
#include <cstdint>
#include <optional>
#include <unordered_map>

#include <GenEnum.hpp>

// class BencodedDictionary
// {
//     GENENUM(uint8_t, Fields, Announce, AnnounceList, Info, CreationDate, Comment, CreatedBy, Encoding);
// };

class BencodeParser
{
public:
    struct BencodeItem
    {
        using BencodeInteger    = int64_t;
        using BencodeString     = std::string;
        using BencodeList       = std::vector<BencodeItem>;
        using BencodeDictionary = std::unordered_map<BencodeString, BencodeItem>;

        std::variant<BencodeInteger, BencodeString, BencodeList, BencodeDictionary> item;
    };

public:
    BencodeParser()  = default;
    ~BencodeParser() = default;

    void parse(const std::string& data);

    size_t size();
    void clear();

    [[nodiscard]] std::optional<const std::reference_wrapper<const BencodeItem>> get() const noexcept;

private:
    void parseInteger(const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator = 'e');
    void parseString(const std::string& data, std::string::const_iterator& currentPos, size_t stringLength);
    void parseList(const std::string& data, std::string::const_iterator& currentPos);
    void parseDictionary(const std::string& data, std::string::const_iterator& currentPos);

    static std::optional<BencodeItem::BencodeInteger> parseIntegerImpl(
        const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator = 'e');

    std::vector<BencodeItem> m_bencodeItems;
};
