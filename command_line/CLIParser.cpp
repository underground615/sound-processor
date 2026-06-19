#include "CLIParser.h"

#include <string>

ArgsParser::Result ArgsParser::parse(const int argc, char* argv[])
{
    if (argc == 1) {
        return Result::noArgs;
    }

    int i = 1;

    while (i < argc) {
        if (std::string(argv[i]) == "-i") {
            if (i + 1 >= argc) {
                return Result::badArgs;
            }
            inFileName_ = argv[i + 1];
            i += 2;
        }
        else if (std::string(argv[i]) == "-o") {
            if (i + 1 >= argc) {
                return Result::badArgs;
            }
            outFileName_ = argv[i + 1];
            i += 2;
        }
        else if (std::string(argv[i]) == "-f") {
            if (i + 1 >= argc) {
                return Result::badArgs;
            }
            FilterDescriptor descriptor;
            descriptor.name = argv[i + 1];
            i += 2;

            while (i < argc && std::string(argv[i]) != "-f") {
                descriptor.params.push_back(argv[i]);
                ++i;
            }

            filterDescriptors_.push_back(descriptor);
        }
        else {
            return Result::badArgs;
        }
    }

    return Result::ok;
}

const char* ArgsParser::getInFileName() const
{
    return inFileName_;
}

const char* ArgsParser::getOutFileName() const
{
    return outFileName_;
}

const std::vector<ArgsParser::FilterDescriptor>&
ArgsParser::getFilterDescriptors() const
{
    return filterDescriptors_;
}
