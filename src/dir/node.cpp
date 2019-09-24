#include "node.h"

#include "file.h"

// Constructors & Destructors

Node::Node() {
    value = nullptr;
}

Node::~Node() {
    if (value) delete(value);
}

// Member Functions

bool Node::load(const std::string& path) {
    std::string data = "";

    // load data

	if (!file.read(path, data)) return false;

    // deserialise data

    std::vector<std::string> loc;

    for (std::string line : split_str(data)) {
        std::string clean = clean_str(line);
        
        // parse cleaned string

        std::vector<std::string> keyVal = split_str(clean, ':');

        
    }
    
    return true;
}

bool Node::save(const std::string& path) {
    std::string data = "";

    // serialise data



    // save data

    if (!file.write(path, data)) return false;

    return true;
}

bool Node::as_bool(bool def) {
    // cast to bool and return

    if (value) {
        Bool* val_cast = dynamic_cast<Bool*>(value);
 
        if (val_cast) return val_cast->value;
    }

    return def;
}

int Node::as_int(int def) {
    // cast to int and return

    if (value) {
        Int* val_cast = dynamic_cast<Int*>(value);

        if (val_cast) return val_cast->value;
    }

    return def;
}

float Node::as_float(float def) {
    // cast to float and return

    if (value) {
        Float* val_cast = dynamic_cast<Float*>(value);

        if (val_cast) return val_cast->value;
    }

    return 0.0f;
}

std::string Node::as_string(std::string def) {
    // cast to string and return

    if (value) {
        String* val_cast = dynamic_cast<String*>(value);

        if (val_cast) return val_cast->value;
    }

    return def;
}

std::vector<std::string> Node::as_string_list(std::vector<std::string> def) {
    // cast to string list and return

    if (value) {
        StringList* val_cast = dynamic_cast<StringList*>(value);

        if (val_cast) return val_cast->value;
    }

    return def;
}

// Operator Overloads

Node& Node::operator[](std::string key) {
    // if key doesn't exist add node and return

    if (children.find(key) == children.end()) children[key] = Node();

    return children.at(key);
}

void Node::operator=(bool val) {
    if (value) delete(value);

    value = new Bool(val);
}

void Node::operator=(int val) {
    if (value) delete(value);

    value = new Int(val);
}

void Node::operator=(float val) {
    if (value) delete(value);

    value = new Float(val);
}

void Node::operator=(const char* val) {
    if (value) delete(value);

    value = new String(val);
}

void Node::operator=(std::string val) {
    if (value) delete(value);

    value = new String(val);
}

void Node::operator=(std::initializer_list<std::string> val) {
    if (value) delete(value);

    value = new StringList(val);
}

void Node::operator=(std::vector<std::string> val) {
    if (value) delete(value);

    value = new StringList(val);
}

void Node::operator=(long) {
    if (value) {
        delete(value);

        value = nullptr;
    }
}
