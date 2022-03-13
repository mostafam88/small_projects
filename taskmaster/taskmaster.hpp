#ifndef TASKMASTER_HPP
#define TASKMASTER_HPP

#include <optional>
#include <vector>

#include "marble.hpp"
#include "types.hpp"


namespace SillyProjects
{

class AbstractPlayer;

class Taskmaster
{
public:
    static const int s_maxNumberOfMarbles{12};
    static const int s_maxAllowedComparisons{3};

    /// Creates a Taskmaster!
    ///
    /// Creates a marble whose id is randomly chosen between 1 and
    /// #s_maxNumberOfMarbles, and its weight is either
    /// Weight::ComparisonResult::lighter or Weight::ComparisonResult::heavier
    /// than other marbles. Then creates a Taskmaster by passing the randomly
    /// generated marble.
    ///
    /// \returns The generated Taskmaster.
    static Taskmaster create();

    bool play(AbstractPlayer& player);

private:
    /// Assigns \p uniqueMarble to #m_uniqueMarble.
    Taskmaster(const Marble& uniqueMarble);

    /// Compares weight of marbles whose ids are found in \p first and
    /// \p second.
    ///
    /// \note Repetitive ids are removed!
    /// \note The weight difference of the unique marble is never greater than
    ///       twice or smaller than half of the other marbles, i.e. the result
    ///       of comparison of the different sizes would tend towards collection
    ///       with more marbles.
    ///
    /// \returns - Weight::ComparisonResult::equal if marbles have equal weight,
    ///          - Weight::ComparisonResult::lighter if marbles in \p first are
    ///          lighter than those in \p second, and
    ///          - Weight::ComparisonResult::heavier if marbles in \p first are
    ///          heavier that those in \p second.
    Weight::ComparisonResult compare(const Types::MarbleIds& first,
                                     const Types::MarbleIds& second) const;

    /// \returns - an initialized optional with Weight::ComparisonResult::equal
    /// if
    ///          both marble ids are empty.
    ///          - an initialized optional with
    ///          Weight::ComparisonResult::lighter if size of first is smaller
    ///          than second.
    ///          - an initialized optional with
    ///          Weight::ComparisonResult::lighter if size of first is smaller
    ///          than second.
    ///          - a non-initialized optional otherwise.
    std::optional<Weight::ComparisonResult>
    compareSizes(const Types::MarbleIdsPair& marbleIdsPair) const;

    /// \pre Given ids have equal size and no id is repeated among them.
    ///
    /// \returns - m_weightComparison of #m_uniqueMarble if its id is found in
    ///          the first list.
    ///          - opposite of m_weightComparison of #m_uniqueMarble if its id
    ///          is found in the second list.
    ///          - Weight::ComparisonResult::equal if id of #m_uniqueMarble is
    ///          not found in any of the lists.
    Weight::ComparisonResult
    safeCompare(const Types::MarbleIdsPair& marbleIdsPair) const;

    const Marble m_uniqueMarble;

    friend class TaskmasterDataAccessor;
};

} // namespace SillyProjects

#endif