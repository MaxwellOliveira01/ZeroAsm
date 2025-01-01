#include <bits/stdc++.h>
#include <string>
#include "util.cpp"
using namespace std;

enum SymbolType {
    def,
    uso,
};
struct Symbol {
    SymbolType type;
    string label;
    int address;
    Symbol(char ch, string label, int address){
        if (ch == 'U') {
            this->type = uso;
        } else {
            this->type = def;
        };
        this->label = label;
        this->address = address;
    }
    string toString() const{
        string typeStr = (this->type == def) ? "def" : "uso";  
        return typeStr + "," + this->label + " " + to_string(this->address);  
    }
};

struct SymbolsTable {
public:
    vector<Symbol> symbols;
    int fatorDeCorrecao;
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
    SymbolsTable(vector<Symbol> st_1, vector<Symbol> st_2){
        symbols.insert(symbols.end(), st_1.begin(), st_1.end());
        symbols.insert(symbols.end(), st_2.begin(), st_2.end());
    }
};

struct CodigoMontado {
    vector<int> values;
    CodigoMontado (string path){
        std::vector<std::string> lines = readFile(path);
        getTokens(lines[lines.size()-1]);
        for (const auto& valorString : getTokens(lines[lines.size()-1])) {
            values.push_back(stoi(valorString));
        }
        
    }
};

struct RelativeAddresses{
    vector<string> addresses;
    RelativeAddresses(string path){
    std::vector<std::string> lines = readFile(path);
        for (const auto& line : lines) {
            vector<string> tokens = getTokens(line);
            if (tokens[0][0] == 'R'){
                addresses.insert(addresses.end(), tokens.begin() + 2, tokens.end());
            }   
        }
    }
};

SymbolsTable geraTabelaGlobal(SymbolsTable st_1, SymbolsTable st_2){
    int fatorDeCorrecao = st_1.symbols.size();
    for (auto& symbol : st_2.symbols) {
        if(symbol.type == def){
            symbol.address += fatorDeCorrecao;
        }           
    }
    return SymbolsTable(st_1.symbols, st_2.symbols);
}