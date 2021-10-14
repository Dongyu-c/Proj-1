#include "rpn.h"
#include <iostream>



int main(int argc, char** argv) {
	
	string test[] = { "2", "12", "6", "-", "/", "5", "3", "+", "*", ">" };

	if (argc == 1) {
		double result = rpn(test, sizeof(test) / sizeof(test[0]));;
		cout << result << endl;
	}
	else if (argc == 2) {
		if (argv[1] == "-l") {
			
		}
		else {
			cout << "Invalid Input" << endl;
		}

	}
}
