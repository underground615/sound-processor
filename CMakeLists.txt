cmake_minimum_required(VERSION 4.0)
project(sound_processor_tests)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.15.1
)

FetchContent_MakeAvailable(Catch2)

include_directories(app)
include_directories(command_line)
include_directories(filters)
include_directories(pipeline)
include_directories(wav)

add_executable(sound_processor
        app/application.cpp
        app/application.h
        app/main.cpp
        command_line/CLIParser.cpp
        command_line/CLIParser.h
        pipeline/FilterProducer.cpp
        pipeline/FilterProducer.h
        pipeline/pipeline.cpp
        pipeline/pipeline.h
        pipeline/PipelineConverter.cpp
        pipeline/PipelineConverter.h
        wav/waveform.cpp
        wav/waveform.h
        wav/WavRead.cpp
        wav/WavRead.h
        wav/WavWrite.cpp
        wav/WavWrite.h
        wav/WavHeader.h
        filters/filter.h
        filters/filters.h
        filters/AmplFilter.h
        filters/AmplFilter.cpp
        filters/NormalizeFilter.h
        filters/NormalizeFilter.cpp
        filters/SilenceFilter.h
        filters/SilenceFilter.cpp
        filters/TimestretchFilter.cpp
        filters/TimestretchFilter.h
        filters/LowpassFilter.cpp
        filters/LowpassFilter.h
        filters/SinGeneratorFilter.cpp
        filters/SinGeneratorFilter.h
        filters/AmGeneratorFilter.cpp
        filters/AmGeneratorFilter.h
        filters/FmGeneratorFilter.cpp
        filters/FmGeneratorFilter.h
)

add_executable(sound_processor_tests
        sound_processor_tests/TestFilters.cpp
        sound_processor_tests/TestParser.cpp
        sound_processor_tests/TestWaveform.cpp

        wav/waveform.cpp

        command_line/CLIParser.cpp

        filters/filters.h
        filters/AmplFilter.cpp
        filters/NormalizeFilter.cpp
        filters/SilenceFilter.cpp
        filters/TimestretchFilter.cpp
        filters/LowpassFilter.cpp
        filters/SinGeneratorFilter.cpp
        filters/AmGeneratorFilter.cpp
        filters/FmGeneratorFilter.cpp

        pipeline/pipeline.cpp
        pipeline/FilterProducer.cpp
        pipeline/PipelineConverter.cpp
)

target_link_libraries(
        sound_processor_tests
        PRIVATE
        Catch2::Catch2WithMain
)