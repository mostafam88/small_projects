#ifndef WEIGHT_HPP
#define WEIGHT_HPP

#include<assert.h>
#include<ostream>


namespace SillyProjects
{
namespace Weight
{

enum class ComparisonResult : int
{
    lighter,
    equal,
    heavier
};

ComparisonResult oppositeOf(const ComparisonResult given);

std::ostream& operator<<(std::ostream&          os,
                         const ComparisonResult comparisonResult);

} // namespace Weight
} // namespace SillyProjects

#endif