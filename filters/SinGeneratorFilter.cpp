#include "SinGeneratorFilter.h"

#include <cmath>
#include <cstdint>
#include <vector>

static constexpr double PI = 3.14159265358979323846;

static int16_t clampToInt16(double value)
{
    if (value > 32767.0) {
        return 32767;
    }

    if (value < -32768.0) {
        return -32768;
    }

    return static_cast<int16_t>(value);
}

SinGeneratorFilter::SinGeneratorFilter(double frequencyHz, double durationMs)
    : frequencyHz_(frequencyHz),
      durationMs_(durationMs)
{
}

Filter::State SinGeneratorFilter::apply(Waveform& waveform)
{
    if (frequencyHz_ < 0.0 || durationMs_ < 0.0) {
        return State::error;
    }

    double durationSeconds = durationMs_ / 1000.0;

    std::size_t sampleCount =
        waveform.secondsToSamples(durationSeconds);

    std::vector<int16_t> samples(sampleCount);

    for (std::size_t i = 0; i < sampleCount; ++i) {
        double t = static_cast<double>(i) / Waveform::SAMPLE_RATE;

        double value =
            32767.0 * std::sin(2.0 * PI * frequencyHz_ * t);

        samples[i] = clampToInt16(value);
    }

    waveform.samples() = samples;

    return State::ok;
}