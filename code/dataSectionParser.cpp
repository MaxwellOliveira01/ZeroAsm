
#include <bits/stdc++.h>

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
    virtual string toString();
    Directives(string label_, DirectiveType type_) : label(label_), type(type_) {}
};

struct ConstDirective : Directives {
    
    // TODO: change it to int?
    string value; // needs to handle decimal, hexadecimal and binary

    ConstDirective(string label_, string value_): Directives(label_, DirectiveType::CONST), value(value_) {

    };

    string toString() override {
        return label + ": CONST " + value;
    }

};

struct SpaceDirective : Directives {

    string value; // str?

    SpaceDirective(string label_): Directives(label_, DirectiveType::SPACE) {
        
    }

    SpaceDirective(string label_, string value_): Directives(label_, DirectiveType::SPACE), value(value_) {

    }

    string toString() override {
        auto s = label + ": SPACE";
        if((int)value.size()) s += " " + value;
        return s;
    }
    
};

struct Data {

    vector<shared_ptr<Directives>> directives;

    Data() = default;

    Data(vector<vector<string>> parsedLines) {
        directives = vector<shared_ptr<Directives>>();
        for(auto &line : parsedLines) {

            if((int)line.size() == 0) {
                continue;
            }

            if(isConstDirective(line)) {
                directives.push_back(make_unique<ConstDirective>(line[0], line.back()));
            } else if(isSpaceDirective(line)){

                auto d = (int)line.size() == 4 ?
                    SpaceDirective(line[0], line.back()) :
                    SpaceDirective(line[0]);

                directives.push_back(make_unique<SpaceDirective>(d));
            } else {
                string message = "Invalid directive: ";
                for(auto &x: line) message += x + " ";
                throw runtime_error(message);
            }
        }
    }

    string toString() {
        string s = "SECTION DATA\n"; 

        for(auto &d : directives) {
            s += d.get()->toString() + "\n";
        }

        return s;        
    }

};

struct PreProcessedData {

    vector<string> lines;

    PreProcessedData() = default;

    PreProcessedData(vector<vector<string>> parsedLines) {
        lines = vector<string>();
        
        for(auto &line : parsedLines) {
        
            if((int)line.size() == 0) {
                continue;
            }

            // just ignore empty lines and comments

            string result = "";

            for(int i = 0; i < (int)line.size(); i++) {
                result += line[i];
                if(i + 1 < (int)line.size() && line[i + 1] != ":") {
                    result += " ";
                }
            }

            lines.push_back(result);
        
        }
    }

    string toString() {
        string s = "SECTION DATA\n";

        for(int i = 0; i < (int)lines.size(); i++) {
            s += lines[i];
            if(i + 1 < (int)lines.size()) {
                s += "\n";
            }
        }
        
        return s;  
    }


};