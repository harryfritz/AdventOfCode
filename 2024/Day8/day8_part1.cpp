
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 8 - Part one
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

vector <int> getAntinodeCoord(vector <int> ant1, vector <int> ant2) {
    vector <int> antinode;
    antinode.push_back(ant2[0] - ant1[0] + ant2[0]);
    antinode.push_back(ant2[1] - ant1[1] + ant2[1]);
    return antinode;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <string> antennaMap;
    vector <string> antinodeMap;
    while(getline(file, input)) {
        cout << "\n" << input;
        antennaMap.push_back(input);
        antinodeMap.push_back(string(input.size(),'.'));
    }

    long long answer = 0;
    for(int y1 = 0; y1 < antennaMap.size(); y1++) {
        for(int x1 = 0; x1 < antennaMap[y1].size(); x1++) {
            if(antennaMap[y1][x1] != '.') {
                vector <int> ant1 = {x1,y1};
                for(int y2 = 0; y2 < antennaMap.size(); y2++) {
                    for(int x2 = 0; x2 < antennaMap[y2].size(); x2++) {
                        if(antennaMap[y2][x2] == antennaMap[y1][x1] && x1 != x2 && y1 != y2) {
                            vector <int> ant2 = {x2,y2};
                            vector <int> antinode = getAntinodeCoord(ant1, ant2);
                            if(antinode[0] >= 0 && antinode[0] < antinodeMap[0].size() && 
                                antinode[1] >= 0 && antinode[1] < antinodeMap.size() && antinodeMap[antinode[1]][antinode[0]] != '#') {
                                    antinodeMap[antinode[1]][antinode[0]] = '#';
                                    answer++;
                                }
                        }
                    }
                }
            } 
        }
    }

    cout << "\n";
    for(string s : antinodeMap) {
        cout << "\n" << s;
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
