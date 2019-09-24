#ifndef config_h
#define config_h

#include <string>
#include <map>

struct Config {
private:
    // Member Variables

    std::map<std::string, bool> bools = std::map<std::string, bool>();
    std::map<std::string, int> ints = std::map<std::string, int>();
    std::map<std::string, float> floats = std::map<std::string, float>();
    std::map<std::string, std::string> strings = std::map<std::string, std::string>();
public:

    // Member Functions

    bool get_bool(const std::string& key);
    int get_int(const std::string& key);
    float get_float(const std::string& key);
    std::string get_string(const std::string& key);

    void set_bool(const std::string& key, bool value = true, bool overwrite = true);
    void set_int(const std::string& key, int value, bool overwrite = true);
    void set_float(const std::string& key, float value, bool overwrite = true);
    void set_string(const std::string& key, const std::string& value, bool overwrite = true);

    bool load(const std::string& path, bool overwrite = false);
    bool parse(const std::vector<std::string>& args, bool overwrite = false);
};

#endif
