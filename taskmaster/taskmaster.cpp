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

    std::uniform_int_distribution<int> uni(1, s_maxNumberOfMarbles);
    const int                          id = uni(rng);

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
    os << std::string(90, '=')
       << "\nTaskmaster: Player wants to find marble with id "
       << m_uniqueMarble.m_id << " which is "
       << ((m_uniqueMarble.m_weightComparison ==
            Weight::ComparisonResult::heavier)
               ? "heavier"
               : "lighter")
       << " than other marbles.\n"
       << std::string(90, '-') << '\n';
    for (int i = 1; i <= s_maxAllowedComparisons; ++i)
    {
        const auto currentMarbleIdsPair = player.getMarbleIdsPairToCompare();
        const auto currentComparisonResult =
            compare(currentMarbleIdsPair.first, currentMarbleIdsPair.second);
        print(i, currentMarbleIdsPair, currentComparisonResult, os);
        player.updateStatus(currentComparisonResult);
    }

    const auto guessedMarbleId = player.guessUniqueMarbleId();
    os << std::string(90, '-') << "\nTaskmaster: Player guessed id is "
       << guessedMarbleId << ".\n"
       << std::string(90, '=') << '\n';

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

void Taskmaster::print(const int                      attempt,
                       const Types::MarbleIdsPair&    marbleIdsPair,
                       const Weight::ComparisonResult comparisonResult,
                       std::ostream&                  os)
{
    const auto weightComparisonResultToChar =
        [](const Weight::ComparisonResult comparisonResult) -> char {
        if (comparisonResult == Weight::ComparisonResult::lighter)
        {
            return '<';
        } else if (comparisonResult == Weight::ComparisonResult::equal)
        {
            return '=';
        } else
        {
            assert(comparisonResult == Weight::ComparisonResult::heavier);
            return '>';
        }
    };

    const auto intToString = [](const int i) -> std::string {
        assert((i > 0) && (i < 99));
        std::string s = std::to_string(i);
        return (i > 9) ? s : " " + s;
    };

    const auto intVectorToString =
        [&intToString](const std::vector<int> v) -> std::string {
        assert(v.size() <= 4);
        std::string s;
        for (const auto i : v)
        {
            s += intToString(i) + " ";
        }
        if (v.size() == 4)
        {
            return s;
        } else
        {
            assert(s.size() < 12);
            std::string padding(12 - s.size(), ' ');
            return s + padding;
        }
    };

    os << "   Attempt " << attempt << ":  {"
       << intVectorToString(marbleIdsPair.first) << "} "
       << weightComparisonResultToChar(comparisonResult) << " {"
       << intVectorToString(marbleIdsPair.second) << "}\n";
}

} // namespace SillyProjects