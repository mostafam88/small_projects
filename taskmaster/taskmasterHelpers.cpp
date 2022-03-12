#include <algorithm>

#include "taskmasterHelpers.hpp"

namespace SillyProjects
{

Types::MarbleIdsPair
TaskmasterHelpers::getNonRepetitiveMarbleIds(const Types::MarbleIds& first,
                                             const Types::MarbleIds& second)
{
    const auto firstSortedAndUnique  = getSortedUnique(first);
    const auto secondSortedAndUnique = getSortedUnique(second);

    const auto intersection =
        getIntersection(firstSortedAndUnique, secondSortedAndUnique);

    const auto firstWithNonRepetitiveIds =
        removeIntersection(firstSortedAndUnique, intersection);
    const auto secondWithNonRepetitiveIds =
        removeIntersection(secondSortedAndUnique, intersection);

    return {firstWithNonRepetitiveIds, secondWithNonRepetitiveIds};
}

Types::MarbleIds
TaskmasterHelpers::getSortedUnique(const Types::MarbleIds& marbleIds)
{
    auto sortedAndUnique{marbleIds};
    std::sort(sortedAndUnique.begin(), sortedAndUnique.end());
    const auto lastIt =
        std::unique(sortedAndUnique.begin(), sortedAndUnique.end());
    sortedAndUnique.erase(lastIt, sortedAndUnique.end());

    return sortedAndUnique;
}


Types::MarbleIds
TaskmasterHelpers::getIntersection(const Types::MarbleIds& first,
                                   const Types::MarbleIds& second)
{
    Types::MarbleIds intersection{};
    std::set_intersection(first.begin(), first.end(), second.begin(),
                          second.end(), std::back_inserter(intersection));

    return intersection;
}


Types::MarbleIds
TaskmasterHelpers::removeIntersection(const Types::MarbleIds& marbleIds,
                                      const Types::MarbleIds& intersection)
{
    Types::MarbleIds collectionWithRemovedIntersection{};
    std::set_difference(marbleIds.begin(), marbleIds.end(),
                        intersection.begin(), intersection.end(),
                        std::back_inserter(collectionWithRemovedIntersection));

    return collectionWithRemovedIntersection;
}

} // namespace SillyProjects
