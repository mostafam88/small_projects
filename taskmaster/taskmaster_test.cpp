#include "gtest/gtest.h"

#include "taskmaster.hpp"

namespace SillyProjects
{

TEST(TaskMasterTest, idIsBetweenOneAndMaxNumberOfMarbles)
{
    Taskmaster taskmaster{};
    const auto marble = taskmaster.getMarble();

    EXPECT_GE(marble.m_id, 1);
    EXPECT_LE(marble.m_id, Taskmaster::s_maxNumberOfMarbles);
}

TEST(TaskMasterTest, weightComparisonIsEitherHeavierOrLighter)
{
    Taskmaster taskmaster{};
    const auto marble = taskmaster.getMarble();

    EXPECT_TRUE(marble.m_weightComparison == WeightComparisonResult::heavier ||
                marble.m_weightComparison == WeightComparisonResult::lighter);
}

TEST(TaskMasterTest, isItReallyUniformRandom)
{
    std::array<int, Taskmaster::s_maxNumberOfMarbles> ids{};
    std::array<int, 2>                                weightDiff{};

    const int numberOfEvaluations{10000};

    for (int i = 0; i < numberOfEvaluations; ++i)
    {
        SillyProjects::Taskmaster taskmaster{};
        const auto                marble = taskmaster.getMarble();

        ASSERT_GE(marble.m_id, 1);
        ASSERT_LE(marble.m_id, Taskmaster::s_maxNumberOfMarbles);
        ++ids[marble.m_id - 1];

        if (marble.m_weightComparison ==
            SillyProjects::WeightComparisonResult::heavier)
        {
            ++weightDiff[0];
        } else
        {
            ASSERT_TRUE(marble.m_weightComparison ==
                        WeightComparisonResult::lighter);
            ++weightDiff[1];
        }
    }

    const auto expectedProbability =
        1.0F / float(Taskmaster::s_maxNumberOfMarbles);

    const auto tolerance = 0.1F * expectedProbability;
    const auto probabilityIsCloseToExpected =
        [&expectedProbability, &numberOfEvaluations,
         &tolerance](const int id) -> void {
        const auto probability = id / float(numberOfEvaluations);
        EXPECT_NEAR(probability, expectedProbability, tolerance);
    };
    std::for_each(ids.begin(), ids.end(), probabilityIsCloseToExpected);

    const auto  binaryExpectedProbability{0.5F};
    const float binaryTolerance{0.05F};
    EXPECT_NEAR(weightDiff[0] / float(numberOfEvaluations),
                binaryExpectedProbability, binaryTolerance);
    EXPECT_NEAR(weightDiff[1] / float(numberOfEvaluations),
                binaryExpectedProbability, binaryTolerance);
}

} // namespace SillyProjects