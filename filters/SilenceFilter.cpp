#include "SilenceFilter.h"

#include <cstring>

SilenceFilter::SilenceFilter(const char* unit, double start, double end)
    : unit_(unit),
      start_(start),
      end_(end)
{
}

Filter::State SilenceFilter::apply(Waveform& waveform)
{
    double startSeconds = start_;
    double endSeconds = end_;

    if (std::strcmp(unit_, "ms") == 0) {
        startSeconds /= 1000.0;
        endSeconds /= 1000.0;
    }

    std::size_t startIndex = waveform.secondsToSamples(startSeconds);
    std::size_t endIndex = waveform.secondsToSamples(endSeconds);

    if (endIndex < startIndex) {
        return State::error;
    }

    std::size_t silenceSize = endIndex - startIndex + 1;

    if (startIndex > waveform.sampleCount()) {
        startIndex = waveform.sampleCount();
    }

    waveform.samples().insert(
        waveform.samples().begin() + startIndex,
        silenceSize,
        0
    );

    return State::ok;
}