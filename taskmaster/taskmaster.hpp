#ifndef TASKMASTER_HPP
#define TASKMASTER_HPP

namespace SillyProjects
{

class Taskmaster
{
public:
    static const int s_maxNumberOfMarbles{12};
    static const int s_maxAllowedComparison{3};

    Taskmaster();

private:
    int m_idMarbleWithDifferentWeight;
    int m_numRemainingComparisons;
};

} // namespace SillyProjects

#endif