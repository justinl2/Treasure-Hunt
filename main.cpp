// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include "traverse.cpp"
#include <getopt.h>

using namespace std;

size_t mapSize;
vector<vector<Legend> > grid;
Coordinate position;
Coordinate landPosition;
Coordinate initAshore;
queue <Coordinate> ashore;
stack <Coordinate> back;
queue <Coordinate> boob;
bool found = false;
bool pathProcessed;
Options options;
size_t notFoundlocations;

size_t xStart = 0;
size_t yStart = 0;
size_t xEnd = 0;
size_t yEnd = 0;
size_t water = 0;
size_t land = 1;
size_t wentAshore = 0;
size_t pathLength = 0; 

void readGridList(){

    vector <Legend> bravo; 

    bravo.resize(mapSize);
    for (size_t i = 0; i < mapSize; ++i) {
        grid.push_back(bravo);
    }

    char x;
    char y;
    char symballs;
    while(cin >> x >> y >> symballs){
        
        size_t x1;
        size_t y1;

        x1 = static_cast<uint32_t>(x - '0');
        y1 = static_cast<uint32_t>(y - '0');


        grid.at(x1).at(y1).symbol = symballs;

   
        if(grid.at(x1).at(y1).symbol == '@'){
            xStart = x1;
            yStart = y1;
        }

    }
}

bool isValid(Coordinate a){

    if(a.x >= mapSize || a.y >= mapSize){
        return false;
    }
    if(grid.at(a.x).at(a.y).symbol == '#'){
        return false;
    }
    if(grid.at(a.x).at(a.y).status != 'u'){
        return false;
    }

    
    return true;
    
}

bool isValidLand(Coordinate a){
    if(a.x >= mapSize || a.y >= mapSize){
        return false;
    }
    if(grid.at(a.x).at(a.y).symbol == 'o' && grid.at(a.x).at(a.y).status == 'u'){
        return true;
    } 

    if(grid.at(a.x).at(a.y).symbol == '$'){
        return true;
    } else {
    return false;
    }

}

void searchLandStack(Coordinate A){
    stack <Coordinate> stack;
    stack.push(A);
    
    initAshore.x = A.x;
    initAshore.y = A.y;
    ashore.push(initAshore);
    wentAshore++;
    if(grid[initAshore.x][initAshore.y].symbol == '$'){
        xEnd = initAshore.x;
        yEnd = initAshore.y;
        found = true;
        return;
    }
    while(stack.empty() == false && found == false){
        land++;
        Coordinate Justin;
        Justin.x = stack.top().x;
        Justin.y = stack.top().y;
        if(grid.at(Justin.x).at(Justin.y).symbol == '$'){
            
            xEnd = Justin.x;
            yEnd = Justin.y;
            grid.at(Justin.x).at(Justin.y).status = 's';
            found = true;
            return;
        }
        
        stack.pop();
        for(size_t i = 0; i < 4; i++){
            if(options.huntOrder[i] == 'N'){
                Coordinate N;
                N.x = Justin.x - 1;
                N.y = Justin.y;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 's';
                        found = true;
                        return;
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 's';
                    }
                }
            }
            else if(options.huntOrder[i] == 'E'){
                Coordinate N;
                N.x = Justin.x;
                N.y = Justin.y + 1;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 'w';
                        found = true;
                        return;
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'w';
                    }
                }
            }
            else if(options.huntOrder[i] == 'S'){
                Coordinate N;
                N.x = Justin.x + 1;
                N.y = Justin.y;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 'n';
                        found = true;
                        return;
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'n';
                    }
                }
            }
            else if(options.huntOrder[i] == 'W'){
                Coordinate N;
                N.x = Justin.x;
                N.y = Justin.y - 1;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 'e';
                        found = true;
                        return;
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'e';
                    }   
                }
            }
        }
    }
}

