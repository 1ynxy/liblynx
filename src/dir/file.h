#ifndef file_h
#define file_h

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

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

std::vector<std::string> split_str(const std::string& data, const char chr = '\n');

extern File file;

#endif
