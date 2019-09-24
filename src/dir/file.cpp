#include "file.h"

#ifdef __linux__
	#include <limits.h>
	#include <unistd.h>
	#include <libgen.h>
#elif WIN32
    //#include <>
#endif

File file;

// Constructors & Destructors

File::File() {
	// get current working directory

	char exe[PATH_MAX];

	if (readlink("/proc/self/exe", exe, PATH_MAX) != -1) bin = std::string(dirname(exe)) + "/";

	// get home environment variable

	home = getenv("HOME");
}

File::~File() {
	
}

// Member Functions

void File::parse_path(std::string& path) const {
	if (path[0] == '~') path.replace(0, 1, home);
	
	if (path[0] != '/') path.replace(0, 0, bin);
}

bool File::read(const std::string& path, std::string& data) const {
	// open file stream, return on fail

    std::ifstream file(path);
	
    if (file.fail()) return false;

	// read file contents

	std::stringstream buffer;

	buffer << file.rdbuf();

	data = buffer.str();

	// close file stream
	
	file.close();
	
	return true;
}

bool File::write(const std::string& path, const std::string& data) const {
	// open file stream, return on fail

    std::ofstream file(path);

    if (file.fail()) return false;

	// write file contents

    file << data;

	// close file stream

    file.close();

    return true;
}

std::string clean_str(const std::string& data) {
	std::string result = "";

	// remove whitespace outside of quotations

	bool escaped = false;
	bool quoted = false;

	for (char c : data) {
		if (escaped) {
			result += c;

			escaped = false;
		}
		else {
			if (c == '\\') escaped = true;
			else if (c == '\"') quoted = !quoted;
			else if (c != ' ' || (quoted && c == ' ')) result += c;
		}
	}

	return result;
}

std::vector<std::string> split_str(const std::string& data, const char chr) {
	// split on given character, newline by default

	std::vector<std::string> result { "" };

	for (char i : data) {
		if (i != chr) result.back() += i;
		else result.push_back("");
	}

	if (result.back() == "") result.erase(result.end());

	return result;
}
