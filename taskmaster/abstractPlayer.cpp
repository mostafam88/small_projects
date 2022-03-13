#include <assert.h>

#include "abstractPlayer.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair AbstractPlayer::getMarbleIdsPairToCompare()
{
    if (m_state == State::init)
    {
        m_currentAttemptMarbleIds = getFirstMarbleIdsPairToCompare();
        m_state                   = State::firstAttemptDone;
    } else if (m_state == State::firstResponseReceived)
    {
        m_currentAttemptMarbleIds = getSecondMarbleIdsPairToCompare();
        m_state                   = State::secondAttemptDone;
    } else if (m_state == State::secondResponceReceived)
    {
        m_currentAttemptMarbleIds = getThirdMarbleIdsPairToCompare();
        m_state                   = State::thirdAttemptDone;
    } else
    {
        // invalid m_state
        assert(false);
    }

    return m_currentAttemptMarbleIds;
}

void AbstractPlayer::updateStatus(
    const Weight::ComparisonResult comparisonResult)
{
    updateStatus(m_currentAttemptMarbleIds, comparisonResult);

    if (m_state == State::firstAttemptDone)
    {
        m_state = State::firstResponseReceived;
    } else if (m_state == State::secondAttemptDone)
    {
        m_state = State::secondResponceReceived;
    } else if (m_state == State::thirdAttemptDone)
    {
        m_state = State::thirdResponceReceived;
    } else
    {
        // invalid m_state
        assert(false);
    }
}

int AbstractPlayer::guessUniqueMarbleId() const
{
    assert(m_state == State::thirdResponceReceived);
    return getUniqueMarbleId();
}

} // namespace SillyProjects
