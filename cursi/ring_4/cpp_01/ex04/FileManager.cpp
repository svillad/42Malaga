#include "FileManager.hpp"

FileManager::FileManager()
	: filename("test.txt"), s1("."), s2(".") {}
	
FileManager::FileManager(const FileManager &f)
	: filename(f.filename), s1(f.s1), s2(f.s2) {}

FileManager::FileManager(const std::string& filename,
		const std::string& s1, const std::string& s2)
	: filename(filename), s1(s1), s2(s2) {}

FileManager&	FileManager::operator=(const FileManager &f) {
	if (this != &f) {
		filename = f.filename;
		s1 = f.s1;
		s2 = f.s2;
	}
	return (*this);
}

bool FileManager::validate(std::ifstream &inputFile,
		const std::string &filename, const std::string &s1) {
	if (!inputFile) {
		handle_error("Error: Unable to open file " + filename);
		return (false);
	}
	if (s1.empty()) {
		handle_error("Error: s1 cannot be empty.");
		return (false);
	}
	return (true);
}

std::string FileManager::read_file_content(std::ifstream& inputFile) {
	std::ostringstream buffer;
	buffer << inputFile.rdbuf();
	return (buffer.str());
}

std::string FileManager::replace_content(const std::string &fileContent,
		const std::string &s1, const std::string &s2) {
	std::string newContent = fileContent;
	size_t pos = 0;
	while ((pos = newContent.find(s1, pos)) != std::string::npos) {
		newContent.erase(pos, s1.length());
		newContent.insert(pos, s2);
		pos += s2.length();
	}
	return (newContent);
}

bool FileManager::write_to_file(const std::string& newFilename,
		const std::string& fileContent) {
	std::ofstream outputFile(newFilename);
	if (!outputFile) {
		handle_error("Error: Unable to create file " + newFilename);
		return (false);
	}
	outputFile << fileContent;
	outputFile.close();
	return (true);
}

bool FileManager::replace_in_file() {
	std::ifstream inputFile(filename);
	if (!validate(inputFile, filename, s1)) {
		return false;
	}
	std::string fileContent = read_file_content(inputFile);
	inputFile.close();
	std::string newContent = replace_content(fileContent, s1, s2);
	std::string newFilename = filename + ".replace";
	return (write_to_file(newFilename, newContent));
}

void FileManager::handle_error(const std::string& message) {
	std::cerr << "\e[31m" << message << "\e[0m" << std::endl;
}
