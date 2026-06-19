#ifndef SOUND_PROCESSOR_LOWPASSFILTER_H
#define SOUND_PROCESSOR_LOWPASSFILTER_H

#include "filter.h"

class LowpassFilter : public Filter {
public:
    explicit LowpassFilter(int windowSize);

    State apply(Waveform& waveform) override;

private:
    int windowSize_;
};

#endif //SOUND_PROCESSOR_LOWPASSFILTER_H