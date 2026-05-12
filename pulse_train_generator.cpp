#include "pulse_train_generator.h"

PulseTrainGenerator::PulseTrainGenerator(PulseParameters params) : params_(params) {}

std::vector<std::complex<double>> PulseTrainGenerator::generate() {
    int samples_per_pulse = static_cast<int>(params_.pulse_width * params_.sample_rate);
    int samples_per_PRI = static_cast<int>(params_.pulse_repetition_interval * params_.sample_rate);
    int total_samples = samples_per_PRI * params_.pulses;
    std::vector<std::complex<double>> signal(total_samples, {0.0, 0.0});

    for (int p = 0; p < params_.pulses; ++p) {
        int pulse_start = p * samples_per_PRI;
        for (int i = 0; i < samples_per_pulse && (pulse_start + i) < total_samples; ++i) {
            // Simple Rectangular Pulse
            signal[pulse_start + i] = {params_.amplitude, 0.0};
        }
    }
    return signal;
}