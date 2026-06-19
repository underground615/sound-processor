#include "FilterProducer.h"

#include <cstring>
#include <string>
#include <stdexcept>

static double parseDouble(const char* text)
{
    std::string s(text);
    std::size_t pos = 0;
    double value = std::stod(s, &pos);

    if (pos != s.size()) {
        throw std::invalid_argument("bad double");
    }

    return value;
}

static int parseInt(const char* text)
{
    std::string s(text);
    std::size_t pos = 0;
    int value = std::stoi(s, &pos);

    if (pos != s.size()) {
        throw std::invalid_argument("bad int");
    }

    return value;
}

namespace FilterProducers {

    Filter* amplCreator(const ArgsParser::FilterDescriptor& fd)
    {
        if (std::strcmp(fd.name, "ampl") != 0)
            throw std::logic_error("Wrong fd for ampl filter producer.");

        if (fd.params.size() != 1)
            throw std::logic_error("Wrong params number for ampl filter producer.");

        try {
            double factor = parseDouble(fd.params[0]);

            Filter* amplFilter = new AmplFilter(factor);
            return amplFilter;
        }
        catch (std::invalid_argument&) {
            throw std::logic_error("Error converting the 1st argument of ampl filter.");
        }
        catch (std::out_of_range&) {
            throw std::logic_error("Error converting the 1st argument of ampl filter.");
        }
        catch (std::invalid_argument&) {
            throw std::logic_error("Error converting the 1st argument of ampl filter.");
        }
        catch (std::out_of_range&) {
            throw std::logic_error("Error converting the 1st argument of ampl filter.");
        }
    }

Filter* normalizeCreator(const ArgsParser::FilterDescriptor& fd)
{
    if (fd.params.size() == 0) {
        return new NormalizeFilter();
    }

    if (fd.params.size() != 1) {
        return nullptr;
    }

    double peak = parseDouble(fd.params[0]);
    return new NormalizeFilter(peak);
}

Filter* silenceCreator(const ArgsParser::FilterDescriptor& fd)
{
    if (fd.params.size() != 3) {
        return nullptr;
    }

    const char* unit = fd.params[0];
    double start = parseDouble(fd.params[1]);
    double end = parseDouble(fd.params[2]);

    return new SilenceFilter(unit, start, end);
}

Filter* timestretchCreator(const ArgsParser::FilterDescriptor& fd)
{
    if (fd.params.size() != 1) {
        return nullptr;
    }

    double factor = parseDouble(fd.params[0]);
    return new TimestretchFilter(factor);
}

Filter* lowpassCreator(const ArgsParser::FilterDescriptor& fd)
{
    if (fd.params.size() != 1) {
        return nullptr;
    }

    int windowSize = parseInt(fd.params[0]);
    return new LowpassFilter(windowSize);
}

Filter* generatorCreator(const ArgsParser::FilterDescriptor& fd)
{
    if (fd.params.size() < 1) {
        return nullptr;
    }

    const char* type = fd.params[0];

    if (std::strcmp(type, "sin") == 0) {
        if (fd.params.size() != 3) {
            return nullptr;
        }

        double frequencyHz = parseDouble(fd.params[1]);
        double durationMs = parseDouble(fd.params[2]);

        return new SinGeneratorFilter(frequencyHz, durationMs);
    }

    if (std::strcmp(type, "am") == 0) {
        if (fd.params.size() != 6) {
            return nullptr;
        }

        double amplitude = parseDouble(fd.params[1]);
        double carrierHz = parseDouble(fd.params[2]);
        double modulationHz = parseDouble(fd.params[3]);
        double depth = parseDouble(fd.params[4]);
        double durationMs = parseDouble(fd.params[5]);

        return new AmGeneratorFilter(
            amplitude,
            carrierHz,
            modulationHz,
            depth,
            durationMs
        );
    }

    if (std::strcmp(type, "fm") == 0) {
        if (fd.params.size() != 6) {
            return nullptr;
        }

        double amplitude = parseDouble(fd.params[1]);
        double carrierHz = parseDouble(fd.params[2]);
        double modulationHz = parseDouble(fd.params[3]);
        double deviationHz = parseDouble(fd.params[4]);
        double durationMs = parseDouble(fd.params[5]);

        return new FmGeneratorFilter(
            amplitude,
            carrierHz,
            modulationHz,
            deviationHz,
            durationMs
        );
    }

    return nullptr;
}

}