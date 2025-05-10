#include <iostream>
#include "engine.h"

int main(int argc, char** argv){

    // Just trying to use those core-defined entities in sanbox to ensure linking.
    Core::String bannerA = Core::__get_banner<Core::Console::HIG>("DBG"_B, 0x66ff6600, 0x66ff6600, 0x66666600);
    Core::String bannerB = Core::__get_banner<Core::Console::HIG>("DBG"  , 0x66ff6600, 0x66ff6600, 0x66666600);
    Core::String bannerC = Core::__get_banner<Core::Console::HIG>("DBG"_D, 0x66ff6600, 0x66ff6600, 0x66666600);
    Core::String highlightedA = Core::__get_highlight<Core::Console::HIG>("This is how to print some debug to console."_B, 0x66ff6600, 0x66666600);
    Core::String highlightedB = Core::__get_highlight<Core::Console::HIG>("This is how to print some debug to console."  , 0x66ff6600, 0x66666600);
    Core::String highlightedC = Core::__get_highlight<Core::Console::HIG>("This is how to print some debug to console."_D, 0x66ff6600, 0x66666600);

    Core::__recurse_output(bannerA, ":"_D, highlightedA);
    Core::__recurse_output(bannerB, ":"_D, highlightedB);
    Core::__recurse_output(bannerC, ":"_D, highlightedC);

    return 0;
}