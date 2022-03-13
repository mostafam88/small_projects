#include <assert.h>

#include "player.hpp"
#include "taskmaster.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair Player::getMarbleIdsPairToCompare(
    std::vector<Types::MarbleIdsPairAndComparisonResult>& previousStagesResult)
    const
{
    static_assert(Taskmaster::s_maxAllowedComparisons == 3);

    if (previousStagesResult.empty())
    {
        return getFirstMarbleIdsPairToCompare();
    } else if (previousStagesResult.size() == 1)
    {
        return getSecondMarbleIdsPairToCompare(previousStagesResult[0]);
    } else
    {
        assert(previousStagesResult.size() == 2);
        return getThirdMarbleIdsPairToCompare(previousStagesResult[0],
                                              previousStagesResult[1]);
    }
}

Types::MarbleIdsPair Player::getFirstMarbleIdsPairToCompare() const
{
    return {};
}


Types::MarbleIdsPair Player::getSecondMarbleIdsPairToCompare(
    const Types::MarbleIdsPairAndComparisonResult& firstStageResult) const
{
    return {};
}


Types::MarbleIdsPair Player::getThirdMarbleIdsPairToCompare(
    const Types::MarbleIdsPairAndComparisonResult& firstStageResult,
    const Types::MarbleIdsPairAndComparisonResult& secondStageResult) const
{
    return {};
}


Marble Player::guessUniqueMarble(
    std::vector<Types::MarbleIdsPairAndComparisonResult>& previousStagesResult)
    const
{
    assert(previousStagesResult.size() == Taskmaster::s_maxAllowedComparisons);
    return Marble{0, Weight::ComparisonResult::equal};
}

} // namespace SillyProjects
