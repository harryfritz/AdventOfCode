/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 10 - Part two Recursive
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define INF 1000000

vector <vector <vector <int>>> allCombinations;

void combinationUtil(vector <vector <int>>& buttons, int ind, int r, 
                        vector <vector <vector <int>>>& combinations, vector <vector <int>>& dataArr) {
    int n = buttons.size();

    if(ind == 0) {
        dataArr.clear();
        combinations.clear();
    }
    
    if(dataArr.size() == r) {
        combinations.push_back(dataArr);
        return;
    }

    for(int i = ind; i < n; i++) {
        dataArr.push_back(buttons[i]);
        combinationUtil(buttons, i + 1, r, combinations, dataArr);
        dataArr.pop_back();
    }
}

vector <string> split(const string& text, char delim) {
    vector <string> tokens;
    
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        cursor = nextDelim + 1;
    }

    return tokens;
}

int minBtnPresses(vector <int>& joltages) {

    bool zero = true;
    for(int i = 0; i < joltages.size() && zero; i++) {
        if(joltages[i] < 0) {
            return INF;
        } else if(joltages[i] != 0) {
            zero = false;
        }
    }
    if(zero) {
        return 0;
    }
    
    // int globalMultiplier = 1;
    // bool _allEven = true;
    // while(_allEven) {
    //     for(int j : joltages)if(j%2==1) _allEven = false;
    //     if(_allEven){
    //         for(int i = 0; i < joltages.size(); i++) joltages[i] /= 2;
    //         globalMultiplier *= 2;
    //     }
    // }

    // Com globalMultiplier: Erro linhas 76 e 149
    // Sem globalMultiplier: Erro linhas 24 e 168

    int minPresses = INF;

    // Goes through every combination checking which patterns match joltages
    for(int btnComb = 0; btnComb < allCombinations.size(); btnComb++) {
        
        // pattern adds all buttons from a given combination. Ex.: (1,3) (1,2) = [0101] [0110] = [0211]
        vector <int> pattern = allCombinations[btnComb][0];
        for(int btn = 1; btn < allCombinations[btnComb].size(); btn++) {
            for(int i = 0; i < pattern.size(); i++) {
                pattern[i] += allCombinations[btnComb][btn][i];
            }
        } 

        // Check if pattern matches parity with joltages. If yes, moves forward
        bool validComb = true;
        for(int i = 0; i < pattern.size() && validComb; i++) {
            if((pattern[i] % 2) != (joltages[i] % 2) || pattern[i] > joltages[i]){
                validComb = false;
            }
        }

        if(validComb){
            vector <int> joltagesCache = joltages;
            int multiplier = 1;
            
            for(int i = 0; i < joltagesCache.size(); i++) joltagesCache[i] -= pattern[i];

            bool allEven = true, allZero = false;
            while(allEven && !allZero){
                for(int i = 0; i < joltagesCache.size(); i++) joltagesCache[i] /= 2;
                multiplier = multiplier*2;
                
                allZero = true;
                for(int j : joltagesCache) {
                    if(j%2==1) {
                        allEven = false;
                        allZero = false;
                    } else if(j!=0) {
                        allZero = false;
                    }
                } 
            }  

            int min = multiplier*minBtnPresses(joltagesCache) + allCombinations[btnComb].size();
            if(min < minPresses){
                minPresses = min;
            }

        }

    }

    bool _allEven = true;
    for(int j : joltages)if(j%2==1) _allEven = false;
    
    
    if(minPresses == INF && _allEven){
        int globalMultiplier = 1;
        while(_allEven) {
            for(int j : joltages)if(j%2==1) _allEven = false;
            if(_allEven){
                for(int i = 0; i < joltages.size(); i++) joltages[i] /= 2;
                globalMultiplier *= 2;
            }
        }
        
        int min = globalMultiplier*minBtnPresses(joltages);
        if(min < minPresses){
            minPresses = min;
        }
    }

    // return globalMultiplier * minPresses;
    return minPresses;
    
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    ofstream output("output.txt");
    output << "My Solution\n";

    vector <int> joltages;
    vector <vector <int>> buttons;

    int answer = 0;

    for(int line = 0; getline(file, input); line++) {        
        
        vector <string> tokens = split(input, ' ');
        tokens.erase(tokens.begin());

        joltages.clear();
        string inner = tokens.back().substr(1, tokens.back().size() - 2);
        vector <string> joltagesStr = split(inner, ',');

        for(string j : joltagesStr) {
            joltages.push_back(stoi(j));
        }
        
        tokens.pop_back();
        buttons.clear();

        for (string token : tokens) {
            
            vector <int> button;
            string inner = token.substr(1, token.size() - 2);
            vector<string> buttonsStr = split(inner, ',');

            for(int j : joltages) button.push_back(0);
            for (string t : buttonsStr) {
                button[stoi(t)] = 1;
            }
            buttons.push_back(button);
        }

        if(line == 26) {
            
            // Populate allCombinations with every possible button combination from 1 to buttons.size()
            allCombinations.clear();
            for(int i = 1; i <= buttons.size(); i++) {
                vector <vector <vector <int>>> combinations;
                vector <vector <int>> dataArr;
                combinationUtil(buttons, 0, i, combinations, dataArr);
                for(vector <vector <int>> combination : combinations) {
                    allCombinations.push_back(combination);
                }
            }
            
            int presses = minBtnPresses(joltages);
            answer += presses;
            cout << "\nLine " << line << " - " << presses << " Presses";
             output << "\n" << presses;
        }
 
    }

    
    
    cout << "\n\nAnswer: " << answer;
    output << "\n\nAnswer: " << answer;
    
    
    file.close();
    return 0;
    
}
