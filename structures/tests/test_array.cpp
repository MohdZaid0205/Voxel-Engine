#include <gtest/gtest.h>
#include "structures.h"

TEST(ArrayTests, SetupVerification) {
    EXPECT_TRUE(is_properly_setup());
}
