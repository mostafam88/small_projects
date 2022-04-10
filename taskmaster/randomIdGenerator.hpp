#ifndef RANDOMIDGENERATOR_HPP
#define RANDOMIDGENERATOR_HPP

#include <random>


namespace SillyProjects
{

// A class provide a clean interface for generating uniformly distributed random
// integer values in the desired range.
// https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
class RandomIdGenerator
{
public:
    static uint getSingle(const uint min, const uint max);

    static std::vector<uint> getMultipleUnique(const uint min, const uint max,
                                               const uint n);

    static std::vector<uint>
    getMultipleUniqueExcluding(const uint min, const uint max, const uint n,
                               const std::vector<uint>& excluding);

    static bool isValidRequest(const uint min, const uint max, const uint n,
                               const std::vector<uint>& excluding);
};

} // namespace SillyProjects


#endif