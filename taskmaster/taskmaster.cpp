#include "taskmaster.hpp"

#include <random>

namespace SillyProjects
{

const int Taskmaster::s_maxNumberOfMarbles;
const int Taskmaster::s_maxAllowedComparison;


Taskmaster::Taskmaster(const Marble& marbleWithDifferentWeight)
  : m_marbleWithDifferentWeight{marbleWithDifferentWeight}
  , m_numRemainingComparisons{s_maxAllowedComparison}
{
}


Taskmaster Taskmaster::create()
{
    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;
    std::mt19937       rng(rd());

    std::uniform_int_distribution<int> uni(1, s_maxNumberOfMarbles);
    const int                          id = uni(rng);

    std::uniform_int_distribution<int> uni2(1, 2);
    const auto                         randomBinary     = uni2(rng);
    const auto                         weightComparison = (randomBinary == 1)
                                                              ? WeightComparisonResult::heavier
                                                              : WeightComparisonResult::lighter;

    const Marble marbleWithDifferentWeight{id, weightComparison};

    return Taskmaster(marbleWithDifferentWeight);
}


WeightComparisonResult Taskmaster::compare(const std::vector<int>& first,
                                           const std::vector<int>& second)
{
    return WeightComparisonResult::heavier;
}


Marble Taskmaster::getMarble()
{
    m_numRemainingComparisons = 0;
    return m_marbleWithDifferentWeight;
}


} // namespace SillyProjects