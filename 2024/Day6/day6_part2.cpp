
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 6 - Part two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char rotateGuard(char guard) {
    if(guard == '^') return '>';
    if(guard == '>') return 'v';
    if(guard == 'v') return '<';
    if(guard == '<') return '^';
    return '^';
}

// 1=up, 2=right, 3=down, 4=left
char guardTrail(char guard) {
    if(guard == '^') return '1';
    if(guard == '>') return '2';
    if(guard == 'v') return '3';
    if(guard == '<') return '4';
    return '1';
}

bool guardPath(vector <string>& map) {
    int guardX, guardY;
    for(int s = 0; s < map.size(); s++) {
        for(int c = 0; c < map[s].size(); c++) {
            if(map[s][c] == '^'){
                guardX = c;
                guardY = s;
            } 
        }
    }

    bool exit = false;
    bool loop = false;
    while(!exit && !loop) {
        int nextX = guardX;
        int nextY = guardY;
        if(map[guardY][guardX] == '^') {            
            nextY--;
        } else if(map[guardY][guardX] == '>') {
            nextX++;
        } else if(map[guardY][guardX] == 'v') {
            nextY++;
        } else if(map[guardY][guardX] == '<') {
            nextX--;
        }

        if(nextX < 0 || nextX >= map[0].size() || nextY < 0 || nextY >= map.size()) {
            exit = true;
            map[guardY][guardX] = guardTrail(map[guardY][guardX]);
        } else {
            if(map[nextY][nextX] == '.' || map[nextY][nextX] >= '1' && map[nextY][nextX] <= '4') {
                map[nextY][nextX] = map[guardY][guardX];
                map[guardY][guardX] = guardTrail(map[guardY][guardX]); 
                guardX = nextX;
                guardY = nextY;
            } else if(map[nextY][nextX] == '#' || map[nextY][nextX] == 'O') {
                map[guardY][guardX] = rotateGuard(map[guardY][guardX]);
                map[nextY][nextX] = '5';
            } else if(map[nextY][nextX] >= '5') {
                map[guardY][guardX] = rotateGuard(map[guardY][guardX]);
                map[nextY][nextX]++;
                if(map[nextY][nextX] >= '9'){
                    loop = true;
                    map[nextY][nextX] = '9';
                }
            }
        }

    }
   
    return loop;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <string> clearMap;
    while(getline(file, input)) {
        // cout << "\n" << input;
        clearMap.push_back(input);   
    }

    int OGguardX, OGguardY;
    for(int s = 0; s < clearMap.size(); s++) {
        for(int c = 0; c < clearMap[s].size(); c++) {
            if(clearMap[s][c] == '^'){
                OGguardX = c;
                OGguardY = s;
            } 
        }
    }

    vector <string> noLoopMap = clearMap;
    guardPath(noLoopMap);
    
    long long answer = 0;
    for(int i = 0; i < noLoopMap.size(); i++) {
        for(int j = 0; j < noLoopMap[i].size(); j++) {
            if(noLoopMap[i][j] >= '1' && noLoopMap[i][j] <= '4') {
                if(!(i == OGguardY && j == OGguardX)) {
                    vector <string> map = clearMap;
                    map[i][j] = 'O';
                    if(guardPath(map)) {
                        answer++;
                    }  
                }
            }
        }
    }
    
    // cout << "\n";
    // for(string s : map){
    //     cout << "\n" << s;
    //     for(char c : s) {
    //         if(c == 'X') answer++;
    //     }
    // }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
