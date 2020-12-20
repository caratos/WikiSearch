// This implementation is in here:
// https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
// C++ program for implementation of KMP pattern searching 
// algorithm 

#ifndef KMPSEARCH
#define KMPSEARCH

#include <string> 
#include <iostream> 
#include <algorithm> 
#include <vector> 

using namespace std;
  
void computeLPSArray(const string &pat, int M, int* lps); 
  
// Prints occurrences of txt[] in pat[] 
bool KMPSearch(const string &pat, const string &txt) 
{ 
    int M = pat.size();
    int N = txt.size();
  
    // create lps[] that will hold the longest prefix suffix 
    int lps[M]; 
  
    // Preprocess the pattern (calculate lps[] array) 
    computeLPSArray(pat, M, lps); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    while (i < N) { 
        if (tolower(pat[j]) == tolower(txt[i])) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            return true; // It is not necessary keep searching
            j = lps[j - 1]; 
        } 
  
        // mismatch after j matches 
        else if (i < N && tolower(pat[j]) != tolower(txt[i])) { 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    }
    return false;
} 
  
// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(const string &pat, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            if (len != 0) { 
                len = lps[len - 1]; 
  
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 



vector<string> split(const string &entry) {
    
    vector<string> words;
    
    string word="";
    for( int i=0; i<entry.size(); i++ ) {
        if( entry[i] == ' ') {
            if( word != "" ) {
                words.push_back(word);
                word = "";
            } 
        }else {
            word += entry[i];
        }
    }
    if( word != "")
        words.push_back(word);

    return words;
}

  
// Driver program to test above function 
/*int main() 
{ 
    //char txt[] = "amigo MIO como estas MIO "; 
    //char pat[] = "mio"; 
    char txt[] = "colombiana shakira en la cancion oficial del mundial       waka waka  esto es";
    char pat[] = "waka";
    if( KMPSearch(string(pat), string(txt)) )
        cout<< "FOUND!" << endl;
    return 0; 
}*/
/*
int main() {
    for(string word : split("esto es una       prueba") ) {
        cout << word << endl;
    }
}*/

#endif