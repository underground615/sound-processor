#include "WavRead.h"
#include "WavHeader.h"

#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstdint>

static bool equals4(const char a[4], const char* b)
{
    return a[0] == b[0] &&
           a[1] == b[1] &&
           a[2] == b[2] &&
           a[3] == b[3];
}

Waveform WavReader::read(const std::string& fileName) const
{
    std::ifstream file(fileName, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Cannot open WAV file");
    }

    RiffHeader riff;
    FmtHeader fmt;
    DataHeader data;

    file.read(reinterpret_cast<char*>(&riff), sizeof(riff));
    if (!file) {
        throw std::runtime_error("Cannot read RIFF header");
    }

    file.read(reinterpret_cast<char*>(&fmt), sizeof(fmt));
    if (!file) {
        throw std::runtime_error("Cannot read fmt header");
    }

    file.read(reinterpret_cast<char*>(&data), sizeof(data));
    if (!file) {
        throw std::runtime_error("Cannot read data header");
    }

    if (!equals4(riff.riff, "RIFF") ||
        !equals4(riff.wave, "WAVE")) {
        throw std::runtime_error("Invalid RIFF/WAVE header");
    }

    if (!equals4(fmt.fmt, "fmt ")) {
        throw std::runtime_error("Invalid fmt chunk");
    }

    if (!equals4(data.data, "data")) {
        throw std::runtime_error("Invalid data chunk");
    }

    if (fmt.audioFormat != 1) {
        throw std::runtime_error("Unsupported WAV format: only PCM is allowed");
    }

    if (fmt.channels != Waveform::CHANNELS) {
        throw std::runtime_error("Unsupported WAV format: only mono is allowed");
    }

    if (fmt.sampleRate != Waveform::SAMPLE_RATE) {
        throw std::runtime_error("Unsupported WAV format: sample rate must be 44100");
    }

    if (fmt.bitsPerSample != Waveform::BITS_PER_SAMPLE) {
        throw std::runtime_error("Unsupported WAV format: only 16 bit samples are allowed");
    }

    if (fmt.blockAlign != Waveform::CHANNELS * Waveform::BITS_PER_SAMPLE / 8) {
        throw std::runtime_error("Invalid WAV block align");
    }

    if (fmt.byteRate != Waveform::SAMPLE_RATE * fmt.blockAlign) {
        throw std::runtime_error("Invalid WAV byte rate");
    }

    if (data.dataSize % sizeof(int16_t) != 0) {
        throw std::runtime_error("Invalid WAV data size");
    }

    if (riff.size != 36 + data.dataSize) {
        throw std::runtime_error("Invalid WAV file size");
    }

    std::vector<int16_t> samples(data.dataSize / sizeof(int16_t));

    file.read(
        reinterpret_cast<char*>(samples.data()),
        data.dataSize
    );

    if (!file) {
        throw std::runtime_error("Cannot read WAV samples");
    }

    return Waveform(samples);
}