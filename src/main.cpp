#include <iostream>

#include <spectogram/visualizer.hpp>

int main() {
    Config config{};
    Visualizer vis{config};

    vis.init(config);
    vis.loop();
}
