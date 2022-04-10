#ifndef LOGICALPLAYER_HPP
#define LOGICALPLAYER_HPP

#include <array>
#include <optional>

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

    enum class PlayingStrategy : uint
    {
        firstEqual,
        firstUnqual
    };

    void setMarbleStatus(const Types::MarbleIds& marbleIds,
                         const MarbleStatus      marbleStatus);

    Types::MarbleIds
    getMarbleIdsWithStatus(const MarbleStatus marbleStatus) const;

    std::array<MarbleStatus, Taskmaster::s_maxNumberOfMarbles> m_marblesStatus{
        {MarbleStatus::unknown}};

    std::optional<PlayingStrategy> m_playingStrategy{};
};

} // namespace SillyProjects


#endif