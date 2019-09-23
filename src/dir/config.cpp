#include "config.h"

#include "file.h"

// Member Functions

bool Config::get_bool(const std::string& key) {
	if (bools.find(key) != bools.end()) return bools[key];

	return false;
}

int Config::get_int(const std::string& key) {
	if (ints.find(key) != ints.end()) return ints[key];

	return 0;
}

float Config::get_float(const std::string& key) {
	if (floats.find(key) != floats.end()) return floats[key];
	
	return 0.0f;
}

std::string Config::get_string(const std::string& key) {
	if (strings.find(key) != strings.end()) return strings[key];
	
	return "";
}

void Config::set_bool(const std::string& key, bool value, bool overwrite) {
	if (!overwrite && bools.find(key) != bools.end()) return;

	bools[key] = value;
}

void Config::set_int(const std::string& key, int value, bool overwrite) {
	if (!overwrite && ints.find(key) != ints.end()) return;

	ints[key] = value;
}

void Config::set_float(const std::string& key, float value, bool overwrite) {
	if (!overwrite && floats.find(key) != floats.end()) return;

	floats[key] = value;
}

void Config::set_string(const std::string& key, const std::string& value, bool overwrite) {
	if (!overwrite && strings.find(key) != strings.end()) return;

	strings[key] = value;
}

bool Config::load(const std::string& path, bool overwrite) {
	// read data from file
	
	std::string data = "";

	if (!file.read(path, data)) return false;

	// split and parse

	return parse(split_str(data));
}

bool Config::parse(const std::vector<std::string>& args, bool overwrite) {
	int state = 0;

	// loop through all arguments and parse

	for (std::string arg : args) { 
		if (arg.length() == 0 || arg[0] == '#') continue;

		std::string type = "", key = "", value = "";

		for (char c : arg) {
			if (state == 0) {
				if (c == '-' || c == ' ') continue;

				if (c != ':') type += c;
				else state++;
			}
			else if (state == 1) {
				if (c == '-' || c == ' ') continue;

				if (c != '=') key += c;
				else state++;
			}
			else value += c;
		}

		if (type == "b") set_bool(key, (value == "true" || value == "on" || value == "1"), overwrite);
		else if (type == "i") set_int(key, std::stoi(value), overwrite);
		else if (type == "f") set_float(key, std::stof(value), overwrite);
		else if (type == "s") set_string(key, value, overwrite);
		else if (state == 0) set_bool(type, true, overwrite);

		type = key = value = "";

		state = 0;
	}
	
	return true;
}
