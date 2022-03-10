#include "taskmaster.hpp"

#include <random>

namespace SillyProjects
{

const int Taskmaster::s_maxNumberOfMarbles;
const int Taskmaster::s_maxAllowedComparison;

Taskmaster::Taskmaster()
  : m_idMarbleWithDifferentWeight{0}
  , m_numRemainingComparisons{s_maxAllowedComparison}
{
    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device                 rd;
    std::mt19937                       rng(rd());
    std::uniform_int_distribution<int> uni(1, s_maxNumberOfMarbles);

    m_idMarbleWithDifferentWeight = uni(rng);
}

int Taskmaster::getMarbleId()
{
    m_numRemainingComparisons = 0;
    return m_idMarbleWithDifferentWeight;
}


} // namespace SillyProjects