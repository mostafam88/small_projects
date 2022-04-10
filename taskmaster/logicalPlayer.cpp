#include <algorithm>
#include <random>
#include <set>

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


    std::set<int> first_set{};
    std::set<int> second_set{};
    while ((first_set.size() < 4))
    {
        const int id = uni(rng);
        first_set.insert(id);
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
}


int LogicalPlayer::getUniqueMarbleId() const
{
    return -1;
}

} // namespace SillyProjects