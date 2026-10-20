#include <iostream>

#include <spectogram/config.hpp>
#include <spectogram/visualizer.hpp>

int main(int argc, char **argv) {
    Config config{};
    Visualizer vis;
    
    vis.init(config);
    vis.loop();
    
    std::cout << "DONE!" << std::endl;
}
