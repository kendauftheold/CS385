/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Michael McCreesh and Hamzah Nizami
 * Date        : October 7th, 2019
 * Description : Does the waterjug puzzle using breadth first search to find minimum pours
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int cap_a, cap_b, cap_c;
int solution[2];
vector<vector<bool>> seen;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

//See if goal conditions are met
bool success(int a, int b){
    if(solution[0] == a && solution[1] == b){//if a and b are the correct values, c must also be correct therefore we know it is complete
        return true;
    }
    return false;
}

//checks to see if a specific combo of water levels has been seen already
bool firstTime(int a, int b){
    if(!seen[a][b]){        //check if this combination of water levels has been seen already
        seen[a][b] = true;  //if not change the value to true
        return true;       //return true if it hadn't been used already
    }
    return false;    //otherwise return false
} 

/*************************  All of the pouring functions are structured in the same way so only the first one will be commented     *******************************/
//POUR C INTO A
State CtoA(State state){
    ostringstream s;
    if(state.a < cap_a){    //makes sure a is not full
        if(cap_a >= state.a + state.c){     //if a won't overflow, pour all of c into it
            state.a = state.a + state.c;
            int old = state.c;      //keeps track of how many gallons were poured
            state.c = 0;        //c is empty now
            if(old == 1){   //if only 1 gallon is poured print "gallon"
                s << "Pour " << old << " gallon from C to A. " << state.to_string();
            }else{  //otherwise print "gallons"
                s << "Pour " << old << " gallons from C to A. " << state.to_string();
            }
        }else{      //if a will overflow...
            int dif = cap_a - state.a;      //finds how much can be poured
            state.a = cap_a;        //fills a
            state.c = state.c - dif;    //finds how much will be left in c
            if( dif == 1){      //if only 1 gallon is poured print "gallon"
                s << "Pour " << dif << " gallon from C to A. " << state.to_string();
            }else{      //otherwise print gallons
                s << "Pour " << dif << " gallons from C to A. " << state.to_string();
            }
        }
        state.directions.push_back(s.str());        //add this state to the directions vector in case this path is the quickest
    }
    return state;       //return the altered state
}

//POUR B INTO A
State BtoA(State state){
    ostringstream s;
    if(state.a < cap_a){
        if(cap_a >= state.a + state.b){
            state.a = state.a + state.b;
            int old = state.b;
            state.b = 0;
            if(old == 1){
                s << "Pour " << old << " gallon from B to A. " << state.to_string();
            }else{
                s << "Pour " << old << " gallons from B to A. " << state.to_string();
            }
        }else{
            int dif = cap_a - state.a;
            state.a = cap_a;
            state.b = state.b - dif;
            if(dif == 1){
                s << "Pour " << dif << " gallon from B to A. " << state.to_string();
            }else{
                s << "Pour " << dif << " gallons from B to A. " << state.to_string();
            }
        }
        state.directions.push_back(s.str());
    }
    return state;
}

//POUR C INTO B
State CtoB(State state){
    ostringstream s;
    if(state.b < cap_b){
        if(cap_b >= state.b + state.c){
            state.b = state.b + state.c;
            int old = state.c;
            state.c = 0;
            if(old == 1){
                s << "Pour " << old << " gallon from C to B. " << state.to_string();
            }else{
                s << "Pour " << old << " gallons from C to B. " << state.to_string();
            }
        }else{
            int dif = cap_b - state.b;
            state.b = cap_b;
            state.c = state.c - dif;
            if(dif == 1){
                s << "Pour " << dif << " gallon from C to B. " << state.to_string();
            }else{
                s << "Pour " << dif << " gallons from C to B. " << state.to_string();
            }
        }
        state.directions.push_back(s.str());
    }
    return state;
}

//POUR A INTO B
State AtoB(State state){
    ostringstream s;
    if(state.b < cap_b){
        if(cap_b >= state.b + state.a){
            state.b = state.b + state.a;
            int old = state.a;
            state.a = 0;
            if(old == 1){
                s << "Pour " << old << " gallon from A to B. " << state.to_string();
            }else{
                s << "Pour " << old << " gallons from A to B. " << state.to_string();
            }
        }else{
            int dif = cap_b - state.b;
            state.b = cap_b;
            state.a = state.a - dif;
            if(dif == 1){
                s << "Pour " << dif << " gallon from A to B. " << state.to_string();
            }else{
                s << "Pour " << dif << " gallons from A to B. " << state.to_string();
            }
        }
        state.directions.push_back(s.str());
    }
    return state;
}

