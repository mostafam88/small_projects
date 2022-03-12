#include "gtest/gtest.h"

#include "weight.hpp"


namespace SillyProjects
{
namespace Weight
{

TEST(WeightTest, OppositeOfHeavier)
{
    const auto result = oppositeOf(ComparisonResult::heavier);
    EXPECT_EQ(result, ComparisonResult::lighter);
}

TEST(WeightTest, OppositeOfLighter)
{
    const auto result = oppositeOf(ComparisonResult::lighter);
    EXPECT_EQ(result, ComparisonResult::heavier);
}

TEST(WeightDeathTest, OppositeOfEqual)
{
    EXPECT_DEATH(oppositeOf(ComparisonResult::equal), "");
}

} // namespace Weight
} // namespace SillyProjects
