#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>

#include "marble.hpp"
#include "types.hpp"
#include "weight.hpp"


namespace SillyProjects
{

class Player
{
public:
    Types::MarbleIdsPair getMarbleIdsPairToCompare();

    void updateStatus(const Weight::ComparisonResult comparisonResult);

    int guessUniqueMarbleId() const;

private:
    Types::MarbleIdsPair getFirstMarbleIdsPairToCompare() const;

    Types::MarbleIdsPair getSecondMarbleIdsPairToCompare() const;

    Types::MarbleIdsPair getThirdMarbleIdsPairToCompare() const;

    const Types::MarbleIdsPair m_firstAttempt{{1, 2, 3, 4}, {5, 6, 7, 8}};
    const std::map<Weight::ComparisonResult, Types::MarbleIdsPair>
        m_secondAttempt{
            {Weight::ComparisonResult::lighter, {{1, 2, 5}, {3, 6, 9}}},
            {Weight::ComparisonResult::equal, {{1, 2}, {9, 10}}},
            {Weight::ComparisonResult::heavier, {{1, 2, 5}, {3, 6, 9}}}};
    const std::map<Weight::ComparisonResult,
                   std::map<Weight::ComparisonResult, Types::MarbleIdsPair>>
        m_thirdAttempt{{Weight::ComparisonResult::lighter,
                        {{Weight::ComparisonResult::lighter, {{1}, {2}}},
                         {Weight::ComparisonResult::equal, {{7}, {8}}},
                         {Weight::ComparisonResult::heavier, {{1}, {3}}}}},
                       {Weight::ComparisonResult::equal,
                        {{Weight::ComparisonResult::lighter, {{1}, {9}}},
                         {Weight::ComparisonResult::equal, {{1}, {11}}},
                         {Weight::ComparisonResult::heavier, {{1}, {9}}}}},
                       {Weight::ComparisonResult::heavier,
                        {{Weight::ComparisonResult::lighter, {{1}, {3}}},
                         {Weight::ComparisonResult::equal, {{7}, {8}}},
                         {Weight::ComparisonResult::heavier, {{1}, {2}}}}}};

    const std::map<Weight::ComparisonResult,
                   std::map<Weight::ComparisonResult,
                            std::map<Weight::ComparisonResult, int>>>
        m_finalGuess{{Weight::ComparisonResult::lighter,
                      {{Weight::ComparisonResult::lighter,
                        {{Weight::ComparisonResult::lighter, 1},
                         {Weight::ComparisonResult::equal, 6},
                         {Weight::ComparisonResult::heavier, 2}}},
                       {Weight::ComparisonResult::equal,
                        {{Weight::ComparisonResult::lighter, 8},
                         {Weight::ComparisonResult::equal, 4},
                         {Weight::ComparisonResult::heavier, 7}}},
                       {Weight::ComparisonResult::heavier,
                        {{Weight::ComparisonResult::lighter, 3},
                         {Weight::ComparisonResult::equal, 5},
                         {Weight::ComparisonResult::heavier, 3}}}}},
                     {Weight::ComparisonResult::equal,
                      {{Weight::ComparisonResult::lighter,
                        {{Weight::ComparisonResult::lighter, 9},
                         {Weight::ComparisonResult::equal, 10},
                         {Weight::ComparisonResult::heavier, 9}}},
                       {Weight::ComparisonResult::equal,
                        {{Weight::ComparisonResult::lighter, 11},
                         {Weight::ComparisonResult::equal, 12},
                         {Weight::ComparisonResult::heavier, 11}}},
                       {Weight::ComparisonResult::heavier,
                        {{Weight::ComparisonResult::lighter, 9},
                         {Weight::ComparisonResult::equal, 10},
                         {Weight::ComparisonResult::heavier, 9}}}}},
                     {Weight::ComparisonResult::heavier,
                      {{Weight::ComparisonResult::lighter,
                        {{Weight::ComparisonResult::lighter, 3},
                         {Weight::ComparisonResult::equal, 5},
                         {Weight::ComparisonResult::heavier, 3}}},
                       {Weight::ComparisonResult::equal,
                        {{Weight::ComparisonResult::lighter, 7},
                         {Weight::ComparisonResult::equal, 4},
                         {Weight::ComparisonResult::heavier, 8}}},
                       {Weight::ComparisonResult::heavier,
                        {{Weight::ComparisonResult::lighter, 2},
                         {Weight::ComparisonResult::equal, 6},
                         {Weight::ComparisonResult::heavier, 1}}}}}};

    std::vector<Types::MarbleIdsPairAndComparisonResult>
        m_previousStageResults{};

    Types::MarbleIdsPair m_currentAttemptMarbleIds{};
};

} // namespace SillyProjects

#endif