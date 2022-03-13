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
};

} // namespace SillyProjects

#endif