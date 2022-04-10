#include <iostream>

#include "logicalPlayer.hpp"
#include "naivePlayer.hpp"
#include "taskmaster.hpp"

int main()
{
    std::cout << "Hello Taskmaster!\n";

    SillyProjects::LogicalPlayer player{};

    auto       taskmaster = SillyProjects::Taskmaster::create();
    const bool success    = taskmaster.play(player, std::cout);

    std::cout << "The game finished " << (success ? "" : "un")
              << "successfully!\n";

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}