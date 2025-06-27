#include <gtest/gtest.h>
#include "structures.h"

using namespace Structures;


TEST(StaticArrayTest, ConstructorInitializesSize) {
    StaticArray<int> arr(5);
    EXPECT_EQ(arr.getSize(), 5);
}

TEST(StaticArrayTest, AccessWorks) {
    StaticArray<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(StaticArrayTest, CopyFromExistingArray) {
    int data[] = { 1, 2, 3 };
    StaticArray<int> arr(data, 3);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[1], 2);
}

TEST(DynamicArrayTest, InsertAtEndIncreasesSize) {
    DynamicArray<int> arr;
    arr.insert(5);
    arr.insert(10);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[1], 10);
}

TEST(DynamicArrayTest, InsertAtIndexShiftsElements) {
    DynamicArray<int> arr;
    arr.insert(1);
    arr.insert(3);
    arr.insert(2, 1);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArrayTest, RemoveFromEndDecreasesSize) {
    DynamicArray<int> arr;
    arr.insert(100);
    arr.insert(200);
    arr.remove();
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr[0], 100);
}

TEST(DynamicArrayTest, RemoveAtIndexShiftsElements) {
    DynamicArray<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.insert(30);
    arr.remove(1); // remove 20
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}

TEST(DynamicArrayTest, ConvertStaticToDynamic) {
    StaticArray<int> sarr(3);
    sarr[0] = 1;
    sarr[1] = 2;
    sarr[2] = 3;
    DynamicArray<int> darr = staticToDynamic(sarr);
    EXPECT_EQ(darr.getSize(), 3);
    EXPECT_EQ(darr[2], 3);
}

TEST(DynamicArrayTest, ConvertDynamicToStatic) {
    DynamicArray<int> darr;
    darr.insert(42);
    darr.insert(99);
    StaticArray<int> sarr = dynamicToStatic(darr);
    EXPECT_EQ(sarr.getSize(), 2);
    EXPECT_EQ(sarr[1], 99);
}