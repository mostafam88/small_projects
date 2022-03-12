#ifndef TASKMASTERHELPERS_HPP
#define TASKMASTERHELPERS_HPP

#include <tuple>
#include <vector>

#include "types.hpp"

namespace SillyProjects
{

/// A collection of helper functions for Taskmaster
class TaskmasterHelpers
{
public:
    static Types::MarbleIdsPair
    getNonRepetitiveMarbleIds(const Types::MarbleIds& first,
                              const Types::MarbleIds& second);

private:
    static Types::MarbleIds getSortedUnique(const Types::MarbleIds& marbleIds);

    static Types::MarbleIds getIntersection(const Types::MarbleIds& first,
                                            const Types::MarbleIds& second);

    static Types::MarbleIds
    removeIntersection(const Types::MarbleIds& marbleIds,
                       const Types::MarbleIds& intersection);
};

} // namespace SillyProjects

#endif