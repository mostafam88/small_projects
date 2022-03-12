#include "taskmaster.hpp"

#include <random>

namespace SillyProjects
{

const int Taskmaster::s_maxNumberOfMarbles;
const int Taskmaster::s_maxAllowedComparisons;


Taskmaster::Taskmaster(const Marble& uniqueMarble)
  : m_uniqueMarble{uniqueMarble}
  , m_numRemainingComparisons{s_maxAllowedComparisons}
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

    const Marble uniqueMarble{id, weightComparison};

    return Taskmaster(uniqueMarble);
}


WeightComparisonResult Taskmaster::compare(const std::vector<int>& first,
                                           const std::vector<int>& second)
{
    return WeightComparisonResult::heavier;
}


Marble Taskmaster::getMarble()
{
    m_numRemainingComparisons = 0;
    return m_uniqueMarble;
}


} // namespace SillyProjects