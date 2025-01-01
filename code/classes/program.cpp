#include <bits/stdc++.h>

#ifndef DATASECTION_INCLUDED
#define DATASECTION_INCLUDED
#include "dataSectionParser.cpp"
#endif

#ifndef TEXT_INCLUDED
#define TEXT_INCLUDED
#include "textSectionParser.cpp"
#endif

using namespace std;

struct Program {

    Data data;
    Text text;

    Program(Data data_, Text text_): data(data_), text(text_) {
        auto _ = createSymbolsTable(); // just to check if it's valid
    };

    map<string, int> createSymbolsTable() {
        map<string, int> table;
        int currentPos = 0;

        for(auto &cmdpointer: text.commands) {
            auto command = cmdpointer.get();

            if((int)command->label.size()) {

                if(table.find(command->label) != table.end()) {
                    showErrorAndExit("Label " + command->label + " already defined");
                }

                table[command->label] = currentPos;
            }

            currentPos += command->size();
        }

        for(auto &directiveptr: data.directives) {
            auto directive = directiveptr.get();

            if(table.find(directive->label) != table.end()) {
                showErrorAndExit("Label " + directive->label + " already defined");
            }

            table[directive->label] = currentPos;
         
            currentPos += directive->size();
        }
    
        return table;

    }

    string toString() {
        return data.toString() + "\n" + text.toString();
    }

};


/*
Rotulo ausente
Rotulo dobrado na mesma linha OK
Rotudo redefinido OK
Numero de operandos errada p uma instrucao
Erros lexicos de rotulos OK
Instrução ou diretiva inválida OK
*/