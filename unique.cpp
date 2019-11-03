/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Michael McCreesh
 * Date        : 9/17/2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    for(size_t i = 0; i < s.size(); i++){///cycles through the string and checks if any of the characters are capitalized
        char character = s[i];
        if(! islower(character)){//returns false if it is not lower case
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

    unsigned int tracker = 0;
    for(size_t i = 0; i < s.size(); i++){
        unsigned int shift = s.at(i) - 'a'; // int shift is the number of shifts that needs to be performed
        unsigned int num = 1<<shift;        //shift the number 1 over shift many times
        if((tracker & num) > 0){            //if tracker and numb > 0 return false (they are the same number)
            return false;
        }
        tracker = tracker | num;            //else tracker = tracker |num (anywhere thers a 1 in num there is also a 1 in tracker)
		
    }
    return true;
}


int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if(argc !=2) {
		cout << "Usage: ./unique <string>" << endl;
		return 0;
	}
	if (is_all_lowercase(argv[1])) {
		if(all_unique_letters(argv[1])) {
			cout << "All letters are unique."; //output formatting
			return 0;
		} else {
			cout << "Duplicate letters found.";
			return 0;
		}
	}

	cerr << "Error: String must contain only lowercase letters." << endl;
	return 0;

}
