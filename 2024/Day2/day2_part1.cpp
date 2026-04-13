/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 2 - Part one
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

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    int answer = 0; 
    while(getline(file, input)) {

        // Print input to inform Safe or Unsafe
        cout << "\n" << input << ": ";
        
        // Build vector 'report' with all current levels
        vector <string> reportStr = split(input, ' ');
        vector <int> report;
        for(string level : reportStr) {
            report.push_back(stoi(level));
        }

        // Traverse 'report'
            // Tendency start 0. 1 means Increasing, -1 means Decreasing
        bool safe = true;
        int tendency = 0;
        for(int level = 1; level < report.size() && safe; level++) {
            if(tendency == 1) {
                if(report[level] <= report[level - 1]) safe = false;
                if(report[level] > report[level - 1] + 3) safe = false;
            } else if(tendency == -1){
                if(report[level] >= report[level - 1]) safe = false;
                if(report[level] < report[level - 1] - 3) safe = false;
            } else {
                if(report[level] > report[level - 1]) tendency = 1;
                if(report[level] < report[level - 1]) tendency = -1;
                if(report[level] > report[level - 1] + 3 || report[level] < report[level - 1] - 3 || report[level] == report[level - 1]) safe = false;

            }
        }

        // Print if Safe or Unsafe
        // Increase 'answer' if Safe
        if(safe) {
            cout << "Safe";
            answer++;
        } else {
            cout << "Unsafe";
        }
        
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}