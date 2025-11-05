#pragma once

#include <map>
#include <vector>
#include <string>
#include <variant>
#include <cstdint>

#include <GenEnum.hpp>

class BencodeParser
{
public:
    struct BencodeItem
    {
        using BencodeInteger    = int64_t;
        using BencodeString     = std::string;
        using BencodeList       = std::vector<BencodeItem>;
        using BencodeDictionary = std::map<BencodeString, BencodeItem>;

        std::variant<BencodeInteger, BencodeString, BencodeList, BencodeDictionary> item;
    };

public:
    BencodeParser()  = default;
    ~BencodeParser() = default;

    void parse(const std::string& data);

    [[nodiscard]] const std::reference_wrapper<const BencodeItem> get() const noexcept;

private:
    void parse(std::string::const_iterator begin, std::string::const_iterator end);

    static BencodeItem parseInteger(std::string::const_iterator& currentPos, std::string::const_iterator& end,
        char integerEndIndicator = kBencodeEndIndicator);
    static BencodeItem parseString(std::string::const_iterator& currentPos, std::string::const_iterator& end);

    static BencodeItem::BencodeInteger parseIntegerImpl(std::string::const_iterator& currentPos, std::string::const_iterator& end,
        char integerEndIndicator = kBencodeEndIndicator);

    static constexpr auto kBencodeEndIndicator       = u8'e';
    static constexpr auto kBencodeSeparatorIndicator = u8':';

    static constexpr auto kBencodeIntegerBegin    = u8'i';
    static constexpr auto kBencodeIntegerMinus    = u8'-';
    static constexpr auto kBencodeListBegin       = u8'l';
    static constexpr auto kBencodeDictionaryBegin = u8'd';

    BencodeItem m_bencodeItems;
};
