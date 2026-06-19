#include "NormalizeFilter.h"

#include <cstdint>

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

NormalizeFilter::NormalizeFilter(double peak)
    : peak_(peak)
{
}

Filter::State NormalizeFilter::apply(Waveform& waveform)
{
    if (waveform.sampleCount() == 0) {
        return State::ok;
    }

    int currentPeak = 0;

    for (std::size_t i = 0; i < waveform.sampleCount(); ++i) {
        int value = waveform[i];

        if (value < 0) {
            value = -value;
        }

        if (value > currentPeak) {
            currentPeak = value;
        }
    }

    if (currentPeak == 0) {
        return State::ok;
    }

    double scale = peak_ * 32767.0 / currentPeak;

    for (std::size_t i = 0; i < waveform.sampleCount(); ++i) {
        waveform[i] = clampToInt16(waveform[i] * scale);
    }

    return State::ok;
}