#ifndef ABSTRACTPLAYER_HPP
#define ABSTRACTPLAYER_HPP

#include "marble.hpp"
#include "types.hpp"
#include "weight.hpp"


namespace SillyProjects
{

class AbstractPlayer
{
public:
    Types::MarbleIdsPair getMarbleIdsPairToCompare();

    void updateStatus(const Weight::ComparisonResult comparisonResult);

    int guessUniqueMarbleId() const;

protected:
    virtual Types::MarbleIdsPair getFirstMarbleIdsPairToCompare() const  = 0;
    virtual Types::MarbleIdsPair getSecondMarbleIdsPairToCompare() const = 0;
    virtual Types::MarbleIdsPair getThirdMarbleIdsPairToCompare() const  = 0;

    virtual void
    updateStatus(const Types::MarbleIdsPair&    currentAttemptMarbleIds,
                 const Weight::ComparisonResult comparisonResult) = 0;

    virtual int getUniqueMarbleId() const = 0;

private:
    enum class State
    {
        init,
        firstAttemptDone,
        firstResponseReceived,
        secondAttemptDone,
        secondResponceReceived,
        thirdAttemptDone,
        thirdResponceReceived
    } m_state{};

    Types::MarbleIdsPair m_currentAttemptMarbleIds{};
};

} // namespace SillyProjects

#endif