#include "gtest/gtest.h"

#include "taskmasterHelpers.hpp"

namespace SillyProjects
{

namespace PrivateTaskMasterHelperTestHelpers
{
void testGetNonRepetitiveMarbleIds(const Types::MarbleIds& first,
                                   const Types::MarbleIds& second,
                                   const Types::MarbleIds& resultFirst,
                                   const Types::MarbleIds& resultsSecond);
}

TEST(TaskMasterHelperTest, GetNonRepetitiveMarbleIds_firstHasRepetitiveIds)
{
    const Types::MarbleIds first        = {2, 2};
    const Types::MarbleIds second       = {4, 5};
    const Types::MarbleIds resultFirst  = {2};
    const Types::MarbleIds resultSecond = {4, 5};

    PrivateTaskMasterHelperTestHelpers::testGetNonRepetitiveMarbleIds(
        first, second, resultFirst, resultSecond);
}

TEST(TaskMasterHelperTest, GetNonRepetitiveMarbleIds_secondHasRepetitiveIds)
{
    const Types::MarbleIds first        = {3, 1, 2};
    const Types::MarbleIds second       = {11, 10, 11};
    const Types::MarbleIds resultFirst  = {1, 2, 3};
    const Types::MarbleIds resultSecond = {10, 11};

    PrivateTaskMasterHelperTestHelpers::testGetNonRepetitiveMarbleIds(
        first, second, resultFirst, resultSecond);
}

TEST(TaskMasterHelperTest,
     GetNonRepetitiveMarbleIds_firstAndSecondShareRepetitiveId)
{
    const Types::MarbleIds first        = {2, 3, 1};
    const Types::MarbleIds second       = {3, 4, 5};
    const Types::MarbleIds resultFirst  = {1, 2};
    const Types::MarbleIds resultSecond = {4, 5};

    PrivateTaskMasterHelperTestHelpers::testGetNonRepetitiveMarbleIds(
        first, second, resultFirst, resultSecond);
}

TEST(TaskMasterHelperTest,
     GetNonRepetitiveMarbleIds_firstHasRepetitiveIdsAndSharesThemWithSecond)
{
    const Types::MarbleIds first        = {2, 3, 2};
    const Types::MarbleIds second       = {2, 5, 3};
    const Types::MarbleIds resultFirst  = {};
    const Types::MarbleIds resultSecond = {5};

    PrivateTaskMasterHelperTestHelpers::testGetNonRepetitiveMarbleIds(
        first, second, resultFirst, resultSecond);
}

TEST(TaskMasterHelperTest,
     GetNonRepetitiveMarbleIds_secondHasRepetitiveIdsAndSharesThemWithFirst)
{
    const Types::MarbleIds first        = {9, 8, 7};
    const Types::MarbleIds second       = {8, 10, 8};
    const Types::MarbleIds resultFirst  = {7, 9};
    const Types::MarbleIds resultSecond = {10};

    PrivateTaskMasterHelperTestHelpers::testGetNonRepetitiveMarbleIds(
        first, second, resultFirst, resultSecond);
}


TEST(TaskMasterHelperTest, GetNonRepetitiveMarbleIds_justUnsorted)
{
    const Types::MarbleIds first        = {7, 10, 6, 5};
    const Types::MarbleIds second       = {4, 3, 12, 8, 1};
    const Types::MarbleIds resultFirst  = {5, 6, 7, 10};
    const Types::MarbleIds resultSecond = {1, 3, 4, 8, 12};

    PrivateTaskMasterHelperTestHelpers::testGetNonRepetitiveMarbleIds(
        first, second, resultFirst, resultSecond);
}


namespace PrivateTaskMasterHelperTestHelpers
{

void testGetNonRepetitiveMarbleIds(const Types::MarbleIds& first,
                                   const Types::MarbleIds& second,
                                   const Types::MarbleIds& resultFirst,
                                   const Types::MarbleIds& resultsSecond)
{
    const auto result =
        TaskmasterHelpers::getNonRepetitiveMarbleIds(first, second);
    EXPECT_EQ(result.first, resultFirst);
    EXPECT_EQ(result.second, resultsSecond);
}

} // namespace PrivateTaskMasterHelperTestHelpers

} // namespace SillyProjects