void searchLand(Coordinate A){
    queue <Coordinate> queue;
    queue.push(A);
    
    initAshore.x = A.x;
    initAshore.y = A.y;
    ashore.push(initAshore);
    wentAshore++;
    if(grid[initAshore.x][initAshore.y].symbol == '$'){
        xEnd = initAshore.x;
        yEnd = initAshore.y;
        found = true;
        return;
    }
    while(queue.empty() == false && grid.at(queue.front().x).at(queue.front().y).symbol == 'o'){
        land++;
        Coordinate Justin;
        Justin.x = queue.front().x;
        Justin.y = queue.front().y;
        if(grid.at(Justin.x).at(Justin.y).symbol == '$'){
            
            xEnd = Justin.x;
            yEnd = Justin.y;
            grid.at(Justin.x).at(Justin.y).status = 's';
            found = true;
            return;
        }
        
        queue.pop();
        for(size_t i = 0; i < 4; i++){
            if(options.huntOrder[i] == 'N'){
                Coordinate N;
                N.x = Justin.x - 1;
                N.y = Justin.y;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 's';
                        found = true;
                        return;
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 's';
                    }
                }
            }
            else if(options.huntOrder[i] == 'E'){
                Coordinate N;
                N.x = Justin.x;
                N.y = Justin.y + 1;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 'w';
                        found = true;
                        return;
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'w';
                    }
                }
            }
            else if(options.huntOrder[i] == 'S'){
                Coordinate N;
                N.x = Justin.x + 1;
                N.y = Justin.y;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 'n';
                        found = true;
                        return;
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'n';
                    }
                }
            }
            else if(options.huntOrder[i] == 'W'){
                Coordinate N;
                N.x = Justin.x;
                N.y = Justin.y - 1;
                if(isValidLand(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        xEnd = N.x;
                        yEnd = N.y;
                        grid.at(N.x).at(N.y).status = 'e';
                        found = true;
                        return;
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'e';
                    }   
                }
            }
        }
    }
}

void searchSeaSQ() {

    stack<Coordinate> stack;
    Coordinate start;
    start.x = xStart;
    start.y = yStart;
    stack.push(start);
    grid.at(xStart).at(yStart).status = 'v';
    while (stack.empty() == false && grid.at(stack.top().x).at(stack.top().y).symbol != '$') {
        
        water++;
        Coordinate temp;
        temp.x = stack.top().x;
        temp.y = stack.top().y;
        stack.pop();

        if (found == false && stack.empty()){
            notFoundlocations = land + water;
        }

        for(size_t i = 0; i < 4; i++){
            if(options.huntOrder[i] == 'N'){
                Coordinate N;
                N.x = temp.x - 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                    grid.at(N.x).at(N.y).status = 's';
                    searchLand(N);
                    return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                    grid.at(N.x).at(N.y).status = 's';
                    searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 's';
                    } 
                }
                

            }
            else if(options.huntOrder[i] == 'E'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y + 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                    grid.at(N.x).at(N.y).status = 'w';
                    searchLand(N);
                    return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'w';
                    }  
                }
            }
            else if(options.huntOrder[i] == 'S'){
                Coordinate N;
                N.x = temp.x + 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                    grid.at(N.x).at(N.y).status = 'n';
                    searchLand(N);
                    return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'n';
                        searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'n';
                    }
                }
            }
            else if(options.huntOrder[i] == 'W'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y - 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                    grid.at(N.x).at(N.y).status = 'e';
                    searchLand(N);
                    return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'e';
                        searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'e';
                    } 
                }
            } 
        }
        
    }
}

void searchSeaSS() {

    stack<Coordinate> stack;
    Coordinate start;
    start.x = xStart;
    start.y = yStart;
    stack.push(start);
    grid.at(xStart).at(yStart).status = 'v';
    while (stack.empty() == false && grid.at(stack.top().x).at(stack.top().y).symbol != '$') {
        water++;
        Coordinate temp;
        temp.x = stack.top().x;
        temp.y = stack.top().y;
        stack.pop();

        if (found == false && stack.empty()){
            notFoundlocations = land + water;
        }

        for(size_t i = 0; i < 4; i++){
            if(options.huntOrder[i] == 'N'){
                Coordinate N;
                N.x = temp.x - 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                    grid.at(N.x).at(N.y).status = 's';
                    searchLandStack(N);
                    return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                    grid.at(N.x).at(N.y).status = 's';
                    searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 's';
                    } 
                }
                

            }
            else if(options.huntOrder[i] == 'E'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y + 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLandStack(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'w';
                    }  
                }
            }
            else if(options.huntOrder[i] == 'S'){
                Coordinate N;
                N.x = temp.x + 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'n';
                        searchLandStack(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'n';
                        searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'n';
                    }
                }
            }
            else if(options.huntOrder[i] == 'W'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y - 1;
                if(isValid(N)){
                if(grid.at(N.x).at(N.y).symbol == '$'){
                    grid.at(N.x).at(N.y).status = 'e';
                    searchLandStack(N);
                    return;
                }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'e';
                        searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        stack.push(N);
                        grid.at(N.x).at(N.y).status = 'e';
                    } 
                }
            }
        }
    }
}

