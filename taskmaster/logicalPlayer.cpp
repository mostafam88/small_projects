#include "logicalPlayer.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair LogicalPlayer::getFirstMarbleIdsPairToCompare() const
{
    return Types::MarbleIdsPair{};
}


Types::MarbleIdsPair LogicalPlayer::getSecondMarbleIdsPairToCompare() const
{
    return Types::MarbleIdsPair{};
}


Types::MarbleIdsPair LogicalPlayer::getThirdMarbleIdsPairToCompare() const
{
    return Types::MarbleIdsPair{};
}


void LogicalPlayer::updateStatus(
    const Types::MarbleIdsPair&    currentAttemptMarbleIds,
    const Weight::ComparisonResult comparisonResult)
{
}


int LogicalPlayer::getUniqueMarbleId() const
{
    return -1;
}

} // namespace SillyProjects