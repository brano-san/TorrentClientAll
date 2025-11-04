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

    size_t size();
    void clear();

    [[nodiscard]] std::optional<const std::reference_wrapper<const BencodeItem>> get() const noexcept;

private:
    static bool isdigit(auto sym);

    static std::optional<BencodeItem> parse(const std::string& data, std::string::const_iterator& currentPos);

    static std::optional<BencodeItem> parseInteger(
        const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator = kBencodeEndIndicator);
    static std::optional<BencodeItem> parseString(
        const std::string& data, std::string::const_iterator& currentPos, size_t stringLength);
    static BencodeItem parseList(const std::string& data, std::string::const_iterator& currentPos);
    static BencodeItem parseDictionary(const std::string& data, std::string::const_iterator& currentPos);

    static std::optional<BencodeItem::BencodeInteger> parseIntegerImpl(
        const std::string& data, std::string::const_iterator& currentPos, char integerEndIndicator = kBencodeEndIndicator);

    static constexpr auto kBencodeEndIndicator = 'e';

    static constexpr auto kBencodeIntegerBegin    = 'i';
    static constexpr auto kBencodeIntegerMinus    = '-';
    static constexpr auto kBencodeListBegin       = 'l';
    static constexpr auto kBencodeDictionaryBegin = 'd';

    std::vector<BencodeItem> m_bencodeItems;
};
