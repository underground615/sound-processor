#ifndef SOUND_PROCESSOR_AMPLFILTER_H
#define SOUND_PROCESSOR_AMPLFILTER_H

#include "filter.h"

class AmplFilter : public Filter {
public:
    explicit AmplFilter(double factor);

    State apply(Waveform& waveform) override;

private:
    double factor_;
};

#endif //SOUND_PROCESSOR_AMPLFILTER_H