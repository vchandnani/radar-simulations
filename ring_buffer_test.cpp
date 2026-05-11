#include <gtest/gtest.h>
#include "ring_buffer.h"

class RingBufferTest : public ::testing::Test {
protected:
    RingBuffer<int> rb{3};
};

TEST_F(RingBufferTest, InitiallyEmpty) {
    EXPECT_TRUE(rb.empty());
    EXPECT_FALSE(rb.full());
}