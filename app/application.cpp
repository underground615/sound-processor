#include "application.h"

#include "filters.h"
#include "WavRead.h"
#include "WavWrite.h"
#include "FilterProducer.h"

#include <iostream>

void Application::configure()
{
    converter_.addFilterProducer("ampl", FilterProducers::amplCreator);
    converter_.addFilterProducer("normalize", FilterProducers::normalizeCreator);
    converter_.addFilterProducer("silence", FilterProducers::silenceCreator);
    converter_.addFilterProducer("timestretch", FilterProducers::timestretchCreator);
    converter_.addFilterProducer("lowpass", FilterProducers::lowpassCreator);
    converter_.addFilterProducer("generator", FilterProducers::generatorCreator);
}

int Application::start(int argc, char* argv[])
{
    ArgsParser parser;
    ArgsParser::Result result = parser.parse(argc, argv);

    if (result == ArgsParser::Result::noArgs) {
        std::cout << "No arguments provided\nUse: sound_processor -i input.wav -o output.wav -f filter params...\n";
        return 0;
    }

    if (result == ArgsParser::Result::badArgs) {
        std::cerr << "Bad CLI arguments\n";
        return 1;
    }

    Waveform waveform;

    if (parser.getInFileName() != nullptr) {
        WavReader reader;
        waveform = reader.read(parser.getInFileName());
    }

    Pipeline pipeline = converter_.createPipeline(parser.getFilterDescriptors());

    Filter::State state = pipeline.apply(waveform);

    if (state != Filter::State::ok) {
        std::cerr << "Applying filters error\n";
        return 2;
    }

    if (parser.getOutFileName() != nullptr) {
        WavWriter writer;
        writer.write(parser.getOutFileName(), waveform);
    }

    return 0;
}