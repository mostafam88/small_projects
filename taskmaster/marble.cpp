#include "marble.hpp"

namespace SillyProjects
{

Marble::Marble(const int id, const Weight::ComparisonResult weightComparison)
  : m_id{id}
  , m_weightComparison{weightComparison}
{
}


std::ostream& operator<<(std::ostream& os, const Marble& marble)
{
    os << "(id: " << marble.m_id << ", weightComparison: "
       << ((marble.m_weightComparison == Weight::ComparisonResult::heavier)
               ? "heavier"
               : "lighter")
       << ')';
    return os;
}

} // namespace SillyProjects