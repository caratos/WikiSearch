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
#include "WikipediaLoader.h"
#include "StringUtil.h"

/* global variables; */
WikiLoader *unary, *binary, *trinary;
map<int,string> documents;
string baseOfAsciiDocuments;

/* util functions */
void loadDocuments(const string &listofNames) {
    ifstream in(listofNames);
    string line;
    int number;
    while( in >> number ) {
        in.ignore();
        getline(in,line);
        documents[number] = line;
    }
}

string getWord(const string &entry) {
    return entry.substr(0, entry.find('/') );
}

int getNumberOfDocument(const string &entry) {
    int pos1 = entry.find("/")+1;
    int pos2 = entry.find_last_of(".")-pos1;
    return atoi(entry.substr(pos1,pos2).c_str() );
}

string getDocument(const string &entry) {
    return documents[ getNumberOfDocument(entry) ];
}

string getLineFromDocument(const string &entry) {
    int number = getNumberOfDocument(entry);
    char correctName[32];
    sprintf(correctName,"%07d.txt",number); //To make wikipedia happens
                                            // 7 is because of the size of the max string for a filename
    
    ifstream in( baseOfAsciiDocuments + correctName );

    string line ;
    int counter = 1;
    string word = getWord(entry);
    
    while( getline(in,line) ) {
        if( KMPSearch(word, line ) ) {
            ostringstream out;
            out << " Line [" << counter << "]: " << line ;
            return out.str();
        }

        counter++;
    }

    in.close();

    return ""; //Didn't found it, should not happen
    
}

/* menu */
//(my skills in menu are a little rusty)
void welcome() {
    cout << "******************************************" << endl;
    cout << "* Welcome to the wikipedia searcher v0.1 *" << endl;
    cout << "* author: Carlos Atencio Torres          *"  << endl;
    cout << "* 2020 - Year of covid                   *"  << endl;
    cout << "******************************************" << endl;
}

string searchmenu1() {
    cout<< "\nInsert an entry you want to search ['q' for leaving]" << endl;
    string option;
    getline(cin, option);
    return option;
}

void searchmenu2(const string &word, WikiLoader *selected) {
    string option;
    cout << "  We sorry, the entry "<< word << " is not exactly in wikipedia" << endl;
    cout << "  maybe, do you want an exhaustive search? it could take some minutes [y/n]" << endl;
    cout << "  ";
    getline(cin, option);
    if( option[0] == 'y' || option[0]=='Y') {
        vector<string> options = selected->searchApproximately( word );
        if( options.empty() )  {
            cout << "  I am afraid there is no such an entry in wikipedia " << endl;
        } else {
            cout << "  There are " << options.size() << " entries" << endl;
            cout << "  do you want to print them all ? [y/n]" << endl;
            cout << "  ";
            getline(cin, option);
            if( option[0] == 'y' || option[0]=='Y') {
                for (int i = 0; i < options.size(); i++) {
                    cout << "    ["<< (i+1) << "]  \"" << getWord(options[i]) << "\"   está en  " << getDocument(options[i]) << endl;;
                }
            }
            else {
                cout << "  wisdom decision" << endl;
            }
        }
    }
    else {
        cout << "  Ok!"<<endl;
    }
}

/* MAIN */
int main() {
    welcome();
    cout << "Loading wikipedia documents... take it easy, this can take some seconds.. " << endl;


    
    baseOfAsciiDocuments = "/disksdd/Doctorado/Wikipedia/Ascii/";
    cout << "Loading unary" <<endl;
    unary = new WikiLoader("/disksdd/Doctorado/Wikipedia/models/wikipedia-unario-total.dot");
    //WARNING: uncomment this only if you have at least 5Gb available of RAM
    cout << "Loading binary" <<endl;
    binary = new WikiLoader("/disksdd/Doctorado/Wikipedia/models/wikipedia-binario-100k.dot");

    //WARNING: uncomment this only if you have at least 10Gb available of RAM
    //cout << "Loading trinary" <<endl;
    //trinary = new WikiLoader("/disksdd/Doctorado/Wikipedia/models/wikipedia-trinario-20k");

    loadDocuments("/disksdd/Doctorado/Wikipedia/code/list-of-names.txt");

    string word, opt1;


    while( (opt1 = searchmenu1()) != "q" ) {
        vector<string> words = split(opt1);
        string result = "";
        WikiLoader * selected = NULL;
        if( words.size() == 1){
            result = unary->search(opt1);
            selected = unary;
        }

        //WARNING: Uncomment this only if you have at least 5GB of available RAM
        else if( words.size() == 2) {
            result = binary->search(opt1);
            selected = binary;
        }

	// WARNING: Uncomment this only if you have at least 10GB of available ram
	/*
        else if( words.size() == 3) {
            result = trinary->search(opt1);
            selected = trinary;
        }*/

	else {
            //TODO: maybe try to implement something with unary for each word.
            cout << "I am sorry, I was not prepared for such a query" << endl;
            continue;
        }

        if( result.empty() )
            searchmenu2(opt1, selected);
        else {
            cout << "Fine!, I got ["<< opt1 << "] in " << getDocument(result) <<"/"<<result<< endl;
            cout << getLineFromDocument(result) << endl;
            cout.flush();
        }
    }
    

    return 0;
}
