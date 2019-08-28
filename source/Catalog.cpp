#include "Catalog.h"

Catalog::Catalog(const std::string& catalog_, const std::string& file_name_){
	catalog = catalog_;
	file_name = file_name_;
	std::replace(catalog.begin(), catalog.end(), '\'', '/');
	if(!std::ifstream(catalog + "/" + file_name)){
		throw std::runtime_error("Error: file does not exist, "
				"make sure the data is entered correctly");
	}
}

void Catalog::Processing(){
	std::ofstream file(catalog + "/" + file_name);
	if(!file){
		throw std::runtime_error("Error: file does not exist, "
				"make sure the data is entered correctly");
	}
	std::vector<std::future<std::string>> futures;
	int step = 50;											//Number of files processed by one thread
	for(int i = 1;; i += step){
		futures.push_back(std::async([=] {
			return SingleThread(i, i + step);}));
		if(!std::ifstream(catalog + "/" + std::to_string(i + step) + ".txt")){
			break;
		}
	}
	for (auto& f: futures) {
		file << move(f.get());
	}
}

std::string Catalog::SingleThread(const int& begin_, const int& end_){
	std::string return_value;
	for(int i = begin_; i < end_; i++){
		std::ifstream file(catalog + "/" + std::to_string(i) + ".txt");
		if(!file){
			break;
		}
		return_value += move(Parsing(move(file)));
	}
	return move(return_value);
}

std::string Catalog::Parsing(std::ifstream file){
	std::string tokens, line, result;
	getline(file, tokens);
	getline(file, line);

	std::string_view str = move(line);
	while(true){
		size_t token = str.find_first_of(tokens);
		result += str.substr(0, token);
		result += "\n";
		if(token == str.npos){
			break;
		}
		else{
			str.remove_prefix(token + 1);
		}
	}
	return move(result);
}
