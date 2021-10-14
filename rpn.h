#include <string>
#include <vector>
#include <iostream>

#include <algorithm>
#include<cmath>
#include<stack>
#include<climits>
#include <math.h>
#include <stdio.h>

#include <typeinfo>

#include <errno.h>
using namespace std;

void  Optional(string* strs);
void AddTabVector(vector<void>& output_vector);
void AddTabNumber(vector<void>& output_vector);
void AddTabNumber(vector<void>& output_vector);
void AddTabVector(vector<void>& output_vector);
void AddEnter(vector<void>& output_vector);
void PrintVectorF(vector<void>& output_vector);


bool isOperator(string str) {
    vector<string>  my_list = { "+","-","*","/","**",">","<"};
    for (int i = 0; i < sizeof(my_list); i++) {
        if (my_list[i] == str) {
            return true;
        }
    }
    return false;
}

bool isOperand(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && (isdigit(*it) || *it == '.')) ++it;
    return !s.empty() && it == s.end();
}

void operation(double a, double b, string oper, double&return_double, bool& return_bool) {
    //Perform operation
    if (oper == "+") {
        return_double = (b + a);
    }
    else if (oper == "-") {
        return_double = (b - a);
    }
    else if (oper == "*") {
        return_double = (b * a);
    }
    else if (oper == "/")
        return_double = (b / a);
    else if (oper == "∗∗") {
        return_double = (pow(b, a));
    }
    else if (oper == "<") {
        return_bool = (b < a);
    }
    else if (oper == ">") {
        return_bool = (b > a);
    }
}




double rpn(string* strs, size_t size) {
    double result = 0.0;
    vector<void> result_list;
    double return_double;
    bool return_bool;
    if (strs[size -1] == "_l") {
        Optional(strs);
    }
    for (int i = 0; i < size; i++) {
        if (isOperator(strs[i])) {
            result_list.push_back(strs[i]);
        }
        if (isOperand(strs[i])) {
            result_list.push_back(stod(strs[i]));
        }
    }
    while (sizeof(result_list) >= 3) {
        int loc;
        for (int i = 2; i < sizeof(result_list); i++) {//find the first operator
            if (isOperator(result_list[i])) {
                loc = i;
                break;
            }
        }
        operation(stod(result_list[loc - 2]), stod(result_list[loc - 1]), result_list[loc], return_double, return_bool);
        if (sizeof(result_list) >= 3) {
            if (result_list[loc] == "<" || result_list[loc] == ">") {
                vector<void> re_list = {};
                for (int i = 0; i < loc - 2; i++) {
                    re_list.push_back(result_list[i]);
                }
                re_list.push_back(return_bool);
                for (int i = loc+1; i < sizeof(result_list); i++) {
                    re_list.push_back(result_list[i]);
                }
                result_list = re_list;
            }
            else {
                vector<void> re_list = {};
                for (int i = 0; i < loc - 2; i++) {
                    re_list.push_back(result_list[i]);
                }
                re_list.push_back(return_double);
                for (int i = loc + 1; i < sizeof(result_list); i++) {
                    re_list.push_back(result_list[i]);
                }
                result_list = re_list;
            }

        }
        else {
            if (result_list[loc] == "<" || result_list[loc] == ">") {
                result_list = {};
                result_list.push_back(return_bool);

            }
            else {
                result_list = {};
                result_list.push_back(return_double);
            }
        }
    }
    result = result_list[0];


    return result;
}



void  Optional(string* strs) {
    vector<void> output;
    vector<void> test_case;
    for (int i = 0; i < (sizeof(strs) / sizeof(strs[0]) - 1); i++) {
        test_case.push_back(strs[i]);
    }
    while (sizeof(test_case) > 0) {
        for (int i = 0; i < sizeof(test_case); i++) {
            if (typeid(test_case[i]).name() == "string" && isOperator(test_case[i])) {
                vector<void> temp;//"(" test_case[i] test_case[i-2]  test_case[i-1] )
                temp.push_back(test_case[i]);
                temp.push_back(test_case[i-2]);
                temp.push_back(test_case[i-1]);
                vector<void>::iterator it;
                it = test_case.begin() + i;
                test_case[i - 2] = temp;
                test_case.erase(it);
                test_case.erase(it - 1);
                break;
            }
        }
    }
    
    PrintVector(test_case);


    return;
}


void PrintVector(vector<void> output_vector) {
    AddQuot(output_vector);
    AddTabVector(output_vector);
    AddTabNumber(output_vector);
    AddEnter(output_vector);
    PrintVectorF(output_vector);    
}



void AddQuot(vector<void>& output_vector) {
    for (int i = 0; i < sizeof(output_vector); i++) {
        if (typeid(output_vector[i]).name() == "string") {
            if (isOperator(output_vector[i])) {
                output_vector[i] = "(" + output_vector[i];
            }
        }
        else {
            AddQuot(output_vector[i]);
        }       
    }
    output_vector.push_back(")");
}


void AddTab(vector<void>& output_vector) {
    for (int i = 0; i < sizeof(output_vector); i++) {
        if (typeid(output_vector[i]).name() == "string") {
               output_vector[i] = "\t" + output_vector[i];           
        }
        else {
            AddTab(output_vector[i]);
        }
    }
}

void AddTabVector(vector<void>& output_vector) {
    for (int i = 0; i < sizeof(output_vector); i++) {
        if (typeid(output_vector[i]).name() == "vector") {
            AddTab(output_vector[i]);
            AddTabVector(output_vector[i]);
        }
    }
}

void AddTabNumber(vector<void>& output_vector) {
    for (int i = 0; i < sizeof(output_vector); i++) {
        if (typeid(output_vector[i]).name() == "string") {
            if (isOperand(output_vector[i])) {
                output_vector[i] == "/t" + output_vector[i];
            }
        }
        else {
            AddTabNumber(output_vector[i]);
        }

    }
}


void AddEnter(vector<void>& output_vector) {
    for (int i = 0; i < sizeof(output_vector); i++) {
        if (typeid(output_vector[i]).name() == "string") {
            output_vector[i] = "\n" + output_vector[i];
        }
        else {
            AddEnter(output_vector[i]);
        }
    }
}
void PrintVectorF(vector<void>& output_vector) {
    for (int i = 0; i < sizeof(output_vector); i++) {
        if (typeid(output_vector[i]).name() == "string") {          
            printf(output_vector[i]);
        }
        else {
            PrintVectorF(output_vector[i]);
        }
    }
}