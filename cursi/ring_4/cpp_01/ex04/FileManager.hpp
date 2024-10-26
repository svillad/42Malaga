#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <sstream>

class FileManager {
private:
	std::string	filename;
	std::string	s1;
	std::string	s2;

	void		handle_error(const std::string& message);
	bool		validate(std::ifstream &inputFile,
					const std::string &filename, const std::string &s1);
	std::string	read_file_content(std::ifstream& inputFile);
	std::string	replace_content(const std::string& fileContent,
					const std::string& s1, const std::string& s2);
	bool		write_to_file(const std::string& newFilename,
					const std::string& fileContent);
	
public:
	FileManager();
	FileManager(const FileManager &f);
	FileManager(const std::string &filename,
		const std::string &s1, const std::string &s2);
	FileManager&	operator=(const FileManager &f);
	
	bool	replace_in_file(void);
};

#endif
