#include <algorithm>
#include <cassert>
#include <set>

#include "randomIdGenerator.hpp"


namespace SillyProjects
{

uint RandomIdGenerator::getSingle(const uint min, const uint max)
{
    std::random_device                  randomDevice;
    std::mt19937                        randomGenerator(randomDevice());
    std::uniform_int_distribution<uint> uniformDistribution(min, max);

    return uniformDistribution(randomGenerator);
}


std::vector<uint> RandomIdGenerator::getMultipleUnique(const uint min,
                                                       const uint max,
                                                       const uint n)
{
    return getMultipleUniqueExcluding(min, max, n, std::vector<uint>{});
}


std::vector<uint> RandomIdGenerator::getMultipleUniqueExcluding(
    const uint min, const uint max, const uint n,
    const std::vector<uint>& excluding)
{
    assert(isValidRequest(min, max, n, excluding));

    std::random_device                  randomDevice;
    std::mt19937                        randomGenerator(randomDevice());
    std::uniform_int_distribution<uint> uniformDistribution(min, max);

    std::vector<uint> result{};
    while (result.size() < n)
    {
        const auto id      = uniformDistribution(randomGenerator);
        const auto isNotIn = [&id](const std::vector<uint>& v) -> bool {
            return (v.end() == std::find(v.begin(), v.end(), id));
        };
        if (isNotIn(result) && isNotIn(excluding))
        {
            result.push_back(id);
        }
    }
    return result;
}

bool RandomIdGenerator::isValidRequest(const uint min, const uint max,
                                       const uint               n,
                                       const std::vector<uint>& excluding)
{
    return true;
}

} // namespace SillyProjects