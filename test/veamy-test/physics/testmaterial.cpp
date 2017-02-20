#include <gtest/gtest.h>
#include <veamy/physics/materials/Materials.h>
#include <veamy/physics/Material.h>

TEST(MaterialTest, InitializationTest){
    Material steel (Materials::material::Steel);
    Material m(210000000000,0.3);

    EXPECT_EQ(steel, m);
}