#include <iostream>

#include "player.hpp"
#include "taskmaster.hpp"

int main()
{
    std::cout << "Hello Taskmaster!\n";

    const SillyProjects::Player player{};

    auto       taskmaster = SillyProjects::Taskmaster::create();
    const bool success    = taskmaster.play(player);

    std::cout << "The game finished " << (success ? "" : "un")
              << "successfully!\n";

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}