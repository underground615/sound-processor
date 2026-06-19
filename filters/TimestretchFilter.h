#ifndef SOUND_PROCESSOR_TIMESTRETCHFILTER_H
#define SOUND_PROCESSOR_TIMESTRETCHFILTER_H

#include "filters.h"

class TimestretchFilter : public Filter {
public:
    explicit TimestretchFilter(double factor);

    State apply(Waveform& waveform) override;

private:
    double factor_;
};

#endif //SOUND_PROCESSOR_TIMESTRETCHFILTER_H