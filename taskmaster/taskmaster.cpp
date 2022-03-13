#include <algorithm>
#include <random>

#include "taskmaster.hpp"
#include "taskmasterHelpers.hpp"
#include "player.hpp"


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
                                                              ? Weight::ComparisonResult::heavier
                                                              : Weight::ComparisonResult::lighter;

    const Marble uniqueMarble{id, weightComparison};

    return Taskmaster(uniqueMarble);
}


bool Taskmaster::play(const Player& player)
{
    return false;
}


Weight::ComparisonResult
Taskmaster::compare(const Types::MarbleIds& first,
                    const Types::MarbleIds& second) const
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


std::optional<Weight::ComparisonResult>
Taskmaster::compareSizes(const Types::MarbleIdsPair& marbleIdsPair) const
{
    const auto& first  = marbleIdsPair.first;
    const auto& second = marbleIdsPair.second;

    if (first.empty() && second.empty())
    {
        return {Weight::ComparisonResult::equal};
    } else if (first.size() < second.size())
    {
        return {Weight::ComparisonResult::lighter};
    } else if (first.size() > second.size())
    {
        return {Weight::ComparisonResult::heavier};
    } else
    {
        return {};
    }
}


Weight::ComparisonResult
Taskmaster::safeCompare(const Types::MarbleIdsPair& marbleIdsPair) const
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
            return Weight::oppositeOf(m_uniqueMarble.m_weightComparison);

        } else
        {
            return Weight::ComparisonResult::equal;
        }
    }
}

} // namespace SillyProjects