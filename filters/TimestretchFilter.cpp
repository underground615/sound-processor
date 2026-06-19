#include "TimestretchFilter.h"

#include <cmath>
#include <cstdint>
#include <vector>

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

TimestretchFilter::TimestretchFilter(double factor)
    : factor_(factor)
{
}

Filter::State TimestretchFilter::apply(Waveform& waveform)
{
    if (factor_ <= 0.0) {
        return State::error;
    }

    std::size_t oldSize = waveform.sampleCount();

    if (oldSize == 0) {
        return State::ok;
    }

    std::size_t newSize =
        static_cast<std::size_t>(std::round(oldSize * factor_));

    std::vector<int16_t> oldSamples = waveform.samples();
    std::vector<int16_t> newSamples(newSize);

    for (std::size_t i = 0; i < newSize; ++i) {
        double pos = static_cast<double>(i) / factor_;

        std::size_t left = static_cast<std::size_t>(pos);
        double frac = pos - left;

        if (left >= oldSize - 1) {
            newSamples[i] = oldSamples[oldSize - 1];
        } else {
            double value =
                oldSamples[left] * (1.0 - frac) +
                oldSamples[left + 1] * frac;

            newSamples[i] = clampToInt16(value);
        }
    }

    waveform.samples() = newSamples;

    return State::ok;
}