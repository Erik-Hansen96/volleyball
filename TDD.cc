#include <iostream>
#include <string>
#include <cctype>
#include <type_traits>
#include <gtest/gtest.h>
using namespace std;
//Jeopardy input test
template <typename T>
string inputCheck(T val){
	//	if(typeid(val) == typeid(char)){ return "INVALID ANSWER INPUT";}
	//	if(val <=0){return "INVALID ANSWER INPUT";}
	if constexpr (is_same_v<T, int>){
		if(val >= 1 && val <=4){
			return "VALID INPUT";
		}
		else return "INVALID ANSWER INPUT";
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
	EXPECT_EQ(inputCheck("sdsdf"), "INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck('a'),"INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck(0),"INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck(15),"INVALID ANSWER INPUT");
	EXPECT_EQ(inputCheck(-90),"INVALID ANSWER INPUT");
}
//Boat placement phase test battleship
template<typename T>
string placementCheck(T val){
	//check if a char
	if constexpr (is_same_v<T, char>){
		char  newVal = toupper(val);
		if(newVal == 'C' || newVal == 'B' || newVal == 'S' || newVal == 'P'){
			return "VALID INPUT";
		}
		else return "INVALID INPUT";
	}
	//not a char
	else return "INVALID INPUT";
}
TEST(battleshipPlacement, GoodInput){
	EXPECT_EQ(placementCheck('c'), "VALID INPUT");
	EXPECT_EQ(placementCheck('b'), "VALID INPUT");
	EXPECT_EQ(placementCheck('s'), "VALID INPUT");
	EXPECT_EQ(placementCheck('p'), "VALID INPUT");
}

TEST(battleshipPlacement, BadInput){
	EXPECT_EQ(placementCheck(1), "INVALID INPUT");
	EXPECT_EQ(placementCheck(-51), "INVALID INPUT");
	EXPECT_EQ(placementCheck("a47s"), "INVALID INPUT");
	EXPECT_EQ(placementCheck('a'), "INVALID INPUT");
}
//Battle ship second phase input test
template<typename T>
string battleInputCheck(T val){
	if constexpr (is_same_v<T, string>){
		if(val.length() != 2 || !isalpha(val[0]) || !isdigit(val[1])){
			return "INVALID INPUT";
		}
		char first = toupper(val[0]);
		char second = val[1];
		if((first >= 'A' && first <= 'J') && (second >='0' && second <='9')){
			return "VALID INPUT";
		}
		else return "INVALID INPUT";
	}
	else return "INVALID INPUT";
}



TEST(battleshipFight, GoodInput){
	string input = "C9";
	EXPECT_EQ(battleInputCheck(input), "VALID INPUT");
	input = "A7";
	EXPECT_EQ(battleInputCheck(input), "VALID INPUT");
	input = "b8";
	EXPECT_EQ(battleInputCheck(input), "VALID INPUT");
	input = "c6";
	EXPECT_EQ(battleInputCheck(input), "VALID INPUT");
}

TEST(battleshipFight, BadInput){
    string input = "z9";
    EXPECT_EQ(battleInputCheck(input), "INVALID INPUT");
    input = "a-7";
    EXPECT_EQ(battleInputCheck(input), "INVALID INPUT");
    input = "988";
    EXPECT_EQ(battleInputCheck(input), "INVALID INPUT");
    input = "cJ";
    EXPECT_EQ(battleInputCheck(input), "INVALID INPUT");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


























