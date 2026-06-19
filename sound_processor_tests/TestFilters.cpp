#include <catch2/catch_test_macros.hpp>

#include "filters.h"

TEST_CASE("AmplFilter multiply")
{
    Waveform w({1000, -2000, 3000});

    AmplFilter filter(2.0);
    filter.apply(w);

    REQUIRE(w[0] == 2000);
    REQUIRE(w[1] == -4000);
    REQUIRE(w[2] == 6000);
}

TEST_CASE("NormalizeFilter max val")
{
    Waveform w({1000, -2000, 500});

    NormalizeFilter filter;
    filter.apply(w);

    REQUIRE(w[0] == 16383);
    REQUIRE(w[1] == -32767);
    REQUIRE(w[2] == 8191);
}

TEST_CASE("TimestretchFilter increase sample count")
{
    Waveform w({100, 200, 300});

    TimestretchFilter filter(2.0);

    REQUIRE(filter.apply(w) == Filter::State::ok);

    REQUIRE(w.sampleCount() == 6);

    REQUIRE(w[0] == 100);
    REQUIRE(w[5] == 300);
}