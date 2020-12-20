/**
 * @file main.cpp
 * @author Carlos Atencio Torres (catencio@unsa.edu.pe)
 * @brief 
 * @version 0.1
 * @date dec 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef WIKIPEDIALOADER
#define WIKIPEDIALOADER

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <cstdlib>

using namespace std;

typedef map<int, map<char,int> > GRAPH;

class WikiLoader {
private:
    GRAPH *graph;
    GRAPH* initGraph( const string &filename );
    bool getEdge(const string &line, int &orig, int &dest, char &label);
    void getAll(const string &word, const int &state, vector<string> &results );
    regex edgeRegex;
    set<int> endstates;

public:
    WikiLoader( const string &path );
    string search(const string &word);
    vector<string> searchApproximately( const string &word);

    void print();
};

#endif