void searchSeaQQ() {

    queue<Coordinate> queue;
    Coordinate start;
    start.x = xStart;
    start.y = yStart;
    queue.push(start);
    grid.at(xStart).at(yStart).status = 'v';
    while (queue.empty() == false && grid.at(queue.front().x).at(queue.front().y).symbol != '$') {
        water++;
        Coordinate temp;
        temp.x = queue.front().x;
        temp.y = queue.front().y;
        queue.pop();

        if (found == false && queue.empty()){
            notFoundlocations = land + water;
        }

        for(size_t i = 0; i < 4; i++){
            if(options.huntOrder[i] == 'N'){
                Coordinate N;
                N.x = temp.x - 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 's';
                        searchLand(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                    grid.at(N.x).at(N.y).status = 's';
                    searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 's';
                    } 
                }
                

            }
            else if(options.huntOrder[i] == 'E'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y + 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLand(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'w';
                    }  
                }
            }
            else if(options.huntOrder[i] == 'S'){
                Coordinate N;
                N.x = temp.x + 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){

                        grid.at(N.x).at(N.y).status = 'n';
                        searchLand(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'n';
                        searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'n';
                    }
                }
            }
            else if(options.huntOrder[i] == 'W'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y - 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'e';
                        searchLand(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'e';
                        searchLand(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'e';
                    } 
                }
            }
        }
    }
}

void searchSeaQS() {

    queue<Coordinate> queue;
    Coordinate start;
    start.x = xStart;
    start.y = yStart;
    queue.push(start);
    grid.at(xStart).at(yStart).status = 'v';
    while (queue.empty() == false && grid.at(queue.front().x).at(queue.front().y).symbol != '$') {
        water++;
        Coordinate temp;
        temp.x = queue.front().x;
        temp.y = queue.front().y;
        queue.pop();

        if (found == false && queue.empty()){
            notFoundlocations = land + water;
        }

        for(size_t i = 0; i < 4; i++){
            if(options.huntOrder[i] == 'N'){
                Coordinate N;
                N.x = temp.x - 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){

                        grid.at(N.x).at(N.y).status = 's';
                        searchLandStack(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                    grid.at(N.x).at(N.y).status = 's';
                    searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 's';
                    } 
                }
                

            }
            else if(options.huntOrder[i] == 'E'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y + 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLandStack(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'w';
                        searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'w';
                    }  
                }
            }
            else if(options.huntOrder[i] == 'S'){
                Coordinate N;
                N.x = temp.x + 1;
                N.y = temp.y;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'n';
                        searchLandStack(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'n';
                        searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'n';
                    }
                }
            }
            else if(options.huntOrder[i] == 'W'){
                Coordinate N;
                N.x = temp.x;
                N.y = temp.y - 1;
                if(isValid(N)){
                    if(grid.at(N.x).at(N.y).symbol == '$'){
                        grid.at(N.x).at(N.y).status = 'e';
                        searchLandStack(N);
                        return;
                    }
                    if(grid.at(N.x).at(N.y).symbol == 'o'){
                        grid.at(N.x).at(N.y).status = 'e';
                        searchLandStack(N);
                        if (found) {
                            return;
                        }
                    }
                    else {
                        queue.push(N);
                        grid.at(N.x).at(N.y).status = 'e';
                    } 
                }
            }
        }
    }
}

