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
        auto _ = createSymbolsTable(true); // just to check perform some validations
    };

    string assemble() {
        auto symbolsTable = createSymbolsTable();
        string result = "";

        for(int i = 0; i < (int)text.commands.size(); i++) {
            auto command = text.commands[i].get();
            if((int)result.size() && result.back() != ' ') result += " ";
            result += command->assemble(symbolsTable);
        }

        for(int i = 0; i < (int)data.directives.size(); i++) {
            auto directive = data.directives[i].get();
            if((int)result.size() && result.back() != ' ') result += " ";
            result += directive->assemble();
        }

        return result;
    }

    map<string, int> createSymbolsTable(bool showErrors = false) {
        map<string, int> table;
        int currentPos = 0;

        for(auto &cmdpointer: text.commands) {
            auto command = cmdpointer.get();

            if((int)command->label.size()) {

                if(showErrors && table.find(command->label) != table.end()) {
                    showError("Label " + command->label + " already defined");
                }

                table[command->label] = currentPos;
            }

            currentPos += command->size();
        }

        for(auto &directiveptr: data.directives) {
            auto directive = directiveptr.get();

            if(showErrors && table.find(directive->label) != table.end()) {
                showError("Label " + directive->label + " already defined");
            }

            table[directive->label] = currentPos;
         
            currentPos += directive->size();
        }

        for(auto &ext : text.externLabels) {

            if(showErrors && table.find(ext) != table.end()) {
                showError("Label " + ext + " already defined");
            }

            table[ext] = 0; // absolute 0

        }

        return table;

    }

    bool isAnModule() {
        return text.isAnModule();
    }

    string assembleToLink() {

        string res = "";
        
        auto s = createSymbolsTable();

        { // D [definition]
            auto publicSymbols = vector<string>(text.publicLabels.begin(), text.publicLabels.end());

            sort(publicSymbols.begin(), publicSymbols.end(), [&](auto a, auto b) {
                return getLabelLocation(a, s) < getLabelLocation(b, s);
            });

            for(auto &x : publicSymbols) {
                res += "D, " + x + " " + to_string(s[x]) + "\n";
            }
        }

        { // U [use]

            vector<pair<string, int>> externSymbols;

            auto f = [&](string label) -> bool {
                for(auto &l : text.externLabels) {
                    if(toLower(l) == toLower(label)) {
                        return true;
                    }
                }
                return false;
            };

            int currentPos = 0;

            for(auto &cmdpointer: text.commands) {
                auto command = cmdpointer.get();

                vector<string> args = { command->arg };

                if(command->type == CommandType::Copy) {
                    auto cpy = dynamic_cast<CopyCommand*>(command);
                    args.push_back(cpy->arg2);
                }

                for(int k = 0; k < (int)args.size(); k++) if(f(args[k])) {
                    externSymbols.push_back(make_pair(args[k], currentPos + k + 1));
                }
                
                currentPos += command->size();
            }

            for(auto &x : externSymbols) {
                res += "U, " + x.first + " " + to_string(x.second) + "\n";
            }

        }

        { // R [relative]

            res += "R,";

            for(auto &cmd : text.commands) {
                auto command = cmd.get();

                res += " 0";

                if(command->type == CommandType::Stop) {
                    continue;
                }

                /*
                    There are two cases:
                        - If the arg is public or is declared on Data Section, it must be 1
                        - If the arg is an extern, it must be 1 too
                    
                    So, we can always append 1 for non-command entries
                */

                res += " 1";

                if(command->type == CommandType::Copy) {
                    // auto cpy = dynamic_cast<CopyCommand*>(command);
                    res += " 1";
                }

            }

            for(auto &dir : data.directives) {
                auto directive = dir.get();
                
                for(int i = 0; i < directive->size(); i++) {
                    res += " 0";
                }

            }

            res += "\n";

        }

        { // [asm]
        
            res += assemble();

        }

        return res;

    }

    string toString() {
        return text.toString() + "\n" + data.toString();
    }

};