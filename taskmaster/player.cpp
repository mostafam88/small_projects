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
    return m_secondAttempt.at(firstStageResult.m_comparisonResult);
}


Types::MarbleIdsPair Player::getThirdMarbleIdsPairToCompare(
    const Types::MarbleIdsPairAndComparisonResult& firstStageResult,
    const Types::MarbleIdsPairAndComparisonResult& secondStageResult) const
{
    assert(firstStageResult.m_marbleIdsPair == m_firstAttempt);
    assert(secondStageResult.m_marbleIdsPair ==
           m_secondAttempt.at(firstStageResult.m_comparisonResult));
    return m_thirdAttempt.at(firstStageResult.m_comparisonResult)
        .at(secondStageResult.m_comparisonResult);
}


int Player::guessUniqueMarbleId(
    std::vector<Types::MarbleIdsPairAndComparisonResult>& previousStagesResult)
    const
{
    assert(previousStagesResult.size() == Taskmaster::s_maxAllowedComparisons);
    assert(previousStagesResult[0].m_marbleIdsPair == m_firstAttempt);
    assert(previousStagesResult[1].m_marbleIdsPair ==
           m_secondAttempt.at(previousStagesResult[0].m_comparisonResult));
    assert(previousStagesResult[2].m_marbleIdsPair ==
           (m_thirdAttempt.at(previousStagesResult[0].m_comparisonResult)
                .at(previousStagesResult[1].m_comparisonResult)));

    return m_finalGuess.at(previousStagesResult[0].m_comparisonResult)
        .at(previousStagesResult[1].m_comparisonResult)
        .at(previousStagesResult[2].m_comparisonResult);
}

} // namespace SillyProjects
