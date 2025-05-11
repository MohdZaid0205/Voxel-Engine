#include <iostream>
#include "engine.h"
// #include "thread"

// just here temporarily to verify intended functionalitites

int add_function(int a, int b) {
    Core::Console::Log("add_function was called with a="_D, a, "b="_D, b);
    return a + b;
}

int loop_it(int n) {
    Core::Console::Log<Core::Console::HIG>("initiating loop_it with n="_D, n);
    Core::uInt32 j = 0;
    for (Core::uInt32 i = 0; i < n; i++){
        j = add_function(j, i);
    }
    Core::Console::Log<Core::Console::HIG>("Looping finished with j="_D, j);
    return j;
}

int main(int argc, char** argv){

    // Just trying to use those core-defined entities in sanbox to ensure linking.
    //Core::String bannerA = Core::__get_banner<Core::Console::LOW>("LOG", 0x66ff6600, 0x66ff6600, 0x66666600);
    //Core::String bannerB = Core::__get_banner<Core::Console::MED>("DBG", 0x66ff6600, 0x66ff6600, 0x66666600);
    //Core::String bannerC = Core::__get_banner<Core::Console::HIG>("ERR", 0xff666600, 0xff666600, 0x66666600);

    //Core::__recurse_output(bannerA, ":", "System initialized"_D, "successfully"_D);
    //Core::__recurse_output(bannerA, ":", "Loaded module"_D, "Core::Graphics"_D);
    //Core::__recurse_output(bannerA, ":", "Configuration file"_D, "config.json"_D);
    //Core::__recurse_output(bannerB, ":", "Memory pool"_D, "allocated"_D);
    //Core::__recurse_output(bannerB, ":", "Time sync"_D, "complete"_B);
    //Core::__recurse_output(bannerA, ":", "Input handler"_D, "registered"_D);
    //Core::__recurse_output(bannerA, ":", "Scheduler"_D, "running"_D);
    //Core::__recurse_output(bannerB, ":", "Network connection"_D, "established"_B);
    //Core::__recurse_output(bannerC, ":", "Critical failure in module"_D, "ShaderCompiler"_D);
    
    Core::uInt32 want = 69;
    Core::Console::Info<Core::Console::MED>("Starting Loop from main"_D);
    Core::uInt32 result1 = loop_it(10);
    Core::uInt32 result2 = loop_it(9);
    if (result1 < want) {
        Core::Console::Error<Core::Console::HIG>("Wanted result to be higher than "_D, want, "But got"_D, result1, "result"_D, "unsatisfactory"_B);
    }
    else {
        Core::Console::Info<Core::Console::MED>("You have passed the test"_D);
    }
    
    return 0;
}