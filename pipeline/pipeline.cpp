#include "Pipeline.h"

Pipeline::~Pipeline()
{
    clear();
}

Pipeline::Pipeline(Pipeline&& other) noexcept
    : filters_(other.filters_)
{
    other.filters_.clear();
}

Pipeline& Pipeline::operator=(Pipeline&& other) noexcept
{
    if (this != &other) {
        clear();

        filters_ = other.filters_;
        other.filters_.clear();
    }

    return *this;
}

Filter::State Pipeline::apply(Waveform& waveform)
{
    for (std::size_t i = 0; i < filters_.size(); ++i) {
        Filter::State state = filters_[i]->apply(waveform);

        if (state != Filter::State::ok) {
            return state;
        }
    }

    return Filter::State::ok;
}

Filter* Pipeline::addFilter(Filter* filter)
{
    filters_.push_back(filter);
    return filter;
}

std::size_t Pipeline::getFilterNumber() const
{
    return filters_.size();
}

Filter* Pipeline::operator[](std::size_t index) const
{
    return filters_[index];
}

void Pipeline::clear()
{
    for (std::size_t i = 0; i < filters_.size(); ++i) {
        delete filters_[i];
    }

    filters_.clear();
}