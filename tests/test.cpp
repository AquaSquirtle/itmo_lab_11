#include "gtest/gtest.h"
#include "lib/Indexer/Indexer.hpp"
#include "lib/Searcher/Searcher.hpp"

TEST(SearcherTest, BaseTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1");
    Searcher searcher;
    auto k = searcher.GetFiles("cats AND dogs OR asd");
    EXPECT_EQ(k[0].first, "C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1\\t1.txt");
    EXPECT_EQ(k[1].first, "C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1\\t2.txt");
    EXPECT_EQ(k[2].first, "C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1\\t5.txt");
}

TEST(SearcherTest, BracketsTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1");
    Searcher searcher;
    auto k = searcher.GetFiles("cats AND (dogs OR asd)");
    EXPECT_EQ(k[0].first, "C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1\\t1.txt");
    EXPECT_EQ(k[1].first, "C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1\\t5.txt");
}


TEST(SearcherTest, SingleWordQueryTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test2");
    Searcher searcher;
    auto k = searcher.GetFiles("Cats");
    EXPECT_EQ(k.size(), 4);
}


TEST(SearcherTest, ComplexQueryTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test1");
    Searcher searcher;
    auto k = searcher.GetFiles("(cats AND dogs) OR (asd AND qwerty)");
    EXPECT_EQ(k.size(), 1);
}


TEST(SearcherTest, ComplexQueryWithMultipleOperatorsTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test3");
    Searcher searcher;
    auto k = searcher.GetFiles("(Elephants OR Lions) AND (Tigers AND Bears) OR (Cats AND Dogs)");
    EXPECT_EQ(k.size(), 3);
}

TEST(SearcherTest, ComplexQueryWithNestedParenthesesTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test3");
    Searcher searcher;
    auto k = searcher.GetFiles("((Elephants OR Lions) AND (Tigers OR Bears)) OR (Cats AND Dogs)");
    EXPECT_EQ(k.size(), 4);
}

TEST(SearcherTest, ComplexQueryWithMultipleWordsTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test3");
    Searcher searcher;
    auto k = searcher.GetFiles("(Elephants AND Lions) OR (Tigers AND Bears) OR (Cats AND Dogs)");
    EXPECT_EQ(k.size(), 3);
}

TEST(SearcherTest, ComplexQueryWithMultipleOccurrencesTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test3");
    Searcher searcher;
    auto k = searcher.GetFiles("(Elephants AND Lions) OR (Tigers AND Bears) OR (Lions AND Tigers)");
    EXPECT_EQ(k.size(), 0);
}

TEST(SearcherTest, ComplexQueryWithPartialMatchesTest) {
    Indexer indexer;
    indexer.Parse("C:\\Users\\krasn\\Desktop\\OP\\lab_11\\labwork11-squirtleKKS\\tests\\test_files\\test3");
    Searcher searcher;
    auto k = searcher.GetFiles("(Elephants OR Lions) AND (Tigers OR Bears) AND (Cats AND Dogs)");
    EXPECT_EQ(k.size(), 1);
}
