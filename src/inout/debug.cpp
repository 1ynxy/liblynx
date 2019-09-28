#include "debug.h"

Debug debug;

// Constructors & Destructors

Debug::Debug(int level) : verbosity(level) {

}

Debug::~Debug() {
	
}

// Member Functions

void Debug::print(int level, const std::string& message) const {
	if (level < verbosity) return;

	std::cout << "[" << dltostr(level) << "] " << message << "\n";
}

void Debug::info(const std::string& message) const {
	print(0, message);
}

void Debug::warn(const std::string& message) const {
	print(1, message);
}

void Debug::error(const std::string& message) const {
	print(2, message);
}

std::string Debug::dltostr(int verbosity) const {
	// converts debug numeric value to string

	switch (verbosity) {
		case 0 : return "INFO";
		case 1 : return "WARN";
		case 2 : return "ERROR";
		default : return "NONE";
	}
}
