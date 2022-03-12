#include "gtest/gtest.h"

#include "taskmasterHelpers.hpp"

namespace SillyProjects
{

using CollectionType = TaskmasterHelpers::CollectionType;

namespace PrivateTaskMasterHelperTestHelpers
{
void testGetCollectionsWithNonRepetitiveIds(
    const CollectionType& first, const CollectionType& second,
    const CollectionType& resultFirst, const CollectionType& resultsSecond);
}

TEST(TaskMasterHelperTest,
     GetCollectionsWithNonRepetitiveIds_firstHasRepetitiveIds)
{
    const CollectionType first        = {2, 2};
    const CollectionType second       = {4, 5};
    const CollectionType resultFirst  = {2};
    const CollectionType resultSecond = {4, 5};

    PrivateTaskMasterHelperTestHelpers::testGetCollectionsWithNonRepetitiveIds(
        first, second, resultFirst, resultSecond);
}

TEST(TaskMasterHelperTest,
     GetCollectionsWithNonRepetitiveIds_secondHasRepetitiveIds)
{
    const CollectionType first        = {3, 1, 2};
    const CollectionType second       = {11, 10, 11};
    const CollectionType resultFirst  = {1, 2, 3};
    const CollectionType resultSecond = {10, 11};

    PrivateTaskMasterHelperTestHelpers::testGetCollectionsWithNonRepetitiveIds(
        first, second, resultFirst, resultSecond);
}

TEST(TaskMasterHelperTest,
     GetCollectionsWithNonRepetitiveIds_firstAndSecondShareRepetitiveId)
{
    const CollectionType first        = {2, 3, 1};
    const CollectionType second       = {3, 4, 5};
    const CollectionType resultFirst  = {1, 2};
    const CollectionType resultSecond = {4, 5};

    PrivateTaskMasterHelperTestHelpers::testGetCollectionsWithNonRepetitiveIds(
        first, second, resultFirst, resultSecond);
}

TEST(
    TaskMasterHelperTest,
    GetCollectionsWithNonRepetitiveIds_firstHasRepetitiveIdsAndSharesThemWithSecond)
{
    const CollectionType first        = {2, 3, 2};
    const CollectionType second       = {2, 5, 3};
    const CollectionType resultFirst  = {};
    const CollectionType resultSecond = {5};

    PrivateTaskMasterHelperTestHelpers::testGetCollectionsWithNonRepetitiveIds(
        first, second, resultFirst, resultSecond);
}

TEST(
    TaskMasterHelperTest,
    GetCollectionsWithNonRepetitiveIds_secondHasRepetitiveIdsAndSharesThemWithFirst)
{
    const CollectionType first        = {9, 8, 7};
    const CollectionType second       = {8, 10, 8};
    const CollectionType resultFirst  = {7, 9};
    const CollectionType resultSecond = {10};

    PrivateTaskMasterHelperTestHelpers::testGetCollectionsWithNonRepetitiveIds(
        first, second, resultFirst, resultSecond);
}


TEST(TaskMasterHelperTest, GetCollectionsWithNonRepetitiveIds_justUnsorted)
{
    const CollectionType first        = {7, 10, 6, 5};
    const CollectionType second       = {4, 3, 12, 8, 1};
    const CollectionType resultFirst  = {5, 6, 7, 10};
    const CollectionType resultSecond = {1, 3, 4, 8, 12};

    PrivateTaskMasterHelperTestHelpers::testGetCollectionsWithNonRepetitiveIds(
        first, second, resultFirst, resultSecond);
}


namespace PrivateTaskMasterHelperTestHelpers
{

void testGetCollectionsWithNonRepetitiveIds(const CollectionType& first,
                                            const CollectionType& second,
                                            const CollectionType& resultFirst,
                                            const CollectionType& resultsSecond)
{
    const auto result =
        TaskmasterHelpers::getCollectionsWithNonRepetitiveIds(first, second);
    EXPECT_EQ(result.first, resultFirst);
    EXPECT_EQ(result.second, resultsSecond);
}

} // namespace PrivateTaskMasterHelperTestHelpers

} // namespace SillyProjects