#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <gtest\gtest.h>
using namespace std;


// getAscendingStr Function requirement
//
// Take space seperated digit string (ex. "1 2 3 5 4") and 
//   modify input string to ascending order ("1 2 3 4 5").
//
// return 0 if success, (empty string)
//       -1 if exception occur (ex. string containing non-digit character)
int getAscendingStr(string& inputStr)
{
	/// Please fill your code here
	int i = 0, j = 0, Array_Num = 0, temp = 0;
	int alpha_Flag = 0;
	vector<int> num;
	char *pEnd = NULL;
	const char *pStart = inputStr.c_str();
	/// detected alpha in string///
	for (string::iterator it = inputStr.begin(); it != inputStr.end(); ++it) {
		if (isalpha(*it))
			alpha_Flag = 1;
	}
	/// convert string -> integer
	while (alpha_Flag == 0) {
		num.push_back(strtol(pStart, &pEnd, 10));
		if (pStart == pEnd)
			break;
		else
			pStart = pEnd;
		Array_Num++;
	}
	//// Bubble Sort ////
	if(alpha_Flag == 0)
		sort(num.begin(),num.end()-1);
	//// Stored the result /////
	if (alpha_Flag == 0) {
		inputStr = to_string(num[0]);
		for (i = 1; i < Array_Num; i++)
			inputStr = inputStr + " " + to_string(num.at(i));
		return 0;
	}
	else
		return -1;
}

// solveQ Function requirement
// 
// solve quadratic function ax^2 + bx + c = 0
//
// return 1 if equation has two different real number root 
//          (return vector size should be 2 containing 2 solution.  
//          Greater value should put into smaller vector index)
//        0 there is only one possible solution to the quadratic equation 
//          (return vector size should be 1)
//       -1 complex roots 
//          (return vector size should be 0)
int solveQ(vector<double> &x, double a, double b, double c)
{
	float delta = pow(b, 2) - 4 * a * c;

	if (delta > 0) { // condition : b^2-4ac > 0
		x.push_back((-b + sqrt(delta)) / (2 * a));
		x.push_back((-b - sqrt(delta)) / (2 * a));
		printf("%f, %f, %d\n", x.at(0), x.at(1), x.size());
		return 1;
	}
	else if (delta == 0) {// condition : b^2-4ac == 0
		x.push_back((-b) / (2 * a));
		printf("%f, %d\n", x.at(0), x.size());
		return 0;
	}
	else {// condition : b^2-4ac < 0
		x.clear();
		printf("%d\n", x.size());
		return -1;
	}

}

int main(int argc, char*argv[]) {

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(getAscendingStr, SimpleAscending)
{//Simple ascending test case

	string inputStr = "1 -3 2195 4 50";
	string tmpStr = inputStr;
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(tmpStr, "-3 1 4 50 2195");
	EXPECT_EQ(err, 0);
}

TEST(getAscendingStr, handleNonDigit)
{//getAscendingStr function should handle non digit case
	string tmpStr = "1 3 2 4 a 7f415";
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(err, -1);
}

TEST(solveQ, twoSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 2, -3);
	EXPECT_EQ(iSol, 1);
	EXPECT_EQ(sol.size(), 2);
	EXPECT_EQ(sol.at(0), 1);
	EXPECT_EQ(sol.at(1), -3);
}

TEST(solveQ, oneSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, -8, 16);
	EXPECT_EQ(iSol, 0);
	EXPECT_EQ(sol.size(), 1);
	EXPECT_EQ(sol.at(0), 4);
}

TEST(solveQ, noSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 1, 16);
	EXPECT_EQ(iSol, -1);
	EXPECT_EQ(sol.size(), 0);
}