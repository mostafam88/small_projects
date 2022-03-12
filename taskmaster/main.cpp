#include <iostream>

#include "taskmaster.hpp"

int main()
{
    std::cout << "Hello Taskmaster!\n";

    auto taskmaster = SillyProjects::Taskmaster::create();
    const auto marble = taskmaster.getMarble();
    std::cout << marble.m_id << "\n";
}