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
    return m_firstAttempt;
}


Types::MarbleIdsPair Player::getSecondMarbleIdsPairToCompare(
    const Types::MarbleIdsPairAndComparisonResult& firstStageResult) const
{
    assert(firstStageResult.m_marbleIdsPair == m_firstAttempt);
    return {};
}


Types::MarbleIdsPair Player::getThirdMarbleIdsPairToCompare(
    const Types::MarbleIdsPairAndComparisonResult& firstStageResult,
    const Types::MarbleIdsPairAndComparisonResult& secondStageResult) const
{
    assert(firstStageResult.m_marbleIdsPair == m_firstAttempt);
    return {};
}


int Player::guessUniqueMarbleId(
    std::vector<Types::MarbleIdsPairAndComparisonResult>& previousStagesResult)
    const
{
    assert(previousStagesResult.size() == Taskmaster::s_maxAllowedComparisons);
    assert(previousStagesResult[0].m_marbleIdsPair == m_firstAttempt);

    return 0;
}

} // namespace SillyProjects
