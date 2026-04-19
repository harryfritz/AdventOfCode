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

int digits(int number) {
    if(number < 10) return 1;
    return 1 + digits(number/10);
}

vector <int> splitEvenInteger(int number) {
    int divider = 1;
    int halfDigits = digits(number) / 2;
    for(int i = 0; i < halfDigits; i++) {
        divider *= 10;
    }
    vector <int> result;
    result.push_back(number/divider);
    result.push_back(number%divider);
    return result;
}

int main() {

    ifstream file;
    file.open("input.txt");
    string input;

    vector <int> stones;
    while(getline(file, input)) {

        // cout << "\n" << input;

        for(string s : split(input, ' ')) {
            stones.push_back(stoi(s));
        }
    
    }

    vector <int> newStones;
    for(int blink = 0; blink < 25; blink++) {
        newStones.clear();
        for(int stone = 0; stone < stones.size(); stone++) {
            if(stones[stone] == 0) {
                newStones.push_back(1);
            } else if(digits(stones[stone])%2 == 0) {
                vector <int> splitStones = splitEvenInteger(stones[stone]);
                newStones.push_back(splitStones[0]);
                newStones.push_back(splitStones[1]);
            } else {
               newStones.push_back(stones[stone]*2024);
            }
            
        }
        stones = newStones;
        cout << "\nBlink " << blink << ": " << stones.size() << " Stones";
    }

    cout << "\n\nAnswer: " << stones.size();

    file.close();
    return 0;
}
