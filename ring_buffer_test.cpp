#include <gtest/gtest.h>
#include "ring_buffer.h"

class RingBufferTest : public ::testing::Test {
protected:
    RingBuffer<int> rb{3};
};

TEST_F(RingBufferTest, InitiallyEmpty) {
    EXPECT_TRUE(rb.empty());
    EXPECT_FALSE(rb.full());
    EXPECT_EQ(rb.size(), 0);
}

TEST_F(RingBufferTest, PushAndPop) {
    rb.push(1);
    rb.push(2);
    EXPECT_FALSE(rb.empty());
    EXPECT_EQ(rb.size(), 2);
    EXPECT_EQ(rb.pop(), 1);
    EXPECT_EQ(rb.pop(), 2);
    EXPECT_TRUE(rb.empty());
}

TEST_F(RingBufferTest, OverwriteOldest) {
    rb.push(1);
    rb.push(2);
    rb.push(3);
    rb.push(4);
    
    EXPECT_EQ(rb.size(), 3);
    EXPECT_EQ(rb.pop(), 2);
    EXPECT_EQ(rb.pop(), 3);
    EXPECT_EQ(rb.pop(), 4);
    EXPECT_TRUE(rb.empty());
}

TEST_F(RingBufferTest, WrapsAroundCorrectly) {
    rb.push(1);
    rb.push(2);
    rb.push(3);
    rb.pop();
    rb.push(4);
    
    EXPECT_EQ(rb.pop(), 2);
    EXPECT_EQ(rb.pop(), 3);
    EXPECT_EQ(rb.pop(), 4);
}