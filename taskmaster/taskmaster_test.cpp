#include "gtest/gtest.h"

#include "taskmaster.hpp"

namespace SillyProjects
{

TEST(TaskMasterTest, idIsBetweenOneAndMaxNumberOfMarbles)
{
  Taskmaster taskmaster{};
  const auto id = taskmaster.getMarbleId();

  EXPECT_GE(id, 1);
  EXPECT_LE(id, Taskmaster::s_maxNumberOfMarbles);
}

} // namespace SillyProjects