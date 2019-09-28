#ifndef node_h
#define node_h

#include <string>
#include <map>

#include "file.h"

struct Value {
    // Virtual Member Functions

    virtual ~Value() {};
};

struct Bool : public Value {
    // Member Variables

    bool value;

    // Constructors & Destructors

    Bool(bool val) : value(val) {}
};

struct Number : public Value {
    // Member Variables

    float value;

    // Constructors & Destructors

    Number(float val) : value(val) {}
};

struct String : public Value {
    // Member Variables

    std::string value;

    // Constructors & Destructors

    String(std::string val) : value(val) {}
};

struct StringList : public Value {
    // Member Variables

    std::vector<std::string> value;

    // Constructors & Destructors

    StringList(std::vector<std::string> val) : value(val) {}
};

struct Node {
    // Member Variables

    std::map<std::string, Node> children;

    Value* value = nullptr;

    // Constructors & Destructors

    Node();
    ~Node();

    // Member Functions

    bool load(const std::string& path);
    bool save(const std::string& path);

    bool as_bool(bool def = false);
    float as_num(float def = 0.0f);
    std::string as_string(std::string def = "");
    std::vector<std::string> as_string_list(std::vector<std::string> def = { });

    // Operator Overloads

    Node& operator[](std::string key);

    void operator=(bool val);
    void operator=(int val);
    void operator=(float val);
    void operator=(const char* val);
    void operator=(std::string val);
    void operator=(std::vector<std::string> val);
    void operator=(std::initializer_list<std::string> val);

    void operator=(long);
};

#endif
