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

SymbolsTable geraTabelaGlobal(int fatorDeCorrecao, SymbolsTable st_1, SymbolsTable st_2){
    for (auto& symbol : st_2.symbols) {
        if(symbol.type == def){
            symbol.address += fatorDeCorrecao;
        }           
    }
    // Remover as linhas de uso:
    vector<Symbol> st_1_semUso;
    for (auto& symbol : st_1.symbols) {
        if(symbol.type == def){
            st_1_semUso.push_back(symbol);
        }           
    }
    vector<Symbol> st_2_semUso;
    for (auto& symbol : st_2.symbols) {
        if(symbol.type == def){
            st_2_semUso.push_back(symbol);
        }           
    }
    return SymbolsTable(st_1_semUso, st_2_semUso);
}
bool in( int valor, vector<string> list){
    for (auto& c : list) {
        if (stoi(c)==valor){
            return true;
        }       
    }
    return false;
}
void corrigeEnderecos(CodigoMontado cm_1, CodigoMontado cm_2, SymbolsTable stG, SymbolsTable usoSt_1, SymbolsTable usoSt_2, RelativeAddresses ra_2){
    for (auto& simboloASerCorrigido : usoSt_1.symbols) {
        if(simboloASerCorrigido.type == uso){
            for (auto& simboloDefinido : stG.symbols) {
                if(simboloASerCorrigido.label == simboloDefinido.label){
                    cm_1.values[simboloASerCorrigido.address] += simboloDefinido.address;
                }           
            }
        }           
    }
    vector<string> indicesUsados;
    for (auto& simboloASerCorrigido : usoSt_2.symbols) {
        if(simboloASerCorrigido.type == uso){
            for (auto& simboloDefinido : stG.symbols) {
                if(simboloASerCorrigido.label == simboloDefinido.label){
                    indicesUsados.push_back(to_string(simboloASerCorrigido.address));
                    cm_2.values[simboloASerCorrigido.address] += simboloDefinido.address;
                }           
            }
        }           
    }
    for (int i = 0; i < ra_2.addresses.size(); i++) {
    // Verificar se o valor em ra_2.addresses[i] é 1 e se o índice i não é encontrado em ra_2.addresses
        if (stoi(ra_2.addresses[i]) == 1 && !(in(i, indicesUsados))) {
            cm_2.values[i] += cm_1.values.size(); // fator de correção
        }
    }
    vector<int> codigoMontadoLigado = cm_1.values;
    codigoMontadoLigado.insert(codigoMontadoLigado.end(), cm_2.values.begin(), cm_2.values.end());
    string resultado;
    for (auto& c : codigoMontadoLigado) {
        resultado +=  std::to_string(c)+ " ";       
    }
    writeToFile("prog1.e", resultado);
}

