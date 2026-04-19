
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 9 - Part one
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void swapPositions(vector <int>& arr, int pos1, int pos2) {
    int temp  = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;
    getline(file, input);
    
    vector <int> disk;
    int biggestFileID = 0;
    for(int c = 0; c < input.size(); c++) {
        int fileID;
        if(c%2 == 1) {
            fileID = -1; // '.'
        } else {
            fileID = c/2;
            biggestFileID = fileID;
        }
        for(int i = 0; i < input[c] - '0'; i++) {
            disk.push_back(fileID);
        }
    }

    int pointCursor = 0;
    int numberCursor = disk.size() - 1;
    bool compacted = false;
    while(!compacted) {
        while(disk[pointCursor] != -1) pointCursor++;
        while(disk[numberCursor] == -1) numberCursor--;
        if(numberCursor < pointCursor) {
            compacted = true;
        } else {
            swapPositions(disk, pointCursor, numberCursor);
        }
    }

    long long answer = 0; 
    int block = 0;
    while(disk[block] != -1){
        answer += block * disk[block];
        block++;
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
