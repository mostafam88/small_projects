#ifndef TASKMASTER_HPP
#define TASKMASTER_HPP

#include <optional>
#include <vector>

#include "marble.hpp"
#include "types.hpp"

namespace SillyProjects
{

class Taskmaster
{
public:
    static const int s_maxNumberOfMarbles{12};
    static const int s_maxAllowedComparisons{3};

    /// Creates a Taskmaster!
    ///
    /// Creates a marble whose id is randomly chosen between 1 and
    /// #s_maxNumberOfMarbles, and its weight is either
    /// WeightComparisonResult::lighter or WeightComparisonResult::heavier than
    /// other marbles. Then creates a Taskmaster by passing the randomly
    /// generated marble.
    ///
    /// \returns The generated Taskmaster.
    static Taskmaster create();

    /// Compares weight of marbles whose ids are found in \p first and
    /// \p second.
    ///
    /// \note Repetitive ids are removed!
    /// \note The weight difference of the unique marble is never greater than
    ///       twice or smaller than half of the other marbles, i.e. the result
    ///       of comparison of the different sizes would tend towards collection
    ///       with more marbles.
    ///
    /// \returns - WeightComparisonResult::equal if marbles have equal weight,
    ///          - WeightComparisonResult::lighter if marbles in \p first are
    ///          lighter than those in \p second, and
    ///          - WeightComparisonResult::heavier if marbles in \p first are
    ///          heavier that those in \p second.
    WeightComparisonResult compare(const std::vector<int>& first,
                                   const std::vector<int>& second);

    /// \note Only for testing; therefore #m_numRemainingComparisons is set to
    /// zero to prevent continuing the game.
    ///
    /// \returns #m_uniqueMarble.
    Marble getMarble();

private:
    /// Assigns \p uniqueMarble to #m_uniqueMarble and sets
    /// #m_numRemainingComparisons to #s_maxAllowedComparisons.
    Taskmaster(const Marble& uniqueMarble);

    /// \returns - an initialized optional with WeightComparisonResult::equal if
    ///          both marble ids are empty.
    ///          - an initialized optional with WeightComparisonResult::lighter
    ///          if size of first is smaller than second.
    ///          - an initialized optional with WeightComparisonResult::lighter
    ///          if size of first is smaller than second.
    ///          - a non-initialized optional otherwise.
    std::optional<WeightComparisonResult>
    compareSizes(const Types::MarbleIdsPair& marbleIdsPair);

    /// \pre Given ids have equal size and no id is repeated among them.
    ///
    /// \returns - m_weightComparison of #m_uniqueMarble if its id is found in
    ///          the first list.
    ///          - opposite of m_weightComparison of #m_uniqueMarble if its id
    ///          is found in the second list.
    ///          - WeightComparisonResult::equal if id of #m_uniqueMarble is not
    ///          found in any of the lists.
    WeightComparisonResult
    safeCompare(const Types::MarbleIdsPair& marbleIdsPair);

    const Marble m_uniqueMarble;
    int          m_numRemainingComparisons;
};

} // namespace SillyProjects

#endif