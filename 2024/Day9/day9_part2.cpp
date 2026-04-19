
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 9 - Part two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void swapPositions(vector <int>& disk, int pos1, int pos2) {
    int temp  = disk[pos1];
    disk[pos1] = disk[pos2];
    disk[pos2] = temp;
}

void swapBlocks(vector <int>& disk, int block1Pos, int block2Pos, int size) {
    for(int i = 0; i < size; i++) {
        swapPositions(disk, block1Pos + i, block2Pos + i);
    }
}

int emptyBlockSize(vector <int>& disk, int pos){
    int size = 0;
    while(disk[pos] == -1) {
        size++; 
        pos++;
        if(pos >= disk.size()) break;
    }
    return size;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;
    getline(file, input);
    
    vector <int> disk;
    vector <vector <int>> blocksMap;
    int biggestFileID = 0;
    for(int c = 0; c < input.size(); c++) {
        int fileID;
        if(c%2 == 1) {
            fileID = -1; // '.'
        } else {
            fileID = c/2;
            biggestFileID = fileID;
            int blockPos = disk.size();
            blocksMap.push_back({input[c] - '0', blockPos});
        }
        for(int i = 0; i < input[c] - '0'; i++) {
            disk.push_back(fileID);
            
        }
    }

    for(int fileID = biggestFileID; fileID >= 0; fileID--) {
        
        for(int block = 0; block < blocksMap[fileID][1]; block++) {
            if(emptyBlockSize(disk, block) >= blocksMap[fileID][0]) {
                swapBlocks(disk, block, blocksMap[fileID][1], blocksMap[fileID][0]);
            }
        }
    }

    long long answer = 0; 
    for(int block = 0; block < disk.size(); block++) {
        if(disk[block] != -1) {
            answer += block * disk[block];
        }
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
