#include "player.hpp"

namespace SillyProjects
{

Types::MarbleIdsPair Player::getMarbleIdsPairToCompare(
    std::vector<Types::MarbleIdsPairAndComparisonResult>& previousStagesResult)
    const
{
    static_assert(Taskmaster::s_maxAllowedComparisons == 3);
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
