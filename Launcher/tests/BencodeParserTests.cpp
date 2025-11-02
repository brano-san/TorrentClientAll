#include <gtest/gtest.h>

#include <BencodeParser/BencodeParser.hpp>

#include "helper.hpp"

TEST(BencodeParserTests, Example0)
{
    const std::string testTorrentFileHeader = getTorrentHeaderExample();

    BencodeParser parser;
    parser.parse(testTorrentFileHeader);

    EXPECT_EQ(1, true);
}

TEST(BencodeParserTests, Example1)
{
    const std::string integerStr = "i42e";

    BencodeParser parser;
    parser.parse(integerStr);

    EXPECT_FALSE(1 == false);
}
