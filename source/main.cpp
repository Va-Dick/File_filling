//#include "profile.h"
//#include "test_runner.h"
#include "Catalog.h"

#include <exception>
#include <string>

using namespace std;

int main(){
	try{
		string catalog, file_name;
		cin >> catalog >> file_name;
		Catalog new_catalog(catalog, file_name);
		new_catalog.Processing();
	}catch(runtime_error &ex){
		cout << ex.what() << endl;
	}
	return 0;
}
