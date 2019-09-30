#ifndef file_h
#define file_h

#include <vector>

#include <sstream>
#include <fstream>

struct File {
	// Member Variables

	std::string bin = "";
	std::string home = "";

	// Constructors & Destructors

	File();
	~File();

	// Member Functions

	void parse_path(std::string& path) const;

	bool read(const std::string& path, std::string& data) const;
	bool write(const std::string& path, const std::string& data) const;
};

extern File file;

std::string clean_str(const std::string& data);

std::vector<std::string> split_str(const std::string& data, const char chr = '\n', int count = -1);

#endif
