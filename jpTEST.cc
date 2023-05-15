#include <iostream>
#include <string>
#include <gtest/gtest.h>
using namespace std;

template <typename T>
string inputCheck(T val){
	if(typeid(val) == typeid(std::string)){ return "INVALID ANSWER INPUT";}
	if(val <=0){return "INVALID ANSWER INPUT";}
	if(val >= 1 && val <=4){
		return "VALID INPUT";
	}
	else return "INVALID ANSWER INPUT";

}
TEST(jeopardy, GoodInput){
		EXPECT_EQ(inputCheck(1),"VALID INPUT");
		EXPECT_EQ(inputCheck(2),"VALID INPUT");
		EXPECT_EQ(inputCheck(3),"VALID INPUT");
		EXPECT_EQ(inputCheck(4),"VALID INPUT");
}


TEST(jeopardy, BadInput){
	EXPECT_EQ(inputCheck('a'),"INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck(0),"INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck(15),"INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck(-90),"INVALID ANSWER INPUT");
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
