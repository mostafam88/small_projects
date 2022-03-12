#ifndef MARBLE_HPP
#define MARBLE_HPP

#include "weightComparisonResult.hpp"


namespace SillyProjects
{

struct Marble
{
    Marble(const int id, const Weight::ComparisonResult weightComparison)
      : m_id{id}
      , m_weightComparison{weightComparison}
    {
    }
    const int                    m_id;
    const Weight::ComparisonResult m_weightComparison;
};

} // namespace SillyProjects

#endif