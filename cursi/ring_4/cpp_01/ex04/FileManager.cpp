/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:45 by svilla-d          #+#    #+#             */
/*   Updated: 2024/12/23 18:59:21 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

std::string FileManager::decode_escapes(const std::string &input) {
	std::string result;
	result.reserve(input.size());

	for (size_t i = 0; i < input.size(); ++i)
	{
		if (input[i] == '\\' && (i + 1) < input.size())
		{
			++i;
			switch (input[i])
			{
				case 'n':
					result.push_back('\n');
					break;
				case 't':
					result.push_back('\t');
					break;
				case '\\':
					result.push_back('\\');
					break;
				case '0':
					result.push_back('\0');
					break;
				default:
					result.push_back(input[i]);
					break;
			}
		}
		else
			result.push_back(input[i]);
	}
	return (result);
}

std::string FileManager::read_file_content(std::ifstream& inputFile) {
	std::ostringstream buffer;
	buffer << inputFile.rdbuf();
	return (buffer.str());
}

std::string FileManager::replace_content(const std::string &fileContent,
				const std::string &s1, const std::string &s2) {
	std::string realS1 = decode_escapes(s1);
	std::string realS2 = decode_escapes(s2);

	std::string newContent = fileContent;
	size_t pos = 0;
	while ((pos = newContent.find(realS1, pos)) != std::string::npos)
	{
		newContent.erase(pos, realS1.length());
		newContent.insert(pos, realS2);
		pos += realS2.length();
	}
	return (newContent);
}

bool FileManager::write_to_file(const std::string& newFilename,
		const std::string& fileContent) {
	std::ofstream outputFile(newFilename.c_str());
	if (!outputFile) {
		handle_error("Error: Unable to create file " + newFilename);
		return (false);
	}
	outputFile << fileContent;
	outputFile.close();
	return (true);
}

bool FileManager::replace_in_file() {
	std::ifstream inputFile(filename.c_str());
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
