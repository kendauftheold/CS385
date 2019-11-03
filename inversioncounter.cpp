/*******************************************************************************
 * Name        : inversioncount.cpp
 * Author      : Michael McCreesh
 * Version     : 1.0
 * Date        : 10/24/2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

static long mergesort(int array[], int scratch[], int low, int high);


long count_inversions_slow(int array[], int length) {
  //Counts the number of inversions in an array in theta(n^2) time.
    long count = 0;
    for (int i = 0; i < length - 1; i++) {
      for (int j = i + 1; j < length; j++) {
        if (array[i] > array[j]) {
          count++;
        }
      }
    }
    return count;
}


long count_inversions_fast(int array[], int length) {
  // Counts the number of inversions in an array in theta(n lg n) time.
    int *temp = new int[length];
    long count = mergesort(array, temp, 0, length - 1);
    delete[] temp;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
  //Sorts a list using the mergesort and returns number of inversions
    if (low == high) {//Array has one element
      return 0;
    }
    else if (low < high) {
      long count = 0;
      int splice = low + ((high - low) / 2);
      int bottom = low;
      int top = splice + 1;
      count += mergesort(array, scratch, low, splice);
      count += mergesort(array, scratch, splice + 1, high);
      for (int i = low; i <= high;i++) {
        if (bottom <= splice && (array[bottom] <= array[top] || top > high)) {
          scratch[i] = array[bottom];
          bottom++;
        }
        else {
          count += (splice - bottom + 1);
          scratch[i] = array[top];
          top++;
        }
      }
      for (int j = low; j <= high; j++) {
        array[j] = scratch[j];
      }
      return count;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
      cerr << "Usage: " << argv[0] << " [slow]" << endl;
      return 1;
    }
    if ((argc == 2) && (strcmp(argv[1], "slow") != 0)) {
      cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
			return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.empty()) {
      cerr << "Error: Sequence of integers not received." << endl;
      return 1;
    }
    if (argc == 1) {
      cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }
    else {
      cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
    return 0;
}
