#include "taskmaster.hpp"


namespace SillyProjects
{

Taskmaster::Taskmaster()
  : m_idMarbleWithDifferentWeight{0}
  , m_numRemainingComparisons{s_maxAllowedComparison}
{
}

} // namespace SillyProjects