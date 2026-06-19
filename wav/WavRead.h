#ifndef SOUND_PROCESSOR_WAVREAD_H
#define SOUND_PROCESSOR_WAVREAD_H

#include "waveform.h"
#include <string>

class WavReader {
public:
    Waveform read(const std::string& fileName) const;
};

#endif //SOUND_PROCESSOR_WAVREAD_H