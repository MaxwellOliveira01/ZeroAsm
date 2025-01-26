#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
#endif

#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED
#include "debug.cpp"
#endif

#ifndef COMMAND_INCLUDED
#define COMMAND_INCLUDED
#include "classes/command.cpp"
#endif

using namespace std;

struct Text {
    vector<shared_ptr<Command>> commands;
    
    set<string> externLabels;
    set<string> publicLabels;

    string moduleName = "";
    bool hasBegin = false, hasEnd = false;

    Text(vector<vector<string>> parsedLines) {
        commands = vector<shared_ptr<Command>>();
        string pastLabels = "";

        for(auto &line : parsedLines) {

            if((int)line.size() == 0) {
                continue;
            }

            string label = "";

            if(hasLabel(line)) {
                
                if((int)pastLabels.size()) {
                    // Bringing an label of an empty line to current line would make 
                    // it invalid (more than one label in a row)
                    showError("More than one label in a row: " + pastLabels + " and " + line[0]);
                } else {
                    label = line[0];
                    line = split(line, 2, (int)line.size());
                    
                    if((int)line.size() == 0) {
                        pastLabels = label;
                        continue;
                    }

                    // Already removed label from line, but we need to check for another one
                    
                    if(hasLabel(line)) {
                        showError("More than one label in a row: " + label + " and " + line[0]);
                    }

                }
            } else if((int)pastLabels.size()) {
                label = pastLabels;
                pastLabels = "";
            }

            // BEGIN: MOD1

            if((int)label.size() && toLower(label) == "begin") {

                if(hasBegin) {
                    showError("Module has more than one begin");
                }

                hasBegin = true;
                moduleName = (int)line.size() ? line[0] : "";
                continue;

            }

            if((int)line.size() && toLower(line[0]) == "end") {
                if(hasEnd) {
                    showError("Module has more than one end");
                }
                hasEnd = true;
                continue;
            }

            if((int)line.size() && toLower(line[0]) == "extern") {
                if(!(int)label.size()) {
                    showError("Extern must have an non empty label");
                }
                externLabels.insert(label);
                continue;
            }

            if((int)line.size() && toLower(line[0]) == "public") {
                if((int)line.size() != 2) {
                    showError("Public field must have exactly one field after, it will be ignored", line);
                }
                publicLabels.insert(line[1]);
                continue;

            }

            auto cmd = ValidateAndCreateClassObj(label, line);

            if(cmd != nullptr) {
                commands.push_back(cmd);
            }

        }

        if(hasBegin && !hasEnd) {
            showError("Module has begin, but doenst have end");
        } else if(!hasBegin && hasEnd) {
            showError("Module has end, but doesnt have begin");
        }

        // if((int)pastLabels.size()) {
        //     throw runtime_error("Invalid label localtion: " + pastLabels);
        // }

    }

    shared_ptr<Command> ValidateAndCreateClassObj(string label, vector<string> line) {

        if((int)label.size() && !isLabelNameValid(label)) {
            showError("Invalid label name: '" + label + "', it will be ignored", line);
            return nullptr;
        }

        if(AddCommand::IsAddCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Add)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<AddCommand>(label, line[1]);
        }

        if(SubCommand::IsSubCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Sub)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<SubCommand>(label, line[1]);
        }
        
        if(MultCommand::IsMultCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Mult)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<MultCommand>(label, line[1]);
        }
        
        if(DivCommand::IsDivCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Div)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<DivCommand>(label, line[1]);
        }
        
        if(JmpCommand::IsJmpCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Jmp)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<JmpCommand>(label, line[1]);
        }
        
        if(JmpnCommand::IsJmpnCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Jmpn)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<JmpnCommand>(label, line[1]);
        }
        
        if(JmppCommand::IsJmppCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Jmpp)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<JmppCommand>(label, line[1]);
        }
        
        if(JmpzCommand::IsJmpzCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Jmpz)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<JmpzCommand>(label, line[1]);
        }
        
        if(CopyCommand::IsCopyCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Copy) + 1 /* comma after arg1 */) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<CopyCommand>(label, line[1], line[3]);
        }
        
        if(LoadCommand::isLoadCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Load)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<LoadCommand>(label, line[1]);
        }
        
        if(StoreCommand::isStoreCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Store)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<StoreCommand>(label, line[1]);
        }
        
        if(InputCommand::isInputCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Input)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<InputCommand>(label, line[1]);
        }
        
        if(OutputCommand::isOutputCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Output)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<OutputCommand>(label, line[1]);
        }
        
        if(StopCommand::isStopCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Stop)) {
                showError("Invalid number of arguments, it will be ignored", line);
            }

            return make_shared<StopCommand>(label);
        }

        showError("Invalid instruction, it will be ignored", line);
        return nullptr;

    }

    bool isAnModule() {
        return hasBegin || hasEnd;
    }

    string toString() {
        string s = "SECTION TEXT"; 

        for(auto &d : commands) {
            s += "\n" + d.get()->toString();
        }

        return s;  
    }

};

struct Macro {

    string name;
    vector<string> args;
    vector<vector<string>> body;

    Macro() = default;

    Macro(string name_, vector<string> args_, vector<vector<string>> body_) {
        name = name_;
        args = args_;
        body = body_;
    }

