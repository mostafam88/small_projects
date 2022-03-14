#include <iostream>

#include "gtest/gtest.h"

#include "naivePlayer.hpp"
#include "taskmaster.hpp"


namespace SillyProjects
{

TEST(NaivePlayerTest, alwaysSuccess)
{
    std::vector<int> guessedValues{};
    int numRuns{0};
    std::stringbuf irrelevantBuffer;
    std::ostream ignorantOstream(&irrelevantBuffer);
    while (guessedValues.size() < Taskmaster::s_maxNumberOfMarbles)
    {
        ++numRuns;
        SillyProjects::NaivePlayer player{};

        auto       taskmaster = SillyProjects::Taskmaster::create();
        const bool success    = taskmaster.play(player, ignorantOstream);
        EXPECT_TRUE(success);

        const int currentGuess = player.guessUniqueMarbleId();

        const auto foundIt = std::find(guessedValues.begin(), guessedValues.end(), currentGuess);
        if (foundIt == guessedValues.end()) {
            guessedValues.push_back(currentGuess);
        }
    }

    std::cout << '\n' << "             Guessed values: \n             ";
    std::sort(guessedValues.begin(), guessedValues.end());
    std::copy(begin(guessedValues), end(guessedValues), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n' << "             Number of runs: " << numRuns << "\n\n";
}

} // namespace SillyProjects
