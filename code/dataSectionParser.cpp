
#include <bits/stdc++.h>

#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
#endif

#ifndef DIRECTIVES_INCLUDED
#define DIRECTIVES_INCLUDED
#include "classes/directives.cpp"
#endif

using namespace std;

struct Data {

    vector<shared_ptr<Directives>> directives;

    Data(vector<vector<string>> parsedLines) {
        directives = vector<shared_ptr<Directives>>();
        for(auto &line : parsedLines) {
            
            if((int)line.size() == 0) {
                continue;
            }

            directives.push_back(ValidateAndCreateClassObj(line));

        }
    }

    shared_ptr<Directives> ValidateAndCreateClassObj(vector<string> tokens) {

        if(!hasLabel(tokens)) {
            showErrorAndExit("Data section must have a label", tokens);
            return nullptr; // unreachable
        }

        if(!isLabelNameValid(tokens[0])) {
            showErrorAndExit("Invalid label name: " + tokens[0], tokens);
            return nullptr; // unreachable
        }

        if(ConstDirective::isConstDirective(tokens)) {
            
            int value = 0;

            if(!isHexNumber(tokens.back(), value)) { // add tests!!
                if(!isDecNumber(tokens.back(), value)) {
                    showErrorAndExit("Invalid const directive value", tokens);
                    return nullptr; // unreachable
                }
            }

            return make_unique<ConstDirective>(tokens[0], value);
        
        } else if(SpaceDirective::isSpaceDirective(tokens)){

            if((int)tokens.size() == 3) {
                return make_unique<SpaceDirective>(tokens[0]);
            } else {

                int value = 0;

                if(!isDecNumber(tokens.back(), value)) {
                    showErrorAndExit("Invalid space directive value", tokens);
                    return nullptr; // unreachable
                } else if(value <= 0) {
                    showErrorAndExit("Space directive value must be greater than 0", tokens);
                    return nullptr; // unreachable
                }

                return make_unique<SpaceDirective>(tokens[0], value);
            }

        } else {
            showErrorAndExit("Invalid directive at data section", tokens);
            return nullptr; // unreachable
        }
    }

    bool LabelIsConst(string label) {
        for(auto &d : directives) {
            if(d.get()->label == label && d.get()->type == DirectiveType::CONST) {
                return true;
            }
        }

        return false;
    }

    string toString() {
        string s = "SECTION DATA"; 

        for(auto &d : directives) {
            s += "\n" + d.get()->toString();
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