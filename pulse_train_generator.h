#ifndef PULSE_TRAIN_GENERATOR_H
#define PULSE_TRAIN_GENERATOR_H

#include <vector>
#include <complex>
#include <cmath>

struct PulseParameters {
    double sample_rate;
    double pulse_width;
    double pulse_repetition_interval;
    double amplitude;
    int pulses;
};

class PulseTrainGenerator {
public:
    PulseTrainGenerator(PulseParameters params);
    std::vector<std::complex<double>> generate();

private:
    PulseParameters params_;
};

#include "pulse_train_generator.cpp"

#endif