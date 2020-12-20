#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

/** Función utilitaria para reemplazar pattern por otra cadena
 */
string replaceAll(string &origin, 
					const string &pattern, 
					const string &destiny) {
	int n = 0;
	while( (n=origin.find(pattern,n)) != string::npos ) {
		origin.replace( n, pattern.size(), destiny);
		n+=destiny.size();
	}
	return origin;
}

/**
 * Obtiene el nombre del archivo con un formato correcto
 */
string getfilename(const string &path) {
	int idx = path.rfind('/')+1;
	string file = path.substr(idx);
	//replaceAll(file," ", "\\ ");
	//replaceAll(file,"(", "\\(");
	//replaceAll(file,")", "\\)");
	return file;
}

/**
 * Obtiene el tiempo actual en una string y adiciona un salto de línea
 */
string printTimestamp() {
	time_t result = time(nullptr);
    return asctime(localtime(&result));
}

/**
 * Lee los archivos contenidos en una carpeta.
 */
void readFiles( const string &path, 
				vector<string> &files
				  ) {
	for( const auto & entry : fs::directory_iterator(path)){
		if ( entry.is_directory() ) 
			readFiles( entry.path(), files );
		else files.push_back( getfilename(entry.path()));
		//else files.push_back( entry.path() );
	}
}