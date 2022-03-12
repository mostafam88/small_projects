#ifndef WEIGHT_HPP
#define WEIGHT_HPP


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

} // namespace Weight
} // namespace SillyProjects

#endif