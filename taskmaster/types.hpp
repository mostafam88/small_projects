#ifndef TYPES_HPP
#define TYPES_HPP

#include <tuple>
#include <vector>

#include "weight.hpp"

namespace SillyProjects
{
namespace Types
{

using MarbleIds     = std::vector<int>;
using MarbleIdsPair = std::pair<MarbleIds, MarbleIds>;

struct MarbleIdsPairAndComparisonResult
{
    MarbleIdsPairAndComparisonResult(
        const MarbleIdsPair&           marbleIdsPair,
        const Weight::ComparisonResult comparisonResult)
      : m_marbleIdsPair{marbleIdsPair}
      , m_comparisonResult{comparisonResult}
    {
    }

    const MarbleIdsPair            m_marbleIdsPair;
    const Weight::ComparisonResult m_comparisonResult;
};

} // namespace Types
} // namespace SillyProjects

#endif