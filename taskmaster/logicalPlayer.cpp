#include <algorithm>
#include <assert.h>

#include "logicalPlayer.hpp"
#include "randomIdGenerator.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair LogicalPlayer::getFirstMarbleIdsPairToCompare() const
{
    const uint firstGuessSize{4};

    return createMarbleIdsPairFromUnknownWithSize(firstGuessSize);
}


Types::MarbleIdsPair LogicalPlayer::getSecondMarbleIdsPairToCompare() const
{
    assert(m_playingStrategy.has_value());
    if (m_playingStrategy.value() == PlayingStrategy::firstEqual)
    {
        return createMarbleIdsPairFromUnknownWithSize(2);
    } else
    {
        return Types::MarbleIdsPair{};
    }
}

Types::MarbleIdsPair LogicalPlayer::createMarbleIdsPairFromUnknownWithSize(
    const uint desiredMarbleIdsSize) const
{
    assert(desiredMarbleIdsSize > 0);
    const uint minIndex{0U};
    const uint maxIndex{2U * desiredMarbleIdsSize - 1U};

    const auto notTestedIds = getMarbleIdsWithStatus(MarbleStatus::unknown);
    assert(notTestedIds.size() > maxIndex);

    const auto firstIndices = RandomIdGenerator::getMultipleUnique(
        minIndex, maxIndex, desiredMarbleIdsSize);
    const auto secondIndices = RandomIdGenerator::getMultipleUniqueExcluding(
        minIndex, maxIndex, desiredMarbleIdsSize, firstIndices);

    const auto transformer = [&notTestedIds](const int i) -> int {
        return notTestedIds[i];
    };

    Types::MarbleIds first{};
    Types::MarbleIds second{};

    std::transform(firstIndices.begin(), firstIndices.end(),
                   std::back_inserter(first), transformer);
    std::transform(secondIndices.begin(), secondIndices.end(),
                   std::back_inserter(second), transformer);

    return Types::MarbleIdsPair{first, second};
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
                      assert((id >= 1) && (id <= 12));
                      m_marblesStatus[id - 1] = marbleStatus;
                  });
}


Types::MarbleIds
LogicalPlayer::getMarbleIdsWithStatus(const MarbleStatus marbleStatus) const
{
    Types::MarbleIds result{};
    for (Types::Id i = 0; i < Taskmaster::s_maxNumberOfMarbles; ++i)
    {
        if (m_marblesStatus[i] == marbleStatus)
        {
            result.push_back(i + 1);
        }
    }
    return result;
}

Types::Id LogicalPlayer::getUniqueMarbleId() const
{
    return 999;
}

} // namespace SillyProjects