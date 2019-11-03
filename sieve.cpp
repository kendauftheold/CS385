/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Michael McCreesh
 * Date        : 9/9/19
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    //declare 2 constant int values - one for max width of a prime and another for the number of primes per row
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    //create int to count how many primes are on current line
    int count = 0;
    //if all primes fit on one row, print all with a space betwwen them
    if(count_num_primes() <= primes_per_row){
        for(int i = 2; i<max_prime_; i++){
            if(is_prime_[i] == true){
                cout << i << " ";
            }
        }
     cout << max_prime_;
    }else{//otherwise use setw() to make all the primes the same length (padded with spaces)
        for(int i = 2; i<=max_prime_; i++){
            if(is_prime_[i] == true){
                if(count == 0){//first in row doesnt need a space before it
                    cout << setw(max_prime_width)<<i;
                }else{//all other primes do
                    cout << setw(max_prime_width+1)<<i;
                }
                count++;
            }
            if(count == primes_per_row){//if you have the max number of primes in the row, go to the next line and set count to 0
                cout << endl;
                count = 0;
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    //traverse through the is_prime_ array and count how many elements are "true"
    int total = 0;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i] == true){
            total++;
        }
    }
    return total;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    //set all elements in is_prime_ to true
    for(int i = 0; i <= limit_; i++){
        is_prime_[i] = true;
    }
    //0 and 1 are not prime so start at 2
    //remove all multiples of 2, then all multiples of 3,... until you reach sqrt of the limit
    for(int i = 2; i <= sqrt(limit_); i++){
        if(is_prime_[i] == true){
            for(int j = i*i; j <= limit_; j+=i){
                is_prime_[j] = false;
            }
        }
    }
    //start at the end of the array and traverse backwards. 
    //first element marked true is the largest prime
    for(int i = limit_; i>0; i--){
        if(is_prime_[i] == true){
            max_prime_ = i;
            break;
        }
    }
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    //divide num by 10 as many times as possilble until num = 0
    //the number of divisions performed is the number of digits in num
    int i = 0;
    while(num > 0){
        num = num/10;
        i++;
    }
    return i;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);
    cout << endl << "Number of primes found: " << sieve.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    sieve.display_primes();
}
