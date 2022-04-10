#ifndef TYPES_HPP
#define TYPES_HPP

#include <ostream>
#include <tuple>
#include <vector>

#include "weight.hpp"

namespace SillyProjects
{
namespace Types
{

using Id            = uint;
using MarbleIds     = std::vector<Id>;
using MarbleIdsPair = std::pair<MarbleIds, MarbleIds>;

std::ostream& operator<<(std::ostream& os, const Types::MarbleIds& MarbleIds);

struct MarbleIdsPairAndComparisonResult
{
    MarbleIdsPairAndComparisonResult(
        const MarbleIdsPair&           marbleIdsPair,
        const Weight::ComparisonResult comparisonResult);

    const MarbleIdsPair            m_marbleIdsPair;
    const Weight::ComparisonResult m_comparisonResult;
};

} // namespace Types
} // namespace SillyProjects

#endif