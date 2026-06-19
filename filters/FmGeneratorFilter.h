#ifndef SOUND_PROCESSOR_FMGENERATORFILTER_H
#define SOUND_PROCESSOR_FMGENERATORFILTER_H

#include "filter.h"

class FmGeneratorFilter : public Filter {
public:
    FmGeneratorFilter(
        double amplitude,
        double carrierHz,
        double modulationHz,
        double deviationHz,
        double durationMs
    );

    State apply(Waveform& waveform) override;

private:
    double amplitude_;
    double carrierHz_;
    double modulationHz_;
    double deviationHz_;
    double durationMs_;
};

#endif //SOUND_PROCESSOR_FMGENERATORFILTER_H