#ifndef SOUND_PROCESSOR_FILTERPRODUCER_H
#define SOUND_PROCESSOR_FILTERPRODUCER_H

#include "filters.h"
#include "CLIParser.h"

namespace FilterProducers {

    Filter* amplCreator(const ArgsParser::FilterDescriptor& fd);
    Filter* normalizeCreator(const ArgsParser::FilterDescriptor& fd);
    Filter* silenceCreator(const ArgsParser::FilterDescriptor& fd);
    Filter* timestretchCreator(const ArgsParser::FilterDescriptor& fd);
    Filter* lowpassCreator(const ArgsParser::FilterDescriptor& fd);
    Filter* generatorCreator(const ArgsParser::FilterDescriptor& fd);

}

#endif //SOUND_PROCESSOR_FILTERPRODUCER_H