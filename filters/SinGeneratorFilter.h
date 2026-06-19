#ifndef SOUND_PROCESSOR_SINGENERATORFILTER_H
#define SOUND_PROCESSOR_SINGENERATORFILTER_H

#include "filter.h"

class SinGeneratorFilter : public Filter {
public:
    SinGeneratorFilter(double frequencyHz,
                       double durationMs);

    State apply(Waveform& waveform) override;

private:
    double frequencyHz_;
    double durationMs_;
};

#endif //SOUND_PROCESSOR_SINGENERATORFILTER_H