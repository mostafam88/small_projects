#ifndef MARBLE_HPP
#define MARBLE_HPP

#include "weight.hpp"


namespace SillyProjects
{

struct Marble
{
    Marble(const int id, const Weight::ComparisonResult weightComparison)
      : m_id{id}
      , m_weightComparison{weightComparison}
    {
    }

    bool operator==(const Marble& other) const
    {
        return (this->m_id == other.m_id) &&
               (this->m_weightComparison == other.m_weightComparison);
    }

    const int                      m_id;
    const Weight::ComparisonResult m_weightComparison;
};

} // namespace SillyProjects

#endif