//POUR B INTO C
State BtoC(State state){
    ostringstream s;
    if(state.c < cap_c){
        if(cap_c >= state.c + state.b){
            state.c = state.c + state.b;
            int old = state.b;
            state.b = 0;
            if(old == 1){
                s << "Pour " << old << " gallon from B to C. " << state.to_string();
            }else{
                s << "Pour " << old << " gallons from B to C. " << state.to_string();
            }
        }else{
            int dif = cap_c - state.c;
            state.c = cap_c;
            state.b = state.b - dif;
            if(dif == 1){
                s << "Pour " << dif << " gallon from B to C. " << state.to_string();
            }else{
                s << "Pour " << dif << " gallons from B to C. " << state.to_string();
            }
        }
        state.directions.push_back(s.str());
    }
    return state;
}

//POUR A INTO C
State AtoC(State state){
    ostringstream s;
    if(state.c < cap_c){
        if(cap_c >= state.c + state.a){
            state.c = state.c + state.a;
            int old = state.a;
            state.a = 0;
            if(old == 1){
                s << "Pour " << old << " gallon from A to C. " << state.to_string();
            }else{
                s << "Pour " << old << " gallons from A to C. " << state.to_string();
            }
        }else{
            int dif = cap_c - state.c;
            state.c = cap_c;
            state.a = state.a - dif;
            if(dif == 1){
                s << "Pour " << dif << " gallon from A to C. " << state.to_string();
            }else{
                s << "Pour " << dif << " gallons from A to C. " << state.to_string();
            }
        }
        state.directions.push_back(s.str());
    }
    return state;
}

//Performs the BFS
State BFS(State start){
    //fill seen vector with false values
    for(int i = 0; i <= cap_a; i++){
        vector<bool> fill;
        seen.push_back(fill);
        for(int j = 0; j <= cap_b; j++){
            seen[i].push_back(false);
        }
    }

    queue<State> pours;
    pours.push(start);  //adds start state to the queue

    while(!pours.empty()){ //while queue isn't empty....
        if(success(pours.front().a, pours.front().b)){//see if the end state has been reached
            return pours.front();//return the final state if so
        }
        if(firstTime(pours.front().a, pours.front().b)){//if the combo of water levels has not been seen before...
            pours.push(CtoA(pours.front()));            //call all the different pour functions to make all possible following states
            pours.push(BtoA(pours.front()));            //add these states to the queue to be tested
            pours.push(CtoB(pours.front()));
            pours.push(AtoB(pours.front()));
            pours.push(BtoC(pours.front()));
            pours.push(AtoC(pours.front()));
        }
        pours.pop();
    }
    State invalid(-1,-1,-1);        //if the queue empties before a solution is found there is no solution
    return invalid;                 //return an extraneous state that is easily recognized this state signifies that there is no solution
}

int main(int argc, char * const argv[]) {
    int n; 
    if(argc != 7){  //if there aren't seven arguments, return this error message
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 0;
    }
    string arg_to_jug_map[4] = {" ", "A", "B", "C"};
    //check if all the arguments are actual integers. 
    for(int i = 1; i < 7; i++){ 
        istringstream iss(argv[i]);
        if(!(iss >> n)){  //check if we have a valid integer 
            if(i <= 3){ 
                cerr << "Error: Invalid capacity '" << iss.str() << "' for jug " << arg_to_jug_map[i] << "." << endl;
                return 0;
            }else{ 
                cerr << "Error: Invalid goal '" << iss.str() << "' for jug " << arg_to_jug_map[i-3] << "." << endl;
                return 0;
            }
        }
        int arg_value = atoi(argv[i]);
        if(arg_value < 0 or (i == 3 and arg_value <= 0)){  //check if it's positive 
            if(i <= 3){ 
                cerr << "Error: Invalid capacity " << "'" << arg_value << "'" << " for jug " << arg_to_jug_map[i] << "."; 
                return 0;
            } else if(i > 3){ 
                cerr << "Error: Invalid goal " << "'" << arg_value << "'" << " for jug " << arg_to_jug_map[i-3] << "."; 
                return 0;
            }
        }
    }
    int goal_sum = 0;
    for(int j = 4; j < 7; j++){ 
        goal_sum += (atoi(argv[j]));
        if((atoi(argv[j])) > (atoi(argv[j-3]))){ //check if all the arguments make sense
            cerr << "Error: Goal cannot exceed capacity of jug " << arg_to_jug_map[j-3] << "." << endl;
            return 0;
        } else if(j == 6 && goal_sum != (atoi(argv[3]))){ 
            cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
            return 0; 
        }
    }
    cap_a = (atoi(argv[1]));
    cap_b = (atoi(argv[2])); 
    cap_c = (atoi(argv[3]));
    solution[0] = (atoi(argv[4]));
    solution[1] = (atoi(argv[5]));
    State initial_state(0, 0, (atoi(argv[3]))); 
    State final_state = BFS(initial_state); 
    if(final_state.a == -1 && final_state.b == -1 && final_state.c == -1){ 
        cerr << "No solution.";
        return 0;
    }
    cout << "Initial state. " << initial_state.to_string() << endl;
    for(size_t j = 0; j < final_state.directions.size(); j++){ 
        cout << final_state.directions.at(j) << endl;
    }
    return 1;
}