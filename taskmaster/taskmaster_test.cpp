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

} // namespace SillyProjects