#include <algorithm>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <random>

#include "abstractPlayer.hpp"
#include "taskmaster.hpp"
#include "taskmasterHelpers.hpp"


namespace SillyProjects
{

const int Taskmaster::s_maxNumberOfMarbles;
const int Taskmaster::s_maxAllowedComparisons;


Taskmaster::Taskmaster(const Marble& uniqueMarble)
  : m_uniqueMarble{uniqueMarble}
{
}


Taskmaster Taskmaster::create()
{
    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;
    std::mt19937       rng(rd());

    std::uniform_int_distribution<Types::Id> uni(1, s_maxNumberOfMarbles);
    const Types::Id                          id = uni(rng);

    std::uniform_int_distribution<int> uni2(1, 2);
    const auto                         randomBinary     = uni2(rng);
    const auto                         weightComparison = (randomBinary == 1)
                                                              ? Weight::ComparisonResult::heavier
                                                              : Weight::ComparisonResult::lighter;

    const Marble uniqueMarble{id, weightComparison};

    return Taskmaster(uniqueMarble);
}

bool Taskmaster::play(AbstractPlayer& player, std::ostream& os)
{
    logPlayPrologue(os);

    for (int attempt = 1; attempt <= s_maxAllowedComparisons; ++attempt)
    {
        const auto currentMarbleIdsPair = player.getMarbleIdsPairToCompare();
        const auto currentComparisonResult =
            compare(currentMarbleIdsPair.first, currentMarbleIdsPair.second);
        logPlayAttempt(attempt, currentMarbleIdsPair, currentComparisonResult,
                       os);
        player.updateStatus(currentComparisonResult);
    }

    const auto guessedMarbleId = player.guessUniqueMarbleId();

    logPlayEnding(guessedMarbleId, os);

    return (guessedMarbleId == m_uniqueMarble.m_id);
}


Weight::ComparisonResult
Taskmaster::compare(const Types::MarbleIds& first,
                    const Types::MarbleIds& second) const
{
    const auto marbleIdsPair =
        TaskmasterHelpers::getNonRepetitiveMarbleIds(first, second);
    const auto sizeComparisonResult = compareSizes(marbleIdsPair);

    if (sizeComparisonResult.has_value())
    {
        return sizeComparisonResult.value();
    } else
    {
        return safeCompare(marbleIdsPair);
    }
}


std::optional<Weight::ComparisonResult>
Taskmaster::compareSizes(const Types::MarbleIdsPair& marbleIdsPair) const
{
    const auto& first  = marbleIdsPair.first;
    const auto& second = marbleIdsPair.second;

    if (first.empty() && second.empty())
    {
        return {Weight::ComparisonResult::equal};
    } else if (first.size() < second.size())
    {
        return {Weight::ComparisonResult::lighter};
    } else if (first.size() > second.size())
    {
        return {Weight::ComparisonResult::heavier};
    } else
    {
        return {};
    }
}


Weight::ComparisonResult
Taskmaster::safeCompare(const Types::MarbleIdsPair& marbleIdsPair) const
{
    const auto& first  = marbleIdsPair.first;
    const auto& second = marbleIdsPair.second;

    const auto itFirst =
        std::find(first.begin(), first.end(), m_uniqueMarble.m_id);
    const bool foundInFirst = (itFirst != first.end());
    if (foundInFirst)
    {
        return m_uniqueMarble.m_weightComparison;
    } else
    {
        const auto itSecond =
            std::find(second.begin(), second.end(), m_uniqueMarble.m_id);
        const bool foundInSecond = (itSecond != second.end());
        if (foundInSecond)
        {
            return Weight::oppositeOf(m_uniqueMarble.m_weightComparison);

        } else
        {
            return Weight::ComparisonResult::equal;
        }
    }
}


void Taskmaster::logPlayPrologue(std::ostream& os) const
{
    os << std::string(90, '=')
       << "\nTaskmaster: Player wants to find this unique marble: "
       << m_uniqueMarble << '\n'
       << std::string(90, '-') << '\n';
}


void Taskmaster::logPlayAttempt(const int                      attempt,
                                const Types::MarbleIdsPair&    marbleIdsPair,
                                const Weight::ComparisonResult comparisonResult,
                                std::ostream&                  os) const
{
    using Types::operator<<;

    os << "   Attempt " << attempt << ":  " << marbleIdsPair.first << "  "
       << comparisonResult << " " << marbleIdsPair.second << '\n';
}


void Taskmaster::logPlayEnding(const Types::Id guessedMarbleId,
                               std::ostream&   os) const
{
    os << std::string(90, '-') << "\nTaskmaster: Player guessed id is "
       << guessedMarbleId << ".\n"
       << std::string(90, '=') << '\n';
}

} // namespace SillyProjects