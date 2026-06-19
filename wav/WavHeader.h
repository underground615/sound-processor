#ifndef SOUND_PROCESSOR_WAVHEADER_H
#define SOUND_PROCESSOR_WAVHEADER_H

#include <cstdint>

#pragma pack(push, 1)

struct RiffHeader {
    char riff[4];
    uint32_t size;
    char wave[4];
};

struct FmtHeader {
    char fmt[4];
    uint32_t chunkSize;
    uint16_t audioFormat;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

struct DataHeader {
    char data[4];
    uint32_t dataSize;
};

#pragma pack(pop)

#endif //SOUND_PROCESSOR_WAVHEADER_H