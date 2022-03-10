#include "taskmaster.hpp"

#include <random>

namespace SillyProjects
{

const int Taskmaster::s_maxNumberOfMarbles;
const int Taskmaster::s_maxAllowedComparison;

Taskmaster::Taskmaster()
  : m_marbleWithDifferentWeight{}
  , m_numRemainingComparisons{s_maxAllowedComparison}
{
    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;
    std::mt19937       rng(rd());

    std::uniform_int_distribution<int> uni(1, s_maxNumberOfMarbles);
    m_marbleWithDifferentWeight.m_id = uni(rng);

    std::uniform_int_distribution<int> uni2(1, 2);
    const auto                         weightComparison = uni2(rng);
    if (weightComparison == 1)
    {
        m_marbleWithDifferentWeight.m_weightComparison =
            WeightComparisonResult::heavier;
    } else
    {
        m_marbleWithDifferentWeight.m_weightComparison =
            WeightComparisonResult::lighter;
    }
}

Marble Taskmaster::getMarble()
{
    m_numRemainingComparisons = 0;
    return m_marbleWithDifferentWeight;
}


} // namespace SillyProjects