#ifndef SOUND_PROCESSOR_APPLICATION_H
#define SOUND_PROCESSOR_APPLICATION_H

#include "PipelineConverter.h"

class Application {
public:
    void configure();
    int start(int argc, char* argv[]);

private:
    CmdLineArgs2PipelineConverter converter_;
};

#endif //SOUND_PROCESSOR_APPLICATION_H