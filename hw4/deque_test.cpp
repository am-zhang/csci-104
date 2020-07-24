#include "deque.h"
#include "gtest/gtest.h"

TEST(DequeTest, NominalPushBack) 
{
	Deque<int> d;
    d.push_back(0);
    d.push_back(1);
    d.push_back(2);
    EXPECT_EQ(0, d[0]);
    EXPECT_EQ(1, d[1]);
    EXPECT_EQ(2, d[2]);
    EXPECT_EQ(3, d.size());
    EXPECT_EQ(false, d.empty());
}

TEST(DequeTest, NominalPushFront) 
{
	Deque<int> d;
    d.push_front(2);
    d.push_front(1);
    d.push_front(0);
    EXPECT_EQ(0, d[0]);
    EXPECT_EQ(1, d[1]);
    EXPECT_EQ(2, d[2]);
    EXPECT_EQ(3, d.size());
    EXPECT_EQ(false, d.empty());
}

TEST(DequeTest, NominalPopBack)
{
	Deque<char> d;
    d.push_back('a');
    d.push_back('b');
    d.push_back('c');
    d.pop_back();
    EXPECT_EQ('a', d[0]);
    EXPECT_EQ('b', d[1]);
    EXPECT_EQ(2, d.size());
    EXPECT_EQ(false, d.empty());
}

TEST(DequeTest, NominalPopFront)
{
	Deque<char> d;
    d.push_front('c');
    d.push_front('b');
    d.push_front('a');
    d.pop_front();
    EXPECT_EQ('b', d[0]);
    EXPECT_EQ('c', d[1]);
    EXPECT_EQ(2, d.size());
}

TEST(DequeTest, OffNominalOperator)
{
	Deque<int> d;
    d.push_back(123);
    d.push_back(456);
    d.push_back(789);
    EXPECT_THROW(d[-1], std::range_error);
}

TEST(DequeTest, ExtendedNominal)
{
	Deque<double> d;
    d.push_back(2.5);
    d.push_back(3.5);
    d.push_back(4.5);
    d.push_back(5.5);
    d.push_back(6.5);
    d.push_back(7.5);
    d.push_back(8.5);
    d.push_back(9.5);
    d.push_front(1.5);
    d.push_front(0.5);
    EXPECT_EQ(0.5, d[0]);
    EXPECT_EQ(1.5, d[1]);
    EXPECT_EQ(2.5, d[2]);
    EXPECT_EQ(3.5, d[3]);
    EXPECT_EQ(4.5, d[4]);
    EXPECT_EQ(10, d.size());
}

TEST(DequeTest, NominalEmpty)
{
	Deque<double> d;
    d.push_back(2.5);
    d.push_back(3.5);
    d.push_back(4.5);
    d.push_front(1.5);
    d.push_front(0.5);
    d.pop_back();
    d.pop_front();
    d.pop_back();
    d.pop_front();
    d.pop_back();
    EXPECT_EQ(true, d.empty());
}

TEST(DequeTest, OffNominalPopFront) 
{
	Deque<int> d;
    d.push_back(0);
    d.push_back(1);
    d.push_back(2);
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    EXPECT_EQ(0, d.size());
}

TEST(DequeTest, OffNominalPopBack) 
{
	Deque<int> d;
    d.push_front(2);
    d.push_front(1);
    d.push_front(0);
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    EXPECT_EQ(0, d.size());
}