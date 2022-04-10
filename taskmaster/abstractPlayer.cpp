#include <assert.h>

#include "abstractPlayer.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair AbstractPlayer::getMarbleIdsPairToCompare()
{
    assert(!m_currentAttemptMarbleIds.has_value());

    m_currentAttemptMarbleIds =
        getMarbleIdsPairToCompare(m_numberOfCompletedAttempts);

    return m_currentAttemptMarbleIds.value();
}


Types::MarbleIdsPair AbstractPlayer::getMarbleIdsPairToCompare(
    const int numberOfCompletedAttempts) const
{
    assert(numberOfCompletedAttempts >= 0 && numberOfCompletedAttempts <= 2);
    if (numberOfCompletedAttempts == 0)
    {
        return getFirstMarbleIdsPairToCompare();
    } else if (numberOfCompletedAttempts == 1)
    {
        return getSecondMarbleIdsPairToCompare();
    } else
    {
        return getThirdMarbleIdsPairToCompare();
    }
}


void AbstractPlayer::updateStatus(
    const Weight::ComparisonResult comparisonResult)
{
    assert(m_currentAttemptMarbleIds.has_value());
    updateStatus(m_currentAttemptMarbleIds.value(), comparisonResult);
    m_currentAttemptMarbleIds.reset();
    ++m_numberOfCompletedAttempts;
}


Types::Id AbstractPlayer::guessUniqueMarbleId() const
{
    assert(m_numberOfCompletedAttempts == 3);
    return getUniqueMarbleId();
}

} // namespace SillyProjects
