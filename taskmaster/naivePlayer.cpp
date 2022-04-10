#include <assert.h>

#include "naivePlayer.hpp"


namespace SillyProjects
{


Types::MarbleIdsPair NaivePlayer::getFirstMarbleIdsPairToCompare() const
{
    assert(m_previousStageResults.empty());

    return m_firstAttempt;
}


Types::MarbleIdsPair NaivePlayer::getSecondMarbleIdsPairToCompare() const
{
    assert(m_previousStageResults.size() == 1);
    assert(m_previousStageResults[0].m_marbleIdsPair == m_firstAttempt);

    return m_secondAttempt.at(m_previousStageResults[0].m_comparisonResult);
}


Types::MarbleIdsPair NaivePlayer::getThirdMarbleIdsPairToCompare() const
{
    assert(m_previousStageResults.size() == 2);
    assert(m_previousStageResults[0].m_marbleIdsPair == m_firstAttempt);
    assert(m_previousStageResults[1].m_marbleIdsPair ==
           m_secondAttempt.at(m_previousStageResults[0].m_comparisonResult));

    return m_thirdAttempt.at(m_previousStageResults[0].m_comparisonResult)
        .at(m_previousStageResults[1].m_comparisonResult);
}


void NaivePlayer::updateStatus(
    const Types::MarbleIdsPair&    currentAttemptMarbleIds,
    const Weight::ComparisonResult comparisonResult)
{
    m_previousStageResults.push_back(Types::MarbleIdsPairAndComparisonResult{
        currentAttemptMarbleIds, comparisonResult});
}

Types::Id NaivePlayer::getUniqueMarbleId() const
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
