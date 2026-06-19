#include "AmGeneratorFilter.h"

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

AmGeneratorFilter::AmGeneratorFilter(
    double amplitude,
    double carrierHz,
    double modulationHz,
    double depth,
    double durationMs
)
    : amplitude_(amplitude),
      carrierHz_(carrierHz),
      modulationHz_(modulationHz),
      depth_(depth),
      durationMs_(durationMs)
{
}

Filter::State AmGeneratorFilter::apply(Waveform& waveform)
{
    if (amplitude_ < 0.0 || amplitude_ > 1.0 ||
        carrierHz_ < 0.0 ||
        modulationHz_ < 0.0 ||
        depth_ < 0.0 || depth_ > 1.0 ||
        durationMs_ < 0.0) {
        return State::error;
        }

    double durationSeconds = durationMs_ / 1000.0;

    std::size_t sampleCount =
        waveform.secondsToSamples(durationSeconds);

    std::vector<int16_t> samples(sampleCount);

    for (std::size_t i = 0; i < sampleCount; ++i) {
        double t = static_cast<double>(i) / Waveform::SAMPLE_RATE;

        double envelope =
            1.0 + depth_ * std::sin(2.0 * PI * modulationHz_ * t);

        double carrier =
            std::sin(2.0 * PI * carrierHz_ * t);

        double value =
            amplitude_ * 32767.0 * envelope * carrier;

        samples[i] = clampToInt16(value);
    }

    waveform.samples() = samples;

    return State::ok;
}