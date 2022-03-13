#include <assert.h>

#include "player.hpp"
#include "taskmaster.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair Player::getMarbleIdsPairToCompare()
{
    static_assert(Taskmaster::s_maxAllowedComparisons == 3);

    if (m_previousStageResults.empty())
    {
        m_currentAttemptMarbleIds = getFirstMarbleIdsPairToCompare();
    } else if (m_previousStageResults.size() == 1)
    {
        m_currentAttemptMarbleIds = getSecondMarbleIdsPairToCompare();
    } else
    {
        assert(m_previousStageResults.size() == 2);
        m_currentAttemptMarbleIds = getThirdMarbleIdsPairToCompare();
    }

    return m_currentAttemptMarbleIds;
}

void Player::updateStatus(const Weight::ComparisonResult comparisonResult)
{
    m_previousStageResults.push_back(Types::MarbleIdsPairAndComparisonResult{
        m_currentAttemptMarbleIds, comparisonResult});
}

Types::MarbleIdsPair Player::getFirstMarbleIdsPairToCompare() const
{
    assert(m_previousStageResults.empty());

    return m_firstAttempt;
}


Types::MarbleIdsPair Player::getSecondMarbleIdsPairToCompare() const
{
    assert(m_previousStageResults.size() == 1);
    assert(m_previousStageResults[0].m_marbleIdsPair == m_firstAttempt);

    return m_secondAttempt.at(m_previousStageResults[0].m_comparisonResult);
}


Types::MarbleIdsPair Player::getThirdMarbleIdsPairToCompare() const
{
    assert(m_previousStageResults.size() == 2);
    assert(m_previousStageResults[0].m_marbleIdsPair == m_firstAttempt);
    assert(m_previousStageResults[1].m_marbleIdsPair ==
           m_secondAttempt.at(m_previousStageResults[0].m_comparisonResult));

    return m_thirdAttempt.at(m_previousStageResults[0].m_comparisonResult)
        .at(m_previousStageResults[1].m_comparisonResult);
}


int Player::guessUniqueMarbleId() const
{
    assert(m_previousStageResults.size() == 3);
    assert(m_previousStageResults[0].m_marbleIdsPair == m_firstAttempt);
    assert(m_previousStageResults[1].m_marbleIdsPair ==
           m_secondAttempt.at(m_previousStageResults[0].m_comparisonResult));
    assert(m_previousStageResults[2].m_marbleIdsPair ==
           (m_thirdAttempt.at(m_previousStageResults[0].m_comparisonResult)
                .at(m_previousStageResults[1].m_comparisonResult)));

    return m_finalGuess.at(m_previousStageResults[0].m_comparisonResult)
        .at(m_previousStageResults[1].m_comparisonResult)
        .at(m_previousStageResults[2].m_comparisonResult);
}

} // namespace SillyProjects
