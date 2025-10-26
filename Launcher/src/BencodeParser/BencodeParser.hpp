#pragma once

#include <GenEnum.hpp>

class BencodedDictionary
{
    GENENUM(uint8_t, Fields, Announce, AnnounceList, Info, CreationDate, Comment, CreatedBy, Encoding);

public:
private:
};

class BencodeParser
{
public:
    BencodeParser();
    ~BencodeParser();

    void parse();

private:
};
