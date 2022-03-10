#ifndef TASKMASTER_HPP
#define TASKMASTER_HPP

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
    int                    m_id{0};
    WeightComparisonResult m_weightComparison{WeightComparisonResult::equal};
};

class Taskmaster
{
public:
    static const int s_maxNumberOfMarbles{12};
    static const int s_maxAllowedComparison{3};

    /// Default Constructor.
    ///
    /// Assigns a random number between 1 and #s_maxNumberOfMarbles to
    /// m_id of #m_marbleWithDifferentWeight and sets #m_numRemainingComparisons
    /// to #s_maxAllowedComparison.
    Taskmaster();

    /// \note Only for testing; therefore #m_numRemainingComparisons is set to
    /// zero to prevent continuing the game.
    ///
    /// \returns #m_marbleWithDifferentWeight.
    Marble getMarble();

private:
    Marble m_marbleWithDifferentWeight;
    int    m_numRemainingComparisons;
};

} // namespace SillyProjects

#endif