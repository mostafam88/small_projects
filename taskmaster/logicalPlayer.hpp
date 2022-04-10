#include "abstractPlayer.hpp"

namespace SillyProjects
{

class LogicalPlayer : public AbstractPlayer
{
protected:
    virtual Types::MarbleIdsPair getFirstMarbleIdsPairToCompare() const;

    virtual Types::MarbleIdsPair getSecondMarbleIdsPairToCompare() const;

    virtual Types::MarbleIdsPair getThirdMarbleIdsPairToCompare() const;

    virtual void
    updateStatus(const Types::MarbleIdsPair&    currentAttemptMarbleIds,
                 const Weight::ComparisonResult comparisonResult);

    virtual int getUniqueMarbleId() const;

private:
};

} // namespace SillyProjects