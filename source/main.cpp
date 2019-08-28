#include "Catalog.h"

#include <exception>
#include <iostream>
#include <string>

using namespace std;

int main() {
	try {
		cout << "Enter directory name and file name" << endl;

		string catalog, file_name;
		cin >> catalog >> file_name;
		Catalog new_catalog(catalog, file_name);
		new_catalog.Processing();

		cout << "The program completed without errors" << endl;
	}
	catch (runtime_error& ex) {
		cout << "Error: " << ex.what() << endl;
	}
	return 0;
}