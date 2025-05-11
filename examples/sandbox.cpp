#include <iostream>
#include "engine.h"

int main(int argc, char** argv){

    // Just trying to use those core-defined entities in sanbox to ensure linking.
    Core::String bannerA = Core::__get_banner<Core::Console::LOW>("LOG", 0x66ff6600, 0x66ff6600, 0x66666600);
    Core::String bannerB = Core::__get_banner<Core::Console::MED>("DBG", 0x66ff6600, 0x66ff6600, 0x66666600);
    Core::String bannerC = Core::__get_banner<Core::Console::HIG>("ERR", 0xff666600, 0xff666600, 0x66666600);

    Core::__recurse_output(bannerA, ":", "System initialized"_D, "successfully"_D);
    Core::__recurse_output(bannerA, ":", "Loaded module"_D, "Core::Graphics"_D);
    Core::__recurse_output(bannerA, ":", "Configuration file"_D, "config.json"_D);
    Core::__recurse_output(bannerB, ":", "Memory pool"_D, "allocated"_D);
    Core::__recurse_output(bannerB, ":", "Time sync"_D, "complete"_B);
    Core::__recurse_output(bannerA, ":", "Input handler"_D, "registered"_D);
    Core::__recurse_output(bannerA, ":", "Scheduler"_D, "running"_D);
    Core::__recurse_output(bannerB, ":", "Network connection"_D, "established"_B);
    Core::__recurse_output(bannerC, ":", "Critical failure in module"_D, "ShaderCompiler"_D);


    return 0;
}