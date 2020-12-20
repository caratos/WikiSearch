/**
@author Carlos Eduardo Atencio Torres
@email catencio@unsa.edu.pe
@date 2020

*/
#include "utilities.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
using namespace std;


regex rgx("[^[:punct:][:space:][:digit:]]+");
vector<string> getAllWords(string seq) {
    vector<string> words;
    
    for( sregex_iterator it(seq.begin(), seq.end(),rgx), it_end; it != it_end; it++) {
        string data = it->str() ;
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if( data.size() > 0)
            words.push_back(data);
    }
    return words;
}


int main() {
    string fromPath = "Processed";
    vector<string> files;
    map<string,int> words;
    readFiles( fromPath, files);
    int nfiles = 1;
    string line;
    cout << "Counting the words in " << fromPath << ":"<< endl;
    for( string fileName : files) {
        ifstream file(fromPath +"/"+fileName);

        if( (++nfiles)%10000 == 0 ) {
            cout << "Processed: " << nfiles << endl;
            cout << printTimestamp();
        }

        while( getline(file, line)) {
            //cout << line << endl;
            for( string word : getAllWords(line) )
                words[word]++;
        }
    }
    int freqMax = 0;
    string freqMaxString = "";
    int sizeMax = 0;
    string sizeMaxString = "";
    
    for( map<string, int>::const_iterator it = words.begin(); it != words.end(); it++) {
        if( it->second > freqMax){
            freqMax = it->second;
            freqMaxString = it->first;
        }
        if( it->first.size() > sizeMax ) {
            sizeMax = it->first.size();
            sizeMaxString = it->first;
        }
    }

    ofstream logFile("conta-palabras.log");
    logFile << "*****************************" << endl;
    logFile << "Total of words: " << words.size() << endl;
    logFile << "Most frequency word: [" << freqMaxString << "] with " << freqMax << " occurrences" << endl;
    logFile << "Longest word: [" << sizeMaxString << "] with " << sizeMax << " characters" << endl;

    return 0;
}
