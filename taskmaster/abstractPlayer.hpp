#ifndef ABSTRACTPLAYER_HPP
#define ABSTRACTPLAYER_HPP

#include <optional>

#include "marble.hpp"
#include "types.hpp"
#include "weight.hpp"


namespace SillyProjects
{

/// Abstract class for players to ensure correct order of request/updates.
class AbstractPlayer
{
public:
    /// Asserts that #m_currentAttemptMarbleIds does not have a value, i.e. the
    /// order of calls are as expected. Then saves the return value of
    /// #getMarbleIdsPairToCompare by passing #m_numberOfCompletedAttempts, and
    /// returns its value.
    ///
    /// \returns The value of updated #m_numberOfCompletedAttempts.
    Types::MarbleIdsPair getMarbleIdsPairToCompare();

    /// Asserts that #m_currentAttemptMarbleIds has a value, i.e. the
    /// order of calls are as expected. Calls abstract #updateStatus by passing
    /// value of #m_currentAttemptMarbleIds and \p comparisonResult. Then resest
    /// #m_currentAttemptMarbleIds and adds #m_numberOfCompletedAttempts by one.
    void updateStatus(const Weight::ComparisonResult comparisonResult);

    // Asserts that #m_numberOfCompletedAttempts is 3,
    // #getMarbleIdsPairToCompare and #updateStatus are called sufficient times,
    // and calls abstract function #getUniqueMarbleId.
    Types::Id guessUniqueMarbleId() const;

protected:
    virtual Types::MarbleIdsPair getFirstMarbleIdsPairToCompare() const  = 0;
    virtual Types::MarbleIdsPair getSecondMarbleIdsPairToCompare() const = 0;
    virtual Types::MarbleIdsPair getThirdMarbleIdsPairToCompare() const  = 0;

    virtual void
    updateStatus(const Types::MarbleIdsPair&    currentAttemptMarbleIds,
                 const Weight::ComparisonResult comparisonResult) = 0;

    virtual Types::Id getUniqueMarbleId() const = 0;

private:
    /// Returns the return value of proper abstract getter depending on
    /// \p numberOfCompletedAttempts.
    Types::MarbleIdsPair
    getMarbleIdsPairToCompare(const int numberOfCompletedAttempts) const;

    std::optional<Types::MarbleIdsPair> m_currentAttemptMarbleIds{};
    int                                 m_numberOfCompletedAttempts{0};
};

} // namespace SillyProjects

#endif