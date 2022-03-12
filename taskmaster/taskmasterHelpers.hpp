#ifndef TASKMASTERHELPERS_HPP
#define TASKMASTERHELPERS_HPP

#include <tuple>
#include <vector>

namespace SillyProjects
{

/// A collection of helper functions for Taskmaster
class TaskmasterHelpers
{
public:
    using CollectionType = std::vector<int>;
    using CollectionPair = std::pair<CollectionType, CollectionType>;

    static CollectionPair
    getCollectionsWithNonRepetitiveIds(const CollectionType& first,
                                       const CollectionType& second);

private:
    static CollectionType getSortedUnique(const CollectionType& collection);

    static CollectionType getIntersection(const CollectionType& first,
                                          const CollectionType& second);

    static CollectionType
    removeIntersection(const CollectionType& collection,
                       const CollectionType& intersection);
};

} // namespace SillyProjects

#endif