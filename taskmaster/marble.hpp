#ifndef MARBLE_HPP
#define MARBLE_HPP

#include "types.hpp"
#include "weight.hpp"


namespace SillyProjects
{

struct Marble
{
    Marble(const Types::Id id, const Weight::ComparisonResult weightComparison);

    const Types::Id                m_id;
    const Weight::ComparisonResult m_weightComparison;
};

std::ostream& operator<<(std::ostream& os, const Marble& marble);

} // namespace SillyProjects

#endif