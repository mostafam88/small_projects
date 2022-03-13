#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "marble.hpp"
#include "types.hpp"
#include "weight.hpp"


namespace SillyProjects
{

class Player
{
public:
    Types::MarbleIdsPair getMarbleIdsPairToCompare(
        std::vector<Types::MarbleIdsPairAndComparisonResult>&
            previousStagesResult) const;

    Marble
    guessUniqueMarble(std::vector<Types::MarbleIdsPairAndComparisonResult>&
                          previousStagesResult) const;

private:
    Types::MarbleIdsPair getFirstMarbleIdsPairToCompare() const;

    Types::MarbleIdsPair getSecondMarbleIdsPairToCompare(
        const Types::MarbleIdsPairAndComparisonResult& firstStageResult) const;

    Types::MarbleIdsPair getThirdMarbleIdsPairToCompare(
        const Types::MarbleIdsPairAndComparisonResult& firstStageResult,
        const Types::MarbleIdsPairAndComparisonResult& secondStageResult) const;

    const Types::MarbleIdsPair m_firstAttempt{{1, 2, 3, 4}, {5, 6, 7, 8}};
};

} // namespace SillyProjects

#endif