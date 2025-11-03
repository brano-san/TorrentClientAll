#include <gtest/gtest.h>

#include <BencodeParser/BencodeParser.hpp>

#include "helper.hpp"

// TEST(BencodeParserTests, Example)
// {
//     const std::string testTorrentFileHeader = getTorrentHeaderExample();

//     BencodeParser parser;
//     // parser.parse(testTorrentFileHeader);

//     EXPECT_EQ(1, true);
// }

TEST(BencodeParserTests, EmptyBencodeList)
{
    const std::string bencodeString = "le";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 0);
}

TEST(BencodeParserTests, BencodeListWithALotOfStrings)
{
    const std::string bencodeString =
        "l5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:"
        "hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:"
        "hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:hello5:helloe";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 50);

    for (const auto& i : list)
    {
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(i.item));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(i.item), "hello");
    }
}

TEST(BencodeParserTests, BencodeListWithALotOfInteger)
{
    const std::string bencodeString =
        "li42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42"
        "ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42"
        "ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42ei42"
        "ee";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 90);

    for (const auto& i : list)
    {
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(i.item));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(i.item), 42);
    }
}

TEST(BencodeParserTests, BencodeListWithTwoInteger)
{
    const std::string bencodeString = "li42ei42ee";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 2);

    for (const auto& i : list)
    {
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(i.item));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(i.item), 42);
    }
}

TEST(BencodeParserTests, BencodeListWithStringAndInteger)
{
    const std::string bencodeString = "l5:helloi42ee";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 2);

    {
        const auto& a = list[1].item;
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(a));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(a), 42);
    }
    {
        const auto& a = list[0].item;
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(a));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(a), "hello");
    }
}

TEST(BencodeParserTests, BencodeListWithIntegerAndString)
{
    const std::string bencodeString = "li42e5:helloe";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 2);

    {
        const auto& a = list[0].item;
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(a));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(a), 42);
    }
    {
        const auto& a = list[1].item;
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(a));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(a), "hello");
    }
}

TEST(BencodeParserTests, BencodeListWithInteger)
{
    const std::string bencodeString = "li42ee";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeList>(bencodeItem));

    const auto list = std::get<BencodeParser::BencodeItem::BencodeList>(bencodeItem);
    EXPECT_EQ(list.size(), 1);

    for (const auto& i : list)
    {
        EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(i.item));
        EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(i.item), 42);
    }
}

TEST(BencodeParserTests, BencodeZeroStringAndInteger)
{
    const std::string bencodeString = "0:i42e";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 2);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem), 42);
}

TEST(BencodeParserTests, BencodeStringAndMegaBigInteger)
{
    const std::string bencodeString = "5:helloi999999999999999999999999999e";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "hello");
}

TEST(BencodeParserTests, BencodeStringAndNegativeInteger)
{
    const std::string bencodeString = "5:helloi-42e";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 2);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem), -42);
}

TEST(BencodeParserTests, BencodeStringAndPositiveInteger)
{
    const std::string bencodeString = "5:helloi42e";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 2);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeInteger>(bencodeItem), 42);
}

TEST(BencodeParserTests, MegaBigIntegerAndBencodeString)
{
    const std::string bencodeString = "i999999999999999999999999999e5:hello";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "hello");
}

TEST(BencodeParserTests, NegativeIntegerAndBencodeZeroString)
{
    const std::string bencodeString = "i-42e0:";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 2);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "");
}

TEST(BencodeParserTests, NegativeIntegerAndBencodeString)
{
    const std::string bencodeString = "i-42e5:hello";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 2);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "hello");
}

TEST(BencodeParserTests, PositiveIntegerAndBencodeString)
{
    const std::string bencodeString = "i42e5:hello";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 2);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "hello");
}

TEST(BencodeParserTests, BencodeLongString)
{
    const std::string bencodeString = "50:hellohellohellohellohellohellohellohellohellohello";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(
        std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "hellohellohellohellohellohellohellohellohellohello");
}

TEST(BencodeParserTests, BencodeStringHello)
{
    const std::string bencodeString = "5:hello";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "hello");
}

TEST(BencodeParserTests, BencodeZeroString)
{
    const std::string bencodeString = "0:";

    BencodeParser parser;
    parser.parse(bencodeString);
    EXPECT_EQ(parser.size(), 1);

    const auto item = parser.get();

    EXPECT_TRUE(item.has_value());

    const auto& bencodeItem = item.value().get().item;
    EXPECT_TRUE(std::holds_alternative<BencodeParser::BencodeItem::BencodeString>(bencodeItem));
    EXPECT_EQ(std::get<BencodeParser::BencodeItem::BencodeString>(bencodeItem), "");
}

TEST(BencodeParserTests, BencodePositiveInteger)
{
    const std::string integerStr = "i42e";

    BencodeParser parser;
    parser.parse(integerStr);
    EXPECT_EQ(parser.size(), 1);

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
    EXPECT_EQ(parser.size(), 1);

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
    EXPECT_EQ(parser.size(), 0);

    const auto& item = parser.get();
    EXPECT_FALSE(item.has_value());
}
