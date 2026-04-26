/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 11 - Part one
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector <string> split(const string& text, char delim) {
    vector <string> tokens;
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        if(nextDelim >= 0) {
            cursor = nextDelim;
            while(text[cursor] == delim) cursor++;
        }
    }
    return tokens;
}

int digits(long long number) {
    if(number < 10) return 1;
    return 1 + digits(number/10);
}

long long evenIntegerDivider(long long number) {
    long long divider = 1;
    int halfDigits = digits(number) / 2;
    for(int i = 0; i < halfDigits; i++) {
        divider *= 10;
    }
    return divider;
}

int main() {

    ifstream file;
    file.open("input.txt");
    string input;

    vector <long long> stones;
    while(getline(file, input)) {

        // cout << "\n" << input;

        for(string s : split(input, ' ')) {
            stones.push_back(stoll(s));
        }
    
    }

    vector <long long> newStones;
    for(int blink = 0; blink < 75; blink++) {
        newStones.clear();
        for(long long stone = 0; stone < stones.size(); stone++) {
            long long stoneValue = stones[stone];
            if(stoneValue == 0) {
                newStones.push_back(1);
            } else if(digits(stoneValue)%2 == 0) {
                long long divider = evenIntegerDivider(stoneValue);
                newStones.push_back(stoneValue/divider);
                newStones.push_back(stoneValue%divider);
            } else {
               newStones.push_back(stoneValue*2024);
            }
            
        }
        stones = newStones;
        
        cout << "\nBlink " << blink << ": " << stones.size() << " Stones";

    }

    cout << "\n\nAnswer: " << stones.size();

    file.close();
    return 0;
}
