/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Michael McCreesh
 * Date        : 9/27/2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> steps;              //creates an empty vector
    vector<int> blank;
    if(num_stairs <= 0){                    //if there are no stairs left add stop
        steps.push_back(blank);
    } else{                                 //otherwise check each number of steps you can take at a time 1, 2, or 3
        for(int i = 1; i <= 3; i++){        
            if(num_stairs >= i){            //if the number of stairs remaining is greater than or equal to the number of steps you are trying to take...
                vector<vector<int>> result = get_ways(num_stairs - i);      //new vector called result is created from the recursive call of the program
                for(size_t j = 0; j < result.size(); j++){
                    result.at(j).push_back(i);                              //add each step to a vector in result
                }
                steps.insert(steps.end(), result.begin(), result.end());
            }
        }
    }
    return steps;
}

int num_digits(int num) {
    //divide num by 10 as many times as possilble until num = 0
    //the number of divisions performed is the number of digits in num
    int i = 0;
    while(num > 0){
        num = num/10;
        i++;
    }
    return i;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int width = num_digits(ways.size());
    int count = 0;
    for (unsigned int i = 0; i < ways.size(); i++) {
        count++;
		cout << setw(width) << count << ". [";                          //all numbers are padded to be the same width
		for (unsigned int j = ways[i].size() - 1; j > 0; j--) {         //print each vector<int> in ways on its own line
			cout << ways.at(i).at(j) << ", ";
		}
		cout << ways.at(i).at(0) << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
    int number;
	istringstream iss;
	if (argc != 2) {            //if there are not 2 arguments give an error
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if (!(iss >> number)) {     //if argument is not a positive integer give error
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	iss.clear();
	if (number <= 0) {          //if argument is not a positive integer give error
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	int cb = get_ways(number).size();
	if (number == 1) {
		cout << cb << " way to climb " << number << " stair." << endl;      //"way" for 1 path "ways" for multiple paths
	} else {
		cout << cb << " ways to climb " << number << " stairs." << endl;
	}
	display_ways(get_ways(number));
	return 0;
}
