#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

using namespace std;
namespace fs = filesystem;

ofstream logFile("report.log");
char command[1024];

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
	}
}

/**
 * Por cada archivo, ejecutar el html2text
 */
void executeHtml2Text( const vector<string> &files, 
						const string & fromPath,  
						const string &toPath,
						const string &errorPath ){
	int nfiles = 1;
	for( string file : files ){
		logFile << "Executing html2text: " << file << "...";
		sprintf(command,"html2text -utf8 '%s/%s' > '%s/%s' 2>> %s", fromPath.c_str(),file.c_str(), toPath.c_str(), file.c_str(), errorPath.c_str()  );
		system( command );
		logFile << " Done!" << endl;

		if( nfiles++ % 1000 == 0 ){ 
			cout << "Until now: " << (nfiles-1) << " procesed with html2text " << endl;
			cout << "current time: " << printTimestamp();
		}
	}
	logFile.flush();
}

/**
 * Elimina los archivos vacios de una cadena
 */
void eraseEmptyFiles(const string &path ) {
	for( const auto & entry : fs::directory_iterator(path)){
		if ( entry.is_directory() ) 
			eraseEmptyFiles( entry.path() );
		else {
			if( entry.file_size() == 0 ) {
				logFile << "Removing ... " << entry.path() << "...";
				remove( entry.path() );
				logFile << "Done!" << endl;
			}
		}
	}
	logFile.flush();
}

int main() {
	string fromPath ="workdir/A";
	string toPath = "Processed";
	string html2textErrorPath = "html2text.error.log";
	vector<string> files;

	logFile << "STARTING ... " << printTimestamp() << endl;

	logFile << "=> Start reading " << printTimestamp();
	readFiles( fromPath, files);
	logFile << "Read files: " << files.size() << endl;

	logFile << "\n=> Executing with html2text " << printTimestamp();
	executeHtml2Text(files, fromPath, toPath, html2textErrorPath);

	logFile << "\n=> Erasing empty files " << printTimestamp();
	eraseEmptyFiles(toPath);


	return 0;
}
