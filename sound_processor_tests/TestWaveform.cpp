#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "waveform.h"

using Catch::Approx;

TEST_CASE("Waveform default constructor")
{
    Waveform waveform;

    REQUIRE(waveform.sampleCount() == 0);
}

TEST_CASE("Waveform stores")
{
    Waveform waveform({100, 200, 300});

    REQUIRE(waveform.sampleCount() == 3);

    REQUIRE(waveform[0] == 100);
    REQUIRE(waveform[1] == 200);
    REQUIRE(waveform[2] == 300);
}

TEST_CASE("Waveform operator[]")
{
    Waveform waveform({100, 200, 300});

    waveform[1] = 500;

    REQUIRE(waveform[1] == 500);
}

TEST_CASE("Waveform duration")
{
    Waveform waveform(
        std::vector<int16_t>(44100)
    );

    REQUIRE(waveform.durationSeconds() == Approx(1.0));
}

TEST_CASE("Waveform seconds to samples")
{
    Waveform waveform;

    REQUIRE(
        waveform.secondsToSamples(1.0)
        == 44100
    );

    REQUIRE(
        waveform.secondsToSamples(0.5)
        == 22050
    );
}

TEST_CASE("Waveform samples to seconds")
{
    Waveform waveform;

    REQUIRE(
        waveform.samplesToSeconds(44100)
        == Approx(1.0)
    );

    REQUIRE(
        waveform.samplesToSeconds(22050)
        == Approx(0.5)
    );
}

TEST_CASE("Waveform resize")
{
    Waveform waveform({1, 2, 3});

    waveform.resizeBySamples(10);

    REQUIRE(
        waveform.sampleCount() == 10
    );
}