#ifndef debug_h
#define debug_h

#include <iostream>
#include <string>

struct Debug {
	// Member Variables

	int verbosity;

	// Constructors & Destructors

	Debug(int level = 0);
	~Debug();

	// Member Functions

	void print(int level, const std::string& message) const;

	void info(const std::string& message) const;
	void warn(const std::string& message) const;
	void error(const std::string& message) const;

	std::string dltostr(int verbosity) const;
};

extern Debug debug;

#endif
