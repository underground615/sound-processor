#ifndef SOUND_PROCESSOR_NORMALIZEFILTER_H
#define SOUND_PROCESSOR_NORMALIZEFILTER_H

#include "filter.h"

class NormalizeFilter : public Filter {
public:
    explicit NormalizeFilter(double peak = 1.0);

    State apply(Waveform& waveform) override;

private:
    double peak_;
};

#endif //SOUND_PROCESSOR_NORMALIZEFILTER_H