    vector<vector<string>> apply(vector<string> lineArgs) {
        
        // if((int)lineArgs.size() != (int)args.size()) { // idk if pre processor should throw errors
        //     showErrorAndExit("Invalid number of arguments in macro " + name);
        // }

        map<string, string> argsMap;

        for(int i = 0; i < (int)args.size(); i++) {
            argsMap[args[i]] = i < (int)lineArgs.size() ? lineArgs[i] : args[i];
        }

        vector<vector<string>> afterApply;

        for(auto &line : body) {
            vector<string> newLine;

            for(auto &token : line) {
                newLine.push_back( argsMap.count(token) ? argsMap[token] : token );
            }

            afterApply.push_back(newLine);
        }

        return afterApply;
    }

};

struct PreProcessedText {

    vector<string> body;   

    map<string, int> MNT; // macro name table: macro name -> index in MDT
    vector<Macro> MDT; // macro definition table: macro index -> macro

    PreProcessedText() = default;

    PreProcessedText(vector<vector<string>> lineTokens) {

        auto lineTokensWithoutMacros = buildMacrosTableAndGetCleanText(lineTokens);
        auto lineTokensWithoutEmptyLabels = vector<vector<string>>();

        string label = "";

        for(auto &line : lineTokensWithoutMacros) {

            while(hasLabel(line)) {
                label += line[0] + ": ";
                line = split(line, 2, (int)line.size());
            }

            if((int)line.size() == 0) {
                continue;
            }

            auto tmp = line;

            if((int)label.size()) {
                tmp.insert(tmp.begin(), label);
            }

            // just to ensure NUM + k will be in the same token
            lineTokensWithoutEmptyLabels.push_back(getTokens(buildLineStr(tmp))); 

            label = "";
        }

        applyMacros(lineTokensWithoutEmptyLabels);

        for(auto &line : lineTokensWithoutEmptyLabels) {
            body.push_back(buildLineStr(line));
        }

    }

    vector<vector<string>> buildMacrosTableAndGetCleanText(vector<vector<string>> lineTokens) {
        
        vector<vector<string>> lineTokensWithoutMacros;

        for(int i = 0; i < (int)lineTokens.size(); i++) {
            if((int)lineTokens[i].size() == 0) continue;
            
            // we can ignore macros without names because we cant use them
            if(!hasLabel(lineTokens[i]) || (int)lineTokens[i].size() < 3 || toLower(lineTokens[i][2]) != "macro") {
                lineTokensWithoutMacros.push_back(lineTokens[i]);
                continue;
            }

            auto name = lineTokens[i][0];
            auto args = split(lineTokens[i], 3, (int)lineTokens[i].size()); // ignoring label, ':', and 'macro'
            auto macroBody = vector<vector<string>>();

            int j = i;

            while(++j < (int)lineTokens.size()) {
                int pk = hasLabel(lineTokens[j]) ? 2 : 0;
                
                if(toLower(lineTokens[j][pk]) == "endmacro") {
                    break;
                }

                macroBody.push_back(lineTokens[j]);
            }

            MNT[name] = (int)MDT.size();
            MDT.push_back(Macro(name, args, macroBody));

            i = j; // skip macro lines
        }

        return lineTokensWithoutMacros;

    }

    void applyMacros(vector<vector<string>>& lines) {

        /*
        One macro can call another macro, so we need to solve these dependencies.
        The easiest way to do this is just try to apply all macros N times, where N is the number of macros.
        This works because we have two scenarios:
            1 - Theres an cycle in the macros, so we cant solve it in anyway
            2 - If theres no cycle, the graph of dependencies is a Directed Acyclic Graph (DAG)
                and in DAGs with N nodes, the longest path is N - 1, so if we try to apply all macros N times,
                all depedencies will be solved. This algorithm use the ideia of BellmanFord algorithm to find shortest path
        */

        for(int k = 0; k < (int)MNT.size() + 1; k++) {

            vector<vector<string>> newLines;

            for(auto &line : lines) {
                int p = hasLabel(line) ? 2 : 0;

                if(p < (int)line.size() && MNT.count(line[p])) {
                    // get the arguments and apply the macro
                    auto macro = MDT[MNT[line[p]]];
                    auto args = split(line, p + 1, (int)line.size());
                    auto appliedMacro = macro.apply(args); 
                    newLines.insert(newLines.end(), appliedMacro.begin(), appliedMacro.end());
                } else {
                    // just copy line
                    newLines.push_back(line);
                }

            }

            lines = newLines;
        }

    }

    string buildLineStr(vector<string> tokens) {

        // "instruction"
        string result = tokens[0]; 

        set<char> dontNeedSpaceBefore = {',', '+', ':'};
        set<char> dontNeedSpaceAfter = {',', '+'};

        for(int k = 1; k < (int)tokens.size(); k++) {
            if((int)result.size() && dontNeedSpaceAfter.count(result.back())) {
                result += tokens[k];
            } else if(dontNeedSpaceBefore.count(tokens[k][0])) {
                result += tokens[k];
            } else {
                result += " " + tokens[k];
            }
        }

        return result;

    }

    string toString() {
        string s = "SECTION TEXT";

        for(int i = 0; i < (int)body.size(); i++) {
            s += "\n" + body[i];
        }
        
        return s;  
    }

};