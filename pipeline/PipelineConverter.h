#ifndef SOUND_PROCESSOR_PIPELINECONVERTER_H
#define SOUND_PROCESSOR_PIPELINECONVERTER_H

#include "CLIParser.h"
#include "Pipeline.h"

#include <map>

using FilterProducer =
    Filter* (*)(const ArgsParser::FilterDescriptor&);

class CmdLineArgs2PipelineConverter {
public:
    void addFilterProducer(
        const char* filterName,
        FilterProducer producer
    );

    Pipeline createPipeline(
        const std::vector<ArgsParser::FilterDescriptor>& descriptors
    ) const;

private:
    FilterProducer getFilterProducer(const char* filterName) const;
    std::map<const char*, FilterProducer> producers_;
};

#endif //SOUND_PROCESSOR_PIPELINECONVERTER_H