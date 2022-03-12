#include <algorithm>
#include <random>

#include "taskmaster.hpp"
#include "taskmasterHelpers.hpp"


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
    const auto marbleIdsPair =
        TaskmasterHelpers::getNonRepetitiveMarbleIds(first, second);
    const auto sizeComparisonResult = compareSizes(marbleIdsPair);

    if (sizeComparisonResult.has_value())
    {
        return sizeComparisonResult.value();
    } else
    {
        return safeCompare(marbleIdsPair);
    }
}


std::optional<WeightComparisonResult>
Taskmaster::compareSizes(const Types::MarbleIdsPair& marbleIdsPair)
{
    const auto& first  = marbleIdsPair.first;
    const auto& second = marbleIdsPair.second;

    if (first.empty() && second.empty())
    {
        return {WeightComparisonResult::equal};
    } else if (first.size() < second.size())
    {
        return {WeightComparisonResult::lighter};
    } else if (first.size() > second.size())
    {
        return {WeightComparisonResult::heavier};
    } else
    {
        return {};
    }
}


WeightComparisonResult
Taskmaster::safeCompare(const Types::MarbleIdsPair& marbleIdsPair)
{
    const auto& first  = marbleIdsPair.first;
    const auto& second = marbleIdsPair.second;

    const auto itFirst =
        std::find(first.begin(), first.end(), m_uniqueMarble.m_id);
    const bool foundInFirst = (itFirst != first.end());
    if (foundInFirst)
    {
        return m_uniqueMarble.m_weightComparison;
    } else
    {
        const auto itSecond =
            std::find(second.begin(), second.end(), m_uniqueMarble.m_id);
        const bool foundInSecond = (itSecond != second.end());
        if (foundInSecond)
        {
            return (m_uniqueMarble.m_weightComparison ==
                    WeightComparisonResult::lighter)
                       ? WeightComparisonResult::heavier
                       : WeightComparisonResult::lighter;

        } else
        {
            return WeightComparisonResult::equal;
        }
    }
}


Marble Taskmaster::getMarble()
{
    m_numRemainingComparisons = 0;
    return m_uniqueMarble;
}


} // namespace SillyProjects