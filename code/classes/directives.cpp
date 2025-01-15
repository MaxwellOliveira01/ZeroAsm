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
    virtual string assemble() = 0;
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
        for(auto &x : line) {
            if(toLower(x) == "const") {
                return true;
            }
        }
        return false;
        // return (int)line.size() == 4 && toLower(line[2]) == "const";
    }

    string assemble() override {
        return to_string(value);
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

    static bool isSpaceDirective(vector<string> line) {

        for(auto &x : line) {
            if(toLower(x) == "space") {
                return true;
            }
        }

        return false;

        // return ((int)line.size() == 3 || (int)line.size() == 4) 
        //     && toLower(line[2]) == "space";
    }


    int size() override {
        return value;
    }    

    string assemble() override {
        string result = "";

        for(int i = 0; i < value; i++) {
            if(i) result += " ";
            result += "0";
        }

        return result;
    }

    string toString() override {
        auto s = label + ": SPACE";
        if(value > 0) s += " " + value;
        return s;
    }
    
};
