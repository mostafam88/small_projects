#ifndef MARBLE_HPP
#define MARBLE_HPP

#include "weight.hpp"


namespace SillyProjects
{

struct Marble
{
    Marble(const int id, const Weight::ComparisonResult weightComparison);

    const int                      m_id;
    const Weight::ComparisonResult m_weightComparison;
};

std::ostream& operator<<(std::ostream& os, const Marble& marble);

} // namespace SillyProjects

#endif