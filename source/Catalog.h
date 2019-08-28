#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <future>
#include <exception>

class Catalog{
public:
	//Constructor with directory name and file name
	Catalog(const std::string& catalog_, const std::string& file_name_);

	//Processing this directory (File splitting for multi-threaded processing)
	void Processing();

	//Single threaded processing
	std::string SingleThread(const int& begin_, const int& end_);

	//Data parsing
	std::string Parsing(std::ifstream file);
private:
	std::string catalog, file_name;
};
