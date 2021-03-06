#include "gtest/gtest.h"

#include <vector>

#include "taskmaster.hpp"


namespace SillyProjects
{

namespace TestHelpers
{

Types::MarbleIds
createVectorWithGivenSizeIncludingUniqueId(const std::size_t size,
                                           const Types::Id   includingId);

Types::MarbleIds createVectorWithGivenSizeExcludingUniqueIds(
    const std::size_t size, const Types::MarbleIds& excludingIds);

} // namespace TestHelpers

class TaskmasterDataAccessor
{
public:
    static Marble getUniqueMarble(const Taskmaster& taskmaster)
    {
        return taskmaster.m_uniqueMarble;
    }

    static Weight::ComparisonResult compare(const Taskmaster&      taskmaster,
                                            const Types::MarbleIds first,
                                            const Types::MarbleIds second)
    {
        return taskmaster.compare(first, second);
    }
};

TEST(TaskmasterTest, idIsBetweenOneAndMaxNumberOfMarbles)
{
    auto       taskmaster = Taskmaster::create();
    const auto marble     = TaskmasterDataAccessor::getUniqueMarble(taskmaster);

    EXPECT_GE(marble.m_id, 1);
    EXPECT_LE(marble.m_id, Taskmaster::s_maxNumberOfMarbles);
}

TEST(TaskmasterTest, weightComparisonIsEitherHeavierOrLighter)
{
    auto       taskmaster = Taskmaster::create();
    const auto marble     = TaskmasterDataAccessor::getUniqueMarble(taskmaster);

    EXPECT_TRUE(marble.m_weightComparison ==
                    Weight::ComparisonResult::heavier ||
                marble.m_weightComparison == Weight::ComparisonResult::lighter);
}

TEST(TaskmasterTest, isItReallyUniformRandom)
{
    std::array<int, Taskmaster::s_maxNumberOfMarbles> ids{};
    std::array<int, 2>                                weightDiff{};

    const int numberOfEvaluations{10000};

    for (int i = 0; i < numberOfEvaluations; ++i)
    {
        auto       taskmaster = Taskmaster::create();
        const auto marble = TaskmasterDataAccessor::getUniqueMarble(taskmaster);

        ASSERT_GE(marble.m_id, 1);
        ASSERT_LE(marble.m_id, Taskmaster::s_maxNumberOfMarbles);
        ++ids[marble.m_id - 1];

        if (marble.m_weightComparison == Weight::ComparisonResult::heavier)
        {
            ++weightDiff[0];
        } else
        {
            ASSERT_TRUE(marble.m_weightComparison ==
                        Weight::ComparisonResult::lighter);
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

TEST(TaskmasterTest, compareWithDifferentSizes)
{
    {
        SCOPED_TRACE("size of first is greater than second!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {1, 2}, {4, 5, 6});
        EXPECT_EQ(result, Weight::ComparisonResult::lighter);
    }
    {
        SCOPED_TRACE("size of first is smaller than second!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {1, 2, 3}, {10, 11});
        EXPECT_EQ(result, Weight::ComparisonResult::heavier);
    }
    {
        SCOPED_TRACE("first is empty!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {}, {4, 5, 6});
        EXPECT_EQ(result, Weight::ComparisonResult::lighter);
    }
    {
        SCOPED_TRACE("second is empty!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {1, 2, 3}, {});
        EXPECT_EQ(result, Weight::ComparisonResult::heavier);
    }
}

TEST(TaskmasterTest, compareWithEmpty)
{
    auto taskmaster = Taskmaster::create();

    const auto result = TaskmasterDataAccessor::compare(taskmaster, {}, {});
    EXPECT_EQ(result, Weight::ComparisonResult::equal);
}

TEST(TaskmasterTest, compareWithRepetitiveIds)
{
    {
        SCOPED_TRACE("first has repetitive ids!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {2, 2}, {4, 5});
        EXPECT_EQ(result, Weight::ComparisonResult::lighter);
    }
    {
        SCOPED_TRACE("second has repetitive ids!");
        auto       taskmaster = Taskmaster::create();
        const auto result     = TaskmasterDataAccessor::compare(
                taskmaster, {1, 2, 3}, {11, 10, 11});
        EXPECT_EQ(result, Weight::ComparisonResult::heavier);
    }
    {
        SCOPED_TRACE("first and second share a repetitive id!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {1, 2, 3}, {3, 4, 5});
        const auto expectedResult =
            TaskmasterDataAccessor::compare(taskmaster, {1, 2}, {4, 5});
        EXPECT_EQ(result, expectedResult);
    }
    {
        SCOPED_TRACE("first has repetitive ids and shares them with second!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {2, 3, 2}, {2, 5, 3});
        EXPECT_EQ(result, Weight::ComparisonResult::lighter);
    }
    {
        SCOPED_TRACE("second has repetitive ids and shares them with first!");
        auto       taskmaster = Taskmaster::create();
        const auto result =
            TaskmasterDataAccessor::compare(taskmaster, {9, 8, 7}, {8, 10, 8});
        EXPECT_EQ(result, Weight::ComparisonResult::heavier);
    }
}

TEST(TaskmasterTest, compareWithUniqueMarbleInOneOfTheCollections)
{
    for (int i = 1; i <= 6; ++i)
    {
        SCOPED_TRACE(i);
        auto       taskmaster = Taskmaster::create();
        const auto uniqueMarble =
            TaskmasterDataAccessor::getUniqueMarble(taskmaster);
        const auto uniqueMarbleId = uniqueMarble.m_id;

        const auto expectedResultFirstContainingUniqMarble =
            uniqueMarble.m_weightComparison;
        const auto expectedResultSecondContainingUniqMarble =
            Weight::oppositeOf(uniqueMarble.m_weightComparison);

        const auto containingUniqMarble =
            TestHelpers::createVectorWithGivenSizeIncludingUniqueId(
                i, uniqueMarbleId);
        const auto notContainingUniqueMarble =
            TestHelpers::createVectorWithGivenSizeExcludingUniqueIds(
                i, containingUniqMarble);

        const auto resultFirstContainingUniqMarble =
            TaskmasterDataAccessor::compare(taskmaster, containingUniqMarble,
                                            notContainingUniqueMarble);
        EXPECT_EQ(resultFirstContainingUniqMarble,
                  expectedResultFirstContainingUniqMarble);

        const auto resultSecondContainingUniqMarble =
            TaskmasterDataAccessor::compare(
                taskmaster, notContainingUniqueMarble, containingUniqMarble);
        EXPECT_EQ(resultSecondContainingUniqMarble,
                  expectedResultSecondContainingUniqMarble);
    }
}

namespace TestHelpers
{

Types::MarbleIds
createVectorWithGivenSizeIncludingUniqueId(const std::size_t size,
                                           const Types::Id   includingId)
{
    assert(size > 0);
    if (size == 1)
    {
        return {includingId};
    } else
    {
        auto result = createVectorWithGivenSizeExcludingUniqueIds(
            size - 1, {includingId});
        result.push_back(includingId);
        return result;
    }
}

Types::MarbleIds createVectorWithGivenSizeExcludingUniqueIds(
    const std::size_t size, const Types::MarbleIds& excludingIds)
{
    Types::MarbleIds output{};
    for (int i = 1;
         (i <= Taskmaster::s_maxNumberOfMarbles) && (output.size() < size); ++i)
    {
        const auto foundIt =
            std::find(excludingIds.begin(), excludingIds.end(), i);
        const bool isInExcludingIds = (excludingIds.end() == foundIt);
        if (isInExcludingIds)
        {
            output.push_back(i);
        }
    }

    return output;
}

} // namespace TestHelpers

} // namespace SillyProjects