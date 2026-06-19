#include "AmplFilter.h"

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

AmplFilter::AmplFilter(double factor)
    : factor_(factor)
{
}

Filter::State AmplFilter::apply(Waveform& waveform)
{
    for (std::size_t i = 0; i < waveform.sampleCount(); ++i) {
        waveform[i] = clampToInt16(waveform[i] * factor_);
    }

    return State::ok;
}