#include "LowpassFilter.h"

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

LowpassFilter::LowpassFilter(int windowSize)
    : windowSize_(windowSize)
{
}

Filter::State LowpassFilter::apply(Waveform& waveform)
{
    if (windowSize_ < 1 || windowSize_ % 2 == 0) {
        return State::error;
    }

    std::size_t size = waveform.sampleCount();

    if (size == 0) {
        return State::ok;
    }

    std::vector<int16_t> oldSamples = waveform.samples();
    std::vector<int16_t> newSamples(size);

    int half = windowSize_ / 2;

    for (std::size_t i = 0; i < size; ++i) {
        double sum = 0.0;

        for (int j = -half; j <= half; ++j) {
            int index = static_cast<int>(i) + j;

            if (index < 0) {
                index = 0;
            }

            if (index >= static_cast<int>(size)) {
                index = static_cast<int>(size) - 1;
            }

            sum += oldSamples[index];
        }

        newSamples[i] = clampToInt16(sum / windowSize_);
    }

    waveform.samples() = newSamples;

    return State::ok;
}