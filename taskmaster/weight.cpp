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

} // namespace Weight
} // namespace SillyProjects
