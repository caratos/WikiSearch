#include "WikipediaLoader.h"

/**
 * @brief This is going to load  a file but in a graphviz format 
 * 
 * @param filename 
 * @return GRAPH 
 */

WikiLoader::WikiLoader( const string &path) {

    this->graph = initGraph(path);

    edgeRegex = regex("([0-9]+) -> ([0-9]+) \\[label=\"(.)\"\\];");
}

GRAPH* WikiLoader::initGraph(const string &filename) {
    GRAPH *graph = new  GRAPH();
    ifstream input(filename);
    
    char line[128]; // actually no line is greater than 100 characters
    
    //reading the header of the file (3 lines)
    input.getline(line, 128);
    input.getline(line, 128);
    input.getline(line, 128);
    
    // now reading the rest of lines until we find "}". 
    // If we find a line starting with '#' is a comment and we should ommit it
    for( input.getline(line, 128); line[0] !='}'; input.getline(line, 128) ) {
        if( line[0] =='#'  )  continue;

        // get the edge and insert into the graph
        int orig,dest;
        char label;
        if( getEdge(line, orig, dest, label) ) {
            if( graph->count(orig) ==0 ){
                (*graph)[orig] = {{label,dest}};
            } else {
                (*graph)[orig][label] = dest;
            }
        }
    }

    return graph;

}


/**
 * @brief Read an edge.
 * 
 * @param line 
 * @param orig 
 * @param dest 
 * @param label 
 * @return true 
 * @return false 
 */
bool WikiLoader::getEdge(const string &line, int &orig, int &dest, char &label) {
    smatch sm;
    
    // TODO: try to answer why this regex doesn't work
    /*if( regex_match( line, sm, edgeRegex) ) {
        orig = atoi(sm[1].str().c_str());
        dest = atoi(sm[2].str().c_str());
        label = sm[3].str()[0];
        return true;
    }*/
    string arrow, labelstring;
    istringstream in(line);
    in>>orig>>arrow;
    if( arrow[0] == '-' ){
        in>>dest;
        in>>labelstring;
        label = labelstring[8];
        return true;
    } else {
        endstates.insert(orig);
    }

    return false;
}

string WikiLoader::search(const string &word) {
    string result="";
    int state = 0; //initial state
    for( char c : word ) {
        if( (*graph)[state].count(c) == 0 ) {
            return "";
        }
        state = (*graph)[state][c];
    }
    if ((*graph)[state].count('/') != 0 ){
        result = word + "/";

        state = (*graph)[state]['/'];
        while( endstates.count(state) == 0  ) {
            result += (*graph)[state].begin()->first;
            state = (*graph)[state].begin()->second;
        }
    }
    return result;
}

vector<string> WikiLoader::searchApproximately( const string &word) {
    int state = 0; //initial state

    vector<string> results;
    for( char c : word ) {
        if( (*graph)[state].count(c) == 0 ) {
            return results; //empty because it is impossible to form such word
        }
        state = (*graph)[state][c];
    }
    getAll(word, state, results );
    
    return results;
}

void WikiLoader::getAll(const string &word, const int &state, vector<string> &results ) {
    if( endstates.count(state) != 0 ) {
        results.push_back( word );
    } else {
        for( auto const &it : (*graph)[state] ) {
            getAll(word+it.first, it.second, results );
        }
    }
}

void WikiLoader::print() {
    for( auto const &it1 : (*graph) ) {
        for( auto const &it2 : it1.second ) {
            cout << it1.first << ' ' << it2.second << ' ' << it2.first << endl;
        }
    }
}

