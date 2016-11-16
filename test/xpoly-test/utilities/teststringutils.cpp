#include <gtest/gtest.h>
#include <x-poly/utilities/stringUtils.h>

TEST(StringUtilsTest, GetPathTest){
    std::string path = string_utils::getPath();

    EXPECT_EQ(path, "C:\\Users\\Catalina\\");
}