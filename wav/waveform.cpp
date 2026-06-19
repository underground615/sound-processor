#include "Waveform.h"

Waveform::Waveform()
{
}

Waveform::Waveform(std::vector<int16_t> samples)
    : samples_(samples)
{
}

std::vector<int16_t>& Waveform::samples()
{
    return samples_;
}

const std::vector<int16_t>& Waveform::samples() const
{
    return samples_;
}

int16_t& Waveform::operator[](std::size_t index)
{
    return samples_[index];
}

const int16_t& Waveform::operator[](std::size_t index) const
{
    return samples_[index];
}

std::size_t Waveform::sampleCount() const
{
    return samples_.size();
}

double Waveform::durationSeconds() const
{
    return static_cast<double>(samples_.size()) / SAMPLE_RATE;
}

std::size_t Waveform::secondsToSamples(double seconds) const
{
    return static_cast<std::size_t>(seconds * SAMPLE_RATE);
}

double Waveform::samplesToSeconds(std::size_t samples) const
{
    return static_cast<double>(samples) / SAMPLE_RATE;
}

void Waveform::resizeBySamples(std::size_t newSize)
{
    samples_.resize(newSize);
}
