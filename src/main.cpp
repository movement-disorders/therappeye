#include <iostream>
#include "engine.h"

int main() {

    // Init engine
    Engine engine;

    while (engine.running()) {
        
        // Update
        engine.update();

        // Render
        engine.render();
    }

    return 0;
}
