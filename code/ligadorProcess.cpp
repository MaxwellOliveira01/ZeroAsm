#include <bits/stdc++.h>
#include <string>
#include "util.cpp"
using namespace std;

enum SymbolType {
    publico,
    externo,
};
struct Symbol {
    SymbolType type;
    string label;
    int address;
    Symbol(char ch, string label, int address){
        if (ch == 'U') {
            this->type = externo;
        } else {
            this->type = publico;
        };
        this->label = label;
        this->address = address;
    }
    string toString() {
        string typeStr = (this->type == publico) ? "publico" : "externo";  
        return typeStr + "," + this->label + " " + to_string(this->address);  
    }
};

struct SymbolsTable {
public:
    vector<Symbol> symbols;
    SymbolsTable(string path){
        std::vector<std::string> lines = readFile(path);
        for (const auto& line : lines) {
            vector<string> tokens = getTokens(line);
            if (tokens[0][0] == 'D' || tokens[0][0] == 'U'){
                Symbol s(tokens[0][0], tokens[2], stoi(tokens[3]));
                symbols.push_back(s);
            }
        }
    }
};