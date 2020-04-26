#include "main.cpp"
#include <gtest/gtest.h>

TEST(TestCase1, SubCasoTest1){
	S = {20,30,40};
	RS = {35,45,10};
	n = 3;
    int res = FB(0,70,0);
    EXPECT_TRUE(res == 2);
}

TEST(Void, void){
    /* Casos pero > 0*/
    S = {};
    RS = {};
    n = 0;
    int res = FB(0,70,0);
    EXPECT_TRUE(res == 0);

    poda_factibilidad = true;
    poda_optimalidad = false;
    res = BT(0,70,0);
    EXPECT_TRUE(res == 0);

    poda_factibilidad = false;
    poda_optimalidad = true;
    res = BT(0,70,0);
    EXPECT_TRUE(res == 0);

    /* Caso resistencia inicial == 0*/

    res = FB(0,0,0);
    EXPECT_TRUE(res == 0);

    poda_factibilidad = true;
    poda_optimalidad = false;
    res = BT(0,0,0);
    EXPECT_TRUE(res == 0);

    poda_factibilidad = false;
    poda_optimalidad = true;
    res = BT(0,0,0);
    EXPECT_TRUE(res == 0);
}



int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
