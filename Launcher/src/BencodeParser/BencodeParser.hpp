#pragma once

#include <vector>
#include <string>
#include <variant>
#include <cstdint>
#include <optional>
#include <unordered_map>

#include <GenEnum.hpp>

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

    [[nodiscard]] const std::reference_wrapper<const BencodeItem> get() const noexcept;

private:
    static std::optional<BencodeItem> parseInteger(
        const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator = kBencodeEndIndicator);
    static std::optional<BencodeItem> parseString(const std::string& data, std::string::const_iterator& currentPos);

    static std::optional<BencodeItem::BencodeInteger> parseIntegerImpl(
        const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator = kBencodeEndIndicator);

    static constexpr auto kBencodeEndIndicator       = u8'e';
    static constexpr auto kBencodeSeparatorIndicator = u8':';

    static constexpr auto kBencodeIntegerBegin    = u8'i';
    static constexpr auto kBencodeIntegerMinus    = u8'-';
    static constexpr auto kBencodeListBegin       = u8'l';
    static constexpr auto kBencodeDictionaryBegin = u8'd';

    BencodeItem m_bencodeItems;
};
