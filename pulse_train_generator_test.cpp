#include <gtest/gtest.h>
#include "pulse_train_generator.h"

TEST(PulseTrainGeneratorTest, GeneratesCorrectPulseCount) {
    // 1MHz SR, 1us PW, 10us PRI, amplitude 1.0, 5 pulses
    PulseParameters params{1e6, 1e-6, 10e-6, 1.0, 5};
    PulseTrainGenerator gen(params);
    auto signal = gen.generate();

    // 5 pulses * 10us * 1MHz = 50 samples
    EXPECT_EQ(signal.size(), 50);
    EXPECT_EQ(signal[0].real(), 1.0);
}

TEST(PulseTrainGeneratorTest, HandlesSilence) {
    PulseParameters params{1e6, 1e-6, 10e-6, 1.0, 1}; 
    PulseTrainGenerator gen(params);
    auto signal = gen.generate();

    // After 1us (1 sample), next samples should be 0
    EXPECT_EQ(signal[1].real(), 0.0);
}