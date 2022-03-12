#ifndef TASKMASTER_HPP
#define TASKMASTER_HPP

#include <vector>


namespace SillyProjects
{

enum class WeightComparisonResult : int
{
    lighter,
    equal,
    heavier
};

struct Marble
{
    Marble(const int id, const WeightComparisonResult weightComparison)
      : m_id{id}
      , m_weightComparison{weightComparison}
    {
    }
    const int                    m_id;
    const WeightComparisonResult m_weightComparison;
};

class Taskmaster
{
public:
    static const int s_maxNumberOfMarbles{12};
    static const int s_maxAllowedComparison{3};

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

    /// Compares weight of marbles ids in \p first and \p second.
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
    /// \returns #m_marbleWithDifferentWeight.
    Marble getMarble();

private:
    /// Assigns \p marbleWithDifferentWeight to #m_marbleWithDifferentWeight
    /// sets #m_numRemainingComparisons to #s_maxAllowedComparison.
    Taskmaster(const Marble& marbleWithDifferentWeight);

    const Marble m_marbleWithDifferentWeight;
    int          m_numRemainingComparisons;
};

} // namespace SillyProjects

#endif