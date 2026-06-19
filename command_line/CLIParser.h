#ifndef SOUND_PROCESSOR_CLIPARSER_H
#define SOUND_PROCESSOR_CLIPARSER_H

#include <vector>

class ArgsParser {
public:
    enum class Result {
        ok,
        noArgs,
        badArgs
    };

    struct FilterDescriptor {
        const char* name;
        std::vector<const char*> params;
    };

    Result parse(int argc, char* argv[]);

    const char* getInFileName() const;
    const char* getOutFileName() const;

    const std::vector<FilterDescriptor>& getFilterDescriptors() const;

private:
    const char* inFileName_ = nullptr;
    const char* outFileName_ = nullptr;

    std::vector<FilterDescriptor> filterDescriptors_;
};

#endif //SOUND_PROCESSOR_CLIPARSER_H
