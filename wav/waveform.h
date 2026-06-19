#ifndef SOUND_PROCESSOR_WAVEFORM_H
#define SOUND_PROCESSOR_WAVEFORM_H

#include <vector>
#include <cstdint>

class Waveform {
public:
    static constexpr int SAMPLE_RATE = 44100;
    static constexpr int BITS_PER_SAMPLE = 16;
    static constexpr int CHANNELS = 1;

    Waveform();
    explicit Waveform(std::vector<int16_t> samples);

    std::vector<int16_t>& samples();
    const std::vector<int16_t>& samples() const;

    int16_t& operator[](std::size_t index);
    const int16_t& operator[](std::size_t index) const;

    std::size_t sampleCount() const;
    double durationSeconds() const;

    std::size_t secondsToSamples(double seconds) const;
    double samplesToSeconds(std::size_t samples) const;

    void resizeBySamples(std::size_t newSize);

private:
    std::vector<int16_t> samples_;
};

#endif //SOUND_PROCESSOR_WAVEFORM_H