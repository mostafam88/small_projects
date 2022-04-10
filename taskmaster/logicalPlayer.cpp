#include <algorithm>
#include <random>

#include "logicalPlayer.hpp"
#include "taskmaster.hpp"


namespace SillyProjects
{

Types::MarbleIdsPair LogicalPlayer::getFirstMarbleIdsPairToCompare() const
{
    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device                 rd;
    std::mt19937                       rng(rd());
    std::uniform_int_distribution<int> uni(1, Taskmaster::s_maxNumberOfMarbles);

    Types::MarbleIds first{};
    Types::MarbleIds second{};
    while ((first.size() < 4))
    {
        const int  id = uni(rng);
        const bool isNew =
            (first.end() == std::find(first.begin(), first.end(), id));
        if (isNew)
        {
            first.push_back(id);
        }
    }

    while (second.size() < 4)
    {
        const int  id = uni(rng);
        const bool isNew =
            (first.end() == std::find(first.begin(), first.end(), id)) &&
            (second.end() == std::find(second.begin(), second.end(), id));
        if (isNew)
        {
            second.push_back(id);
        }
    }

    std::sort(first.begin(), first.end());
    std::sort(first.begin(), first.end());

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
}


int LogicalPlayer::getUniqueMarbleId() const
{
    return -1;
}

} // namespace SillyProjects