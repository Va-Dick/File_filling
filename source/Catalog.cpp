#include "Catalog.h"

Catalog::Catalog(const std::string& catalog_, const std::string& file_result_) {
	catalog = catalog_;
	file_result = file_result_;
	std::replace(catalog.begin(), catalog.end(), '\\', '/');			//Validation
	if (!std::ifstream(catalog + "/" + file_result)) {
		throw std::runtime_error("file " + catalog + "/" + file_result + " does not exist, "
			"make sure the data is entered correctly");
	}
	GetFileNames();
}

void Catalog::GetFileNames() {
	for (auto& entry : fs::directory_iterator(catalog)) {				//Getting a list of files
		std::string file = entry.path().u8string();
		file.erase(begin(file), ++(find(begin(file), end(file), '\\')));
		if (file_result != file) {
			file_names.push_back(file);
		}
	}
}

void Catalog::Processing() {
	std::ofstream file(catalog + "/" + file_result);
	std::vector<std::future<std::string>> futures;
	
	size_t size_part_of_vector = (file_names.size() > std::thread::hardware_concurrency()) ?
		file_names.size() / std::thread::hardware_concurrency() : file_names.size();		//Getting the optimal number of files per stream
	for (auto part_of_vector : Paginate(file_names, size_part_of_vector)) {					//Divide the vector into parts
		futures.push_back(std::async([=] { return SingleThread(part_of_vector); }));
	}
	for (auto& f : futures) {
		file << move(f.get());
	}
}

template <typename Vector>
std::string Catalog::SingleThread(const Vector& part_of_vector) {
	std::string return_value;
	for (const auto& name : part_of_vector) {
		return_value += move(Parsing(name));
	}
	return move(return_value);
}

std::string Catalog::Parsing(std::string name) {
	std::ifstream file(catalog + "/" + name);
	if (!file) {
		throw std::runtime_error("problem opening resource file " + catalog + "/" + name);
	}
	std::string line_, token, tokens, result;
	getline(file, line_);
	std::string_view line = line_;

	while (getline(file, token)) {
		if (token != "") {
			tokens += move(token);
		}
	}
	while (true) {
		size_t find_token = line.find_first_of(tokens);
		result += line.substr(0, find_token);
		result += "\n";
		if (find_token == line.npos) {
			break;
		}
		else {
			line.remove_prefix(find_token + 1);
		}
	}
	return move(result);
}