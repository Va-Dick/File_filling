#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <algorithm>
#include <future>
#include <exception>
#include <filesystem>

#include "Paginator.h"

namespace fs = std::filesystem;

class Catalog {
public:
	//Constructor with directory name and file name
	Catalog(const std::string& catalog_, const std::string& file_name_);

	//Reading file names from a directory
	void GetFileNames();

	//Processing this directory (File splitting for multi-threaded processing)
	void Processing();

	//Single threaded processing
	template <typename Vector>
	std::string SingleThread(const Vector& part_of_vector);

	//Data parsing
	std::string Parsing(std::string name);

	~Catalog() {}
private:
	std::string catalog, file_result;
	std::vector<std::string> file_names;
};