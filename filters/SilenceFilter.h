#ifndef SOUND_PROCESSOR_SILENCEFILTER_H
#define SOUND_PROCESSOR_SILENCEFILTER_H

#include "filter.h"

class SilenceFilter : public Filter {
public:
    SilenceFilter(const char* unit, double start, double end);

    State apply(Waveform& waveform) override;

private:
    const char* unit_;
    double start_;
    double end_;
};

#endif //SOUND_PROCESSOR_SILENCEFILTER_H