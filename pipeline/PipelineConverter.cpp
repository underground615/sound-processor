#include "PipelineConverter.h"

#include <cstring>

void CmdLineArgs2PipelineConverter::addFilterProducer(
    const char* filterName,
    FilterProducer producer
)
{
    producers_[filterName] = producer;
}

Pipeline CmdLineArgs2PipelineConverter::createPipeline(
    const std::vector<ArgsParser::FilterDescriptor>& descriptors
) const
{
    Pipeline pipeline;

    for (std::size_t i = 0; i < descriptors.size(); ++i) {
        const ArgsParser::FilterDescriptor& descriptor = descriptors[i];

        FilterProducer producer =
            getFilterProducer(descriptor.name);

        if (producer == nullptr) {
            continue;
        }

        Filter* filter = producer(descriptor);

        if (filter != nullptr) {
            pipeline.addFilter(filter);
        }
    }

    return pipeline;
}

FilterProducer CmdLineArgs2PipelineConverter::getFilterProducer(
    const char* filterName
) const
{
    for (auto it = producers_.begin(); it != producers_.end(); ++it) {
        if (std::strcmp(it->first, filterName) == 0) {
            return it->second;
        }
    }

    return nullptr;
}