void backTrace(vector<vector<Legend> > grid){


    Coordinate pointer = {xEnd, yEnd};
    
    back.push(pointer);        

    while(grid.at(pointer.x).at(pointer.y).status != 'v' || grid.at(pointer.x).at(pointer.y).symbol != '@'){

        

        if(grid.at(pointer.x).at(pointer.y).status == 'n'){    
            
            pointer.x = pointer.x - 1;
            pointer.y = pointer.y;
            pathLength++;
            back.push(pointer);
            boob.push(pointer);
        }
        else if(grid.at(pointer.x).at(pointer.y).status == 's'){
            
            pointer.x = pointer.x + 1;
            pointer.y = pointer.y;
            pathLength++;
            back.push(pointer);
            boob.push(pointer);
        }
        else if(grid.at(pointer.x).at(pointer.y).status == 'e'){
            
            pointer.x = pointer.x;
            pointer.y = pointer.y + 1;
            pathLength++;
            back.push(pointer);
            boob.push(pointer);
        }
        else if(grid.at(pointer.x).at(pointer.y).status == 'w'){
            
            pointer.x = pointer.x;
            pointer.y = pointer.y - 1;
            pathLength++;
            back.push(pointer);
            boob.push(pointer);
        }
        
    }

}

void standard(){
    if(found){
        cout << "Treasure found at " << xEnd << "," << yEnd << " with path length " << pathLength << ".\n";
    }else{
        cout << "No treasure found after investigating " << notFoundlocations << " locations.\n";
    }
}

void Verbose(){
    
    if(found){
    cout << "Treasure hunt started at: " << xStart << "," << yStart << "\n";
    while(ashore.empty() == false && ashore.size() != 1){
        cout << "Went ashore at: " << ashore.front().x << "," << ashore.front().y << "\n";
        cout << "Searching island... party returned with no treasure.\n";
        ashore.pop();
        }
    while(ashore.size() == 1){ 
        cout << "Went ashore at: " << ashore.front().x << "," << ashore.front().y << "\n";
        cout << "Searching island... party found treasure at " << xEnd << "," << yEnd << ".\n";
        ashore.pop();
    }
    } else {
    cout << "Treasure hunt started at: " << xStart << "," << yStart << "\n";
    while(ashore.size() != 1){
    cout << "Went ashore at: " << ashore.front().x << "," << ashore.front().y << "\n";
    cout << "Searching island... party returned with no treasure." << "\n";
    ashore.pop();
    }
    while(ashore.size() == 1){
    cout << "Went ashore at: " << ashore.front().x << "," << ashore.front().y << "\n";
    cout << "Searching island... party returned with no treasure." << "\n";
    cout << "Treasure hunt failed\n";
    ashore.pop();
    }
}
}

void Stats(){
    if(found){
    cout << "--- STATS ---\n";
    cout << "Starting location: " << xStart << "," << yStart << "\n";
    cout << "Water locations investigated: " << water << "\n";
    cout << "Land locations investigated: " << land << "\n";
    cout << "Went ashore: " << wentAshore << "\n";
    cout << "Path length: " << pathLength << "\n";
    cout << "Treasure location: " << xEnd << "," << yEnd << "\n";
    cout << "--- STATS ---\n";
    } else {
    cout << "--- STATS ---\n";
    cout << "Starting location: " << xStart << "," << yStart << "\n";
    cout << "Water locations investigated: " << water << "\n";
    cout << "Land locations investigated: " << land - 1 << "\n";
    cout << "Went ashore: " << wentAshore << "\n";
    cout << "--- STATS ---\n";    
    }

}

void coordList(){
    if(found){
    cout << "Sail:\n";
    while(back.empty() == false && grid[back.top().x][back.top().y].symbol != 'o'){
        if(grid[back.top().x][back.top().y].symbol == '$'){
            cout << "Search:" << "\n";
            cout << back.top().x << "," << back.top().y << "\n";
            return;
        }
        cout << back.top().x << "," << back.top().y << "\n";
        back.pop();
    }
    cout << "Search:" << "\n";
    while(back.empty() == false && back.size() != 1){
        
        cout << back.top().x << "," << back.top().y << "\n";
        back.pop();
    }
    while(back.empty() == false && back.size() == 1){
        
        cout << back.top().x << "," << back.top().y << "\n";
        back.pop();
    }
    }
} 

