#include "types.hpp"

namespace SillyProjects
{
namespace Types
{

std::ostream& operator<<(std::ostream& os, const Types::MarbleIds& MarbleIds)
{
    const auto intToString = [](const int i) -> std::string {
        assert((i > 0) && (i < 99));
        std::string s = std::to_string(i);
        return (i > 9) ? s : " " + s;
    };

    os << "{";
    for (const auto i : MarbleIds)
    {
        os << intToString(i) << " ";
    }
    if (MarbleIds.size() < 4)
    {
        std::string padding(12 - 3 * MarbleIds.size(), ' ');
        os << padding;
    }
    os << "}";

    return os;
}

MarbleIdsPairAndComparisonResult::MarbleIdsPairAndComparisonResult(
    const MarbleIdsPair&           marbleIdsPair,
    const Weight::ComparisonResult comparisonResult)
  : m_marbleIdsPair{marbleIdsPair}
  , m_comparisonResult{comparisonResult}
{
}

} // namespace Types
} // namespace SillyProjects
