#include <array>

#include "abstractPlayer.hpp"
#include "taskmaster.hpp"


namespace SillyProjects
{

class LogicalPlayer : public AbstractPlayer
{
protected:
    virtual Types::MarbleIdsPair getFirstMarbleIdsPairToCompare() const;

    virtual Types::MarbleIdsPair getSecondMarbleIdsPairToCompare() const;

    virtual Types::MarbleIdsPair getThirdMarbleIdsPairToCompare() const;

    virtual void
    updateStatus(const Types::MarbleIdsPair&    currentAttemptMarbleIds,
                 const Weight::ComparisonResult comparisonResult);

    virtual int getUniqueMarbleId() const;

private:
    enum class MarbleStatus : uint
    {
        unknown,
        lighter,
        equal,
        heavier
    };

    void setMarbleStatus(const Types::MarbleIds& marbleIds,
                         const MarbleStatus      marbleStatus);

    Types::MarbleIds
    getMarbleIdsWithStatus(const MarbleStatus marbleStatus) const;

    std::array<MarbleStatus, Taskmaster::s_maxNumberOfMarbles> m_marblesStatus{
        {MarbleStatus::unknown}};
};

} // namespace SillyProjects