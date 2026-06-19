#ifndef SOUND_PROCESSOR_PIPELINE_H
#define SOUND_PROCESSOR_PIPELINE_H

#include "filters.h"

#include <vector>
#include <cstddef>

class Pipeline {
public:
    Pipeline() = default;
    ~Pipeline();

    Pipeline(const Pipeline& other) = delete;
    Pipeline& operator=(const Pipeline& other) = delete;

    Pipeline(Pipeline&& other) noexcept;
    Pipeline& operator=(Pipeline&& other) noexcept;

    Filter::State apply(Waveform& waveform);

    Filter* addFilter(Filter* filter);

    std::size_t getFilterNumber() const;
    Filter* operator[](std::size_t index) const;

private:
    void clear();
    std::vector<Filter*> filters_;
};

#endif //SOUND_PROCESSOR_PIPELINE_H