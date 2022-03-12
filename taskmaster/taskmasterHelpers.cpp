#include <algorithm>

#include "taskmasterHelpers.hpp"

namespace SillyProjects
{

TaskmasterHelpers::CollectionPair
TaskmasterHelpers::getCollectionsWithNonRepetitiveIds(
    const CollectionType& first, const CollectionType& second)
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

TaskmasterHelpers::CollectionType
TaskmasterHelpers::getSortedUnique(const CollectionType& collection)
{
    auto sortedAndUnique{collection};
    std::sort(sortedAndUnique.begin(), sortedAndUnique.end());
    const auto lastIt =
        std::unique(sortedAndUnique.begin(), sortedAndUnique.end());
    sortedAndUnique.erase(lastIt, sortedAndUnique.end());

    return sortedAndUnique;
}


TaskmasterHelpers::CollectionType
TaskmasterHelpers::getIntersection(const CollectionType& first,
                                   const CollectionType& second)
{
    CollectionType intersection{};
    std::set_intersection(first.begin(), first.end(), second.begin(),
                          second.end(), std::back_inserter(intersection));

    return intersection;
}


TaskmasterHelpers::CollectionType
TaskmasterHelpers::removeIntersection(const CollectionType& collection,
                                      const CollectionType& intersection)
{
    CollectionType collectionWithRemovedIntersection{};
    std::set_difference(collection.begin(), collection.end(),
                        intersection.begin(), intersection.end(),
                        std::back_inserter(collectionWithRemovedIntersection));

    return collectionWithRemovedIntersection;
}

} // namespace SillyProjects
