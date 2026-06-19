#ifndef SOUND_PROCESSOR_WAVWRITE_H
#define SOUND_PROCESSOR_WAVWRITE_H

#include "waveform.h"

#include <string>

class WavWriter {
public:
    void write(const std::string& fileName, const Waveform& waveform) const;
};

#endif //SOUND_PROCESSOR_WAVWRITE_H