#ifndef TASKMASTER_HPP
#define TASKMASTER_HPP

namespace SillyProjects
{

class Taskmaster
{
public:
    static const int s_maxNumberOfMarbles{12};
    static const int s_maxAllowedComparison{3};

    /// Default Constructor.
    ///
    /// Assigns a random number between 1 and #s_maxNumberOfMarbles to
    /// #m_idMarbleWithDifferentWeight and sets #m_numRemainingComparisons to
    /// #s_maxAllowedComparison.
    Taskmaster();

    /// \note Only for testing; therefore #m_numRemainingComparisons is set to
    /// zero to prevent continuing the game.
    ///
    /// \returns #m_idMarbleWithDifferentWeight.
    int getMarbleId();

private:
    int m_idMarbleWithDifferentWeight;
    int m_numRemainingComparisons;
};

} // namespace SillyProjects

#endif