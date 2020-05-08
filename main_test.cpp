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

    S = {};
    RS = {};
    n = 0;
    res = PD(0,70);
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

TEST(TestCase1, ProgramacionDinamica){
    S = {20,30,40};
    RS = {35,45,10};
    n = 3;
    int res = PD(n, 70);
    EXPECT_TRUE(res == 2);
}

TEST(TestCase2, ProgramacionDinamica){
    S = {40,30,20};
    RS = {20,30,40};
    n = 3;
    int res = PD(n, 10);
    EXPECT_TRUE(res == 0);

    RS = {35,45,10};
    n = 3;
    res = PD(n, 70);
    EXPECT_TRUE(res == 2);

    S = {1,2,3,4,5,6,7,8,9,5,3,3,4,2,43,345,2,5,65,4,7,3};
    RS = {70,5,6,234,2465,12,345,3321,3566,4,32,4,3,7,9,0,3,21,3,9,32,12};
    n = 22;
    res = PD(n, 700);
    EXPECT_TRUE(res == FB(0,700,0));
}



int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
