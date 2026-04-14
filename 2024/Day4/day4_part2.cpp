
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 4 - Part two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isXMAS(vector <string>& wordSearch, int i, int j) {
    
    if(wordSearch[i-1][j-1] == 'M' && wordSearch[i+1][j+1] == 'S' 
        && wordSearch[i-1][j+1] == 'M' && wordSearch[i+1][j-1] == 'S') return true;

    if(wordSearch[i-1][j-1] == 'S' && wordSearch[i+1][j+1] == 'M' 
        && wordSearch[i-1][j+1] == 'S' && wordSearch[i+1][j-1] == 'M') return true;

    if(wordSearch[i-1][j-1] == 'M' && wordSearch[i+1][j+1] == 'S' 
        && wordSearch[i-1][j+1] == 'S' && wordSearch[i+1][j-1] == 'M') return true;

    if(wordSearch[i-1][j-1] == 'S' && wordSearch[i+1][j+1] == 'M' 
        && wordSearch[i-1][j+1] == 'M' && wordSearch[i+1][j-1] == 'S') return true;  
    
    return false;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    long long answer = 0; 
    vector <string> wordSearch;
    while(getline(file, input)) {
        cout << "\n" << input;
        wordSearch.push_back(input);
    }

    int count = 0;
    for(int i = 1; i < wordSearch.size() - 1; i++){
        for(int j = 1; j < wordSearch[i].size() - 1; j++){
            if(wordSearch[i][j] == 'A' && isXMAS(wordSearch, i, j)) {
                count++;
            }
        }
    }

    cout << "\n\nAnswer: " << count;

    file.close();
    return 0;
}
