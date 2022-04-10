#include <algorithm>
#include <random>
#include <set>

#include "logicalPlayer.hpp"
#include "randomIdGenerator.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair LogicalPlayer::getFirstMarbleIdsPairToCompare() const
{
    const Types::Id idMin{1};
    const Types::Id idMax{Taskmaster::s_maxNumberOfMarbles};
    const uint      guessSize{4};

    const auto first =
        RandomIdGenerator::getMultipleUnique(idMin, idMax, guessSize);
    const auto second = RandomIdGenerator::getMultipleUniqueExcluding(
        idMin, idMax, guessSize, first);

    return Types::MarbleIdsPair{first, second};
}

    while (second_set.size() < 4)
    {
        const int  id    = uni(rng);
        const bool isNew = (first_set.find(id) == first_set.end());
        if (isNew)
        {
            second_set.insert(id);
        }
    }


    Types::MarbleIds first{};
    Types::MarbleIds second{};

    std::copy(first_set.begin(), first_set.end(), std::back_inserter(first));
    std::copy(second_set.begin(), second_set.end(), std::back_inserter(second));

    return Types::MarbleIdsPair{first, second};
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
    if (comparisonResult == Weight::ComparisonResult::equal)
    {
        setMarbleStatus(currentAttemptMarbleIds.first, MarbleStatus::equal);
        setMarbleStatus(currentAttemptMarbleIds.second, MarbleStatus::equal);
    } else if (comparisonResult == Weight::ComparisonResult::heavier)
    {
        setMarbleStatus(currentAttemptMarbleIds.first, MarbleStatus::heavier);
        setMarbleStatus(currentAttemptMarbleIds.second, MarbleStatus::lighter);
        const auto rest = getMarbleIdsWithStatus(MarbleStatus::unknown);
        setMarbleStatus(rest, MarbleStatus::equal);
    } else
    {
        updateStatus(std::make_pair(currentAttemptMarbleIds.second,
                                    currentAttemptMarbleIds.first),
                     Weight::ComparisonResult::heavier);
    }

    if (!m_playingStrategy.has_value())
    {
        m_playingStrategy =
            (comparisonResult == Weight::ComparisonResult::equal)
                ? PlayingStrategy::firstEqual
                : PlayingStrategy::firstUnqual;
    }
}


void LogicalPlayer::setMarbleStatus(const Types::MarbleIds& marbleIds,
                                    const MarbleStatus      marbleStatus)
{
    std::for_each(marbleIds.begin(), marbleIds.end(),
                  [this, &marbleStatus](const int id) -> void {
                      m_marblesStatus[id] = marbleStatus;
                  });
}


Types::MarbleIds
LogicalPlayer::getMarbleIdsWithStatus(const MarbleStatus marbleStatus) const
{
    Types::MarbleIds result{};
    for (int i = 0; i < Taskmaster::s_maxNumberOfMarbles; ++i)
    {
        if (m_marblesStatus[i] == marbleStatus)
        {
            result.push_back(i);
        }
    }
    return result;
}

Types::Id LogicalPlayer::getUniqueMarbleId() const
{
    return 999;
}

} // namespace SillyProjects