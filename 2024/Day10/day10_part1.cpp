
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 10 - Part one
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool cointainsPair(vector <vector <int>> &trailHead, const vector <int> &pair){
    for(vector <int> pairs : trailHead){
        if(pairs == pair) return true;
    }
    return false;
}

void followPaths(vector <vector <int>>& map, vector <vector <int>> &trailHead, int row, int col, int height) {
    if(height == 9) {
        if(!cointainsPair(trailHead, {row, col})){
            trailHead.push_back({row, col});
        }
        return;
    }

    vector <vector <int>> positions;
    if(row > 0) {
        positions.push_back({map[row-1][col], row-1, col});
    }
    if(col > 0) {
        positions.push_back({map[row][col-1], row, col-1});
    }
    if(col < map[row].size() - 1){
        positions.push_back({map[row][col+1], row, col+1});
    }
    if(row < map.size() - 1){
        positions.push_back({map[row+1][col], row+1, col});
    }

    for(vector <int> position : positions) {
        if(position[0] == height+1) {
            followPaths(map, trailHead, position[1], position[2], height+1);
        } 
    }        

}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <vector <int>> map;
    while(getline(file, input)) {

        cout << "\n" << input;

        map.push_back({});
        int row = map.size() - 1;
        for(int c = 0; c < input.size(); c++) {
            map[row].push_back(input[c] - '0');
        }   
    }

    cout << "\n";
    long long answer = 0; 
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++) {
            if(map[i][j] == 0) {
                vector <vector <int>> trailHead;
                trailHead.push_back({i, j});
                followPaths(map, trailHead, i, j, 0);
                int score = trailHead.size() - 1;
                cout << "\n(" << i << "," << j << "): " << score;
                answer += score;
            }
                
        }
    }

    
    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
