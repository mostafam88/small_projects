#include <assert.h>

#include "weight.hpp"


namespace SillyProjects
{
namespace Weight
{

ComparisonResult oppositeOf(const ComparisonResult given)
{
    assert((given == ComparisonResult::heavier) ||
           (given == ComparisonResult::lighter));

    return (given == ComparisonResult::heavier) ? ComparisonResult::lighter
                                                : ComparisonResult::heavier;
}

std::ostream& operator<<(std::ostream&          os,
                         const ComparisonResult comparisonResult)
{
    if (comparisonResult == Weight::ComparisonResult::lighter)
    {
        os << '<';
    } else if (comparisonResult == Weight::ComparisonResult::equal)
    {
        os << '=';
    } else
    {
        assert(comparisonResult == Weight::ComparisonResult::heavier);
        os << '>';
    }

    return os;
}

} // namespace Weight
} // namespace SillyProjects
