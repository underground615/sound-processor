#ifndef SOUND_PROCESSOR_FILTER_H
#define SOUND_PROCESSOR_FILTER_H

#include "waveform.h"

class Filter {
public:
    enum class State {
        ok,
        error
    };

    virtual ~Filter() = default;

    virtual State apply(Waveform& waveform) = 0;
};

#endif //SOUND_PROCESSOR_FILTER_H