void printMap(vector<vector<Legend> > grid) {
    if(found){
    grid[xEnd][yEnd].symbol = 'X';

    Coordinate prev = {xEnd, yEnd};

    while(boob.empty() == false){
            if(grid.at(boob.front().x).at(boob.front().y).status == 'n' || grid.at(boob.front().x).at(boob.front().y).status == 's'){
                grid.at(boob.front().x).at(boob.front().y).symbol = '|';
            }
            if(grid.at(boob.front().x).at(boob.front().y).status == 'e' || grid.at(boob.front().x).at(boob.front().y).status == 'w'){
                grid.at(boob.front().x).at(boob.front().y).symbol = '-';
            }
            if(grid.at(boob.front().x).at(boob.front().y).status == 'n' || grid.at(boob.front().x).at(boob.front().y).status == 's'){
                if(grid.at(prev.x).at(prev.y).status == 'e' || grid.at(prev.x).at(prev.y).status == 'w'){
                grid.at(boob.front().x).at(boob.front().y).symbol = '+';
                }
            }
            if(grid.at(boob.front().x).at(boob.front().y).status == 'e' || grid.at(boob.front().x).at(boob.front().y).status == 'w'){
                if(grid.at(prev.x).at(prev.y).status == 's' || grid.at(prev.x).at(prev.y).status == 'n'){
                    grid.at(boob.front().x).at(boob.front().y).symbol = '+';
                }
            }


        prev.x = boob.front().x;
        prev.y = boob.front().y;
        boob.pop();
        }
        for (size_t i = 0; i < mapSize; ++i) {
            for (size_t j = 0; j < mapSize; ++j) {
                cout << grid[i][j].symbol;
        }
            cout << endl;
        }
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    int option = 0;
    int option_index = 0;

    //declarations for hunt order
    size_t n_tracker = 0;
    size_t s_tracker = 0;
    size_t e_tracker = 0;
    size_t w_tracker = 0;

    struct option longopts[] = {
        { "help", no_argument, nullptr, 'h' },
        { "captain", required_argument, nullptr, 'c' },
        { "first-mate", required_argument, nullptr, 'f'},
        { "hunt-order", required_argument, nullptr, 'o'},
        { "verbose", no_argument, nullptr, 'v'},
        { "stats", no_argument, nullptr, 's'},
        { "show-path", required_argument, nullptr, 'p'},
        { nullptr, 0, nullptr, '\0' }};

    while((option = getopt_long(argc, argv, "hc:f:o:vsp:", longopts, &option_index)) != -1) {
        switch (option){
            case 'h':
                cout << "This is a call for help";
                exit(0);
                break;

            case 'c':
                    if(string(optarg) == "QUEUE"){
                        options.captain = 'Q';
                        break;
                    }else if(string(optarg) == "STACK"){
                        options.captain = 'S';
                        break;
                    }else{
                        exit(1);
                    }

            case 'f':
                if(string(optarg) == "STACK"){
                        options.firstMate = 'S';
                        break;
                    }else if(string(optarg) == "QUEUE"){
                        options.firstMate = 'Q';
                        break;
                    }else{
                        exit(1);
                    }

            case 'o':
                options.huntOrder = string(optarg);
                if(options.huntOrder.size() != 4){
                    cout << "Invalid argument to --hunt-order\n";
                    exit(1);
                }
                for(size_t i = 0; i < 4; i++){
                    if(options.huntOrder[i] == 'N'){
                        ++n_tracker;
                    }
                    else if(options.huntOrder[i] == 'S'){
                        ++s_tracker;
                    }
                    else if(options.huntOrder[i] == 'E'){
                        ++e_tracker;
                    }
                    else if(options.huntOrder[i] == 'W'){
                        ++w_tracker;
                    }
                }

                if(!((n_tracker == 1) && (s_tracker == 1) && (e_tracker == 1) && (w_tracker == 1))){
                    exit(1);
                }
                break;

            case 'v':
                options.verbose = true;
                break;

            case 's':
                options.stats = true;
                break;

            case 'p':
                if (pathProcessed == true){
                    cerr << "Specify --show-path only once\n";
                    exit(1);
                }
                if(string(optarg) == "M"){
                    options.path = 'M';
                }else if(string(optarg) == "L"){
                    options.path = 'L';
                }else{
                    exit(1);
                }
                pathProcessed = true;
                break;

            default:
                exit(1); 
        } 
        
    }

    string b;

    while(getline(cin, b)){
        if(b[0] == '#'){
        }

        else if(b[0] == 'M'){   
            size_t bruh;
            cin >> bruh;
            
            mapSize = bruh;
            char terrain;
            grid.resize(mapSize,vector<Legend>(mapSize));
            for(size_t i = 0; i < mapSize; ++i){
                for(size_t j = 0; j < mapSize; ++j){
                    cin >> terrain;
                    grid.at(i).at(j).symbol = terrain;
                    if(terrain == '@'){
                        xStart = i;
                        yStart = j;
                    }
                }
            }
           

        if (options.captain == 'S' && options.firstMate == 'Q') {
            searchSeaSQ();

            if(found == false) {
                
            } else {

            backTrace(grid);
            }
            

            if(options.verbose == true){
                Verbose();
            }
            if(options.stats == true){
                Stats();
            }
            if(options.path == 'M'){
                printMap(grid);
            }
            if(options.path == 'L'){
                coordList();
            }
            standard();
        
        }

        else if (options.captain == 'S' && options.firstMate == 'S'){
            searchSeaSS();

            if(found == false) {
                
            } else {
            backTrace(grid);
            }
            
            if(options.verbose == true){
                Verbose();
            }
            if(options.stats == true){
                Stats();
            }
            if(options.path == 'M'){
                printMap(grid);
            }
            if(options.path == 'L'){
                coordList();
            }
            standard();

        }
        else if (options.captain == 'Q' && options.firstMate == 'Q'){
            searchSeaQQ();

            if(found == false) {
                
            } else {
            backTrace(grid);
            }
            
            if(options.verbose == true){
                Verbose();
            }
            if(options.stats == true){
                Stats();
            }
            if(options.path == 'M'){
                printMap(grid);
            }
            if(options.path == 'L'){
                coordList();
            }
            standard();
        }
        else if (options.captain == 'Q' && options.firstMate == 'S'){
            searchSeaQS();

            if(found == false) {
                
            } else {
            backTrace(grid);
            }
            
            if(options.verbose == true){
                Verbose();
            }
            if(options.stats == true){
                Stats();
            }
            if(options.path == 'M'){
                printMap(grid);
            }
            if(options.path == 'L'){
                coordList();
            }
            standard();
        }
        
        }

        else if(b[0] == 'L'){
            size_t bruh;

            cin >> bruh;
            mapSize = bruh;

            readGridList();

            if (options.captain == 'S' && options.firstMate == 'Q') {
                searchSeaSQ();
                backTrace(grid);
            
                if(options.verbose == true){
                    Verbose();
                }
                if(options.stats == true){
                    Stats();
                }
                if(options.path == 'M'){
                    printMap(grid);
                }
                if(options.path == 'L'){
                    coordList();
                }
                standard();

            }
            else if (options.captain == 'S' && options.firstMate == 'S'){
                searchSeaSS();
                if(found == false) {
                    
                } else {
                backTrace(grid);
                }
            
                if(options.verbose == true){
                    Verbose();
                }
                if(options.stats == true){
                    Stats();
                }
                if(options.path == 'M'){
                    printMap(grid);
                }
                if(options.path == 'L'){
                    coordList();
                }
                standard();
            }
            else if (options.captain == 'Q' && options.firstMate == 'Q'){
                searchSeaQQ();

            if(found == false) {
                
            } else {
            backTrace(grid);
            }
            
                if(options.verbose == true){
                    Verbose();
                }
                if(options.stats == true){
                    Stats();
                }
                if(options.path == 'M'){
                    printMap(grid);
                }
                if(options.path == 'L'){
                    coordList();
                }
                standard();
            }
            else if (options.captain == 'Q' && options.firstMate == 'S'){
                searchSeaQS();

            if(found == false) {
                
            } else {
            backTrace(grid);
            }
            
                if(options.verbose == true){
                    Verbose();
                }
                if(options.stats == true){
                    Stats();
                }
                if(options.path == 'M'){
                    printMap(grid);
                }
                if(options.path == 'L'){
                    coordList();
                }
                standard();
            }
        }
    }

}
