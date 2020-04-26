#include "main.cpp"
#include <gtest/gtest.h>

TEST(TestCase1, SubCasoTest1){
	S = {20,30,40};
	RS = {35,45,10};
	n = 3;
    int res = FB(0,70,0);
    EXPECT_TRUE(res == 2);
}





int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
