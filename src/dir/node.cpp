#include "node.h"

#include "file.h"
#include "debug.h"

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
        if (line[0] == '#' || line[0] == '\n') continue;

        // get path depth

        int numSpaces = 0;

        for (char c : line) {
            if (c == ' ') numSpaces++;
            else break;
        }

        int depth = (numSpaces / 2) + 1;

        if (depth > loc.size() + 1) return false;
        
        // clean and parse string

        std::vector<std::string> split = split_str(clean_str(line), ':', 1);

        debug.info("before: " + std::to_string(depth) + " : " + std::to_string(loc.size()));

        while (depth <= loc.size()) loc.erase(loc.end());

        loc.push_back(split[0]);

        if (split.size() > 1) {
            // line is path and value

            Node& tmp = *this;
            
            for (std::string bit : loc) tmp = tmp[bit];

            tmp = split[1];

            // get & print path

            std::string debg = "/";

            for (std::string bit : loc) debg += bit + "/";

            debg += split[1];

            debug.info("loaded : " + debg);
        }

        debug.info("after: " + std::to_string(depth) + " : " + std::to_string(loc.size()));
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

void Node::operator=(std::vector<std::string> val) {
    if (value) delete(value);

    value = new StringList(val);
}

void Node::operator=(std::initializer_list<std::string> val) {
    if (value) delete(value);

    value = new StringList(val);
}

void Node::operator=(long) {
    // so value is nullable

    if (value) {
        delete(value);

        value = nullptr;
    }
}
