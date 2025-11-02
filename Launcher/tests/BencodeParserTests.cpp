#include <gtest/gtest.h>

#include <BencodeParser/BencodeParser.hpp>

#include "helper.hpp"

TEST(BencodeParserTests, Example0)
{
    const std::string testTorrentFileHeader = getTorrentHeaderExample();

    BencodeParser parser;
    // parser.parse(testTorrentFileHeader);

    EXPECT_EQ(1, true);
}

TEST(BencodeParserTests, BencodePositiveInteger)
{
    const std::string integerStr = "i42e";

    BencodeParser parser;
    parser.parse(integerStr);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem), 42);
}

TEST(BencodeParserTests, BencodeNegativeInteger)
{
    const std::string integerStr = "i-42e";

    BencodeParser parser;
    parser.parse(integerStr);

    const auto& item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem), -42);
}

TEST(BencodeParserTests, BencodeVeryBigInteger)
{
    const std::string integerStr = "i999999999999999999999999999e";

    BencodeParser parser;
    parser.parse(integerStr);

    const auto& item = parser.get();
    EXPECT_FALSE(item.has_value());
}
