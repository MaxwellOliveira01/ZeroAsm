#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
#endif

using namespace std;

enum DirectiveType {
    SPACE,
    CONST,
};

struct Directives { // abstract
    string label;
    DirectiveType type;
    virtual ~Directives() = default;
    virtual string toString() = 0;
    virtual int size() = 0;
    Directives(string label_, DirectiveType type_) : label(label_), type(type_) {}
};

struct ConstDirective : Directives {
    
    int value;

    ConstDirective(string label_, int value_): Directives(label_, DirectiveType::CONST), value(value_) {

    };

    int size() override {
        return 1;
    }

    static bool isConstDirective(vector<string> line) {
        return (int)line.size() == 4 && toLower(line[2]) == "const";
    }

    string toString() override {
        return label + ": CONST " + to_string(value);
    }

};

struct SpaceDirective : Directives {

    int value;

    SpaceDirective(string label_): Directives(label_, DirectiveType::SPACE), value(1) {
        
    }

    SpaceDirective(string label_, int value_): Directives(label_, DirectiveType::SPACE), value(value_) {

    }

    int size() override {
        return value;
    }

    static bool isSpaceDirective(vector<string> line) {
        return ((int)line.size() == 3 || (int)line.size() == 4) 
            && toLower(line[2]) == "space";
    }

    string toString() override {
        auto s = label + ": SPACE";
        if(value > 0) s += " " + value;
        return s;
    }
    
};
