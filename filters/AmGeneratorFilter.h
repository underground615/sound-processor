#ifndef SOUND_PROCESSOR_AMGENERATORFILTER_H
#define SOUND_PROCESSOR_AMGENERATORFILTER_H

#include "filter.h"

class AmGeneratorFilter : public Filter {
public:
    AmGeneratorFilter(
        double amplitude,
        double carrierHz,
        double modulationHz,
        double depth,
        double durationMs
    );

    State apply(Waveform& waveform) override;

private:
    double amplitude_;
    double carrierHz_;
    double modulationHz_;
    double depth_;
    double durationMs_;
};

#endif //SOUND_PROCESSOR_AMGENERATORFILTER_H