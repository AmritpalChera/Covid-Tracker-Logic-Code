// Lab Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "tests.hpp"
#include <iostream>
#include <vector>
/*
Person::Person(string fName, string idnty, string tDate, bool posi):
    firstName(fName), id(idnty), testDate(tDate), isPositive(posi) {};
*/
int main()
{
    GraphTest test;
    vector<string> messages;
    messages.resize(5);
    messages[0] = "Inserting Individuals: ";
    messages[1] = "Inserting Individuals and their contacts; one cluster: ";
    messages[2] = "Number of positive cases with one cluster: ";
    messages[3] = "Number of positive cases with multiple clusters: ";
    messages[4] = "Largest Cluster size with atleast 2 cases: ";

    bool test_results[5] = {
        test.test1(),
        test.test2(),
        test.test3(),
        test.test4(),
        test.test5()
    };

    
    for (int a = 0; a < messages.size(); a++) {
        string s;
        (test_results[a] == 1) ? s = "\npassed\n" : s = "\nfailed\n";
        cout << messages[a] << s;
    }
    
    cout << "\nwe done \n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
