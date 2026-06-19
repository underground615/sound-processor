#include "WavWrite.h"
#include "WavHeader.h"

#include <fstream>
#include <stdexcept>

void WavWriter::write(
    const std::string& fileName,
    const Waveform& waveform
) const
{
    std::ofstream file(fileName, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Cannot open output file");
    }

    uint32_t dataSize =
        waveform.sampleCount() * sizeof(int16_t);

    RiffHeader riff = {
        {'R', 'I', 'F', 'F'},
        36 + dataSize,
        {'W', 'A', 'V', 'E'}
    };

    FmtHeader fmt = {
        {'f', 'm', 't', ' '},
        16,
        1,
        Waveform::CHANNELS,
        Waveform::SAMPLE_RATE,
        Waveform::SAMPLE_RATE *
            Waveform::CHANNELS *
            Waveform::BITS_PER_SAMPLE / 8,
        Waveform::CHANNELS *
            Waveform::BITS_PER_SAMPLE / 8,
        Waveform::BITS_PER_SAMPLE
    };

    DataHeader data = {
        {'d', 'a', 't', 'a'},
        dataSize
    };

    file.write(
        reinterpret_cast<const char*>(&riff),
        sizeof(riff)
    );

    file.write(
        reinterpret_cast<const char*>(&fmt),
        sizeof(fmt)
    );

    file.write(
        reinterpret_cast<const char*>(&data),
        sizeof(data)
    );

    file.write(
        reinterpret_cast<const char*>(
            waveform.samples().data()
        ),
        dataSize
    );
}