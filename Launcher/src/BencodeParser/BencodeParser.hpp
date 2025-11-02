#pragma once

#include <vector>
#include <string>
#include <variant>
#include <cstdint>
#include <unordered_map>

#include <GenEnum.hpp>

class BencodedDictionary
{
    GENENUM(uint8_t, Fields, Announce, AnnounceList, Info, CreationDate, Comment, CreatedBy, Encoding);

public:
private:
};

class BencodeParser
{
    struct BencodeItem
    {
        using BencodeInteger    = int64_t;
        using BencodeString     = std::string;
        using BencodeList       = std::vector<BencodeItem>;
        using BencodeDictionary = std::unordered_map<BencodeItem, BencodeItem>;

        std::variant<BencodeInteger, BencodeString, BencodeList, BencodeDictionary> item;
    };

public:
    BencodeParser();
    ~BencodeParser();

    void parse(const std::string& data);

private:
};
