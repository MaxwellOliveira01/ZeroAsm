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
                
                if(toLower(line[0]) == "begin") {

                    if((int)line.size() <= 2) {
                        showErrorAndExit("Module must have a name", line);
                    }

                    hasBegin = true;
                    moduleName = line[2];
                    continue;
                }

                if((int)pastLabels.size()) {
                    // Bringing an label of an empty line to current line would make 
                    // it invalid (more than one label in a row)
                    showErrorAndExit("More than one label in a row: " + pastLabels + " and " + line[0]);
                } else {
                    label = line[0];
                    line = split(line, 2, (int)line.size());
                    
                    if((int)line.size() == 0) {
                        pastLabels = label;
                        continue;
                    }

                    // Already removed label from line, but we need to check for another one
                    
                    if(hasLabel(line)) {
                        showErrorAndExit("More than one label in a row: " + label + " and " + line[0]);
                    }

                }
            } else if((int)pastLabels.size()) {
                label = pastLabels;
                pastLabels = "";
            }

            if((int)line.size() && toLower(line[0]) == "end") {
                hasEnd = true;
                pastLabels = label;
                continue;
            }

            auto cmd = ValidateAndCreateClassObj(label, line);

            if(cmd != nullptr) {
                commands.push_back(cmd);
            }

        }

        if(hasBegin && !hasEnd) {
            showErrorAndExit("Module has begin, but doenst have end");
        } else if(!hasBegin && hasEnd) {
            showErrorAndExit("Module has end, but doesnt have begin");
        }

        // if((int)pastLabels.size()) {
        //     throw runtime_error("Invalid label localtion: " + pastLabels);
        // }

    }

    shared_ptr<Command> ValidateAndCreateClassObj(string label, vector<string> line) {

        if((int)label.size() && !isLabelNameValid(label)) {
            showErrorAndExit("Invalid label name: '" + label + "'");
            return nullptr; // unreachable
        }

        if(hasBegin) {

            if((int)line.size() && toLower(line[0]) == "extern") {
                if(!(int)label.size()) {
                    showErrorAndExit("Extern must have an non empty label");
                }
                externLabels.insert(label);
                return nullptr;
            }

            if((int)line.size() && toLower(line[0]) == "public") {

                // if((int)label.size()) {
                //     showErrorAndExit("You cannot have an label to an public field");
                // }

                if((int)line.size() != 2) {
                    showErrorAndExit("Public field must exactly one field after", line);
                }

                publicLabels.insert(line[1]);
                return nullptr;

            }

        }

        if(AddCommand::IsAddCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Add)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<AddCommand>(label, line[1]);
        }

        if(SubCommand::IsSubCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Sub)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<SubCommand>(label, line[1]);
        }
        
        if(MultCommand::IsMultCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Mult)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<MultCommand>(label, line[1]);
        }
        
        if(DivCommand::IsDivCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Div)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<DivCommand>(label, line[1]);
        }
        
        if(JmpCommand::IsJmpCommand(line)) {

            if((int)line.size() != Command::size(CommandType::Jmp)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<JmpCommand>(label, line[1]);
        }
        
        if(JmpnCommand::IsJmpnCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Jmpn)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<JmpnCommand>(label, line[1]);
        }
        
        if(JmppCommand::IsJmppCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Jmpp)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<JmppCommand>(label, line[1]);
        }
        
        if(JmpzCommand::IsJmpzCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Jmpz)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<JmpzCommand>(label, line[1]);
        }
        
        if(CopyCommand::IsCopyCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Copy) + 1 /* comma after arg1 */) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<CopyCommand>(label, line[1], line[3]);
        }
        
        if(LoadCommand::isLoadCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Load)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<LoadCommand>(label, line[1]);
        }
        
        if(StoreCommand::isStoreCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Store)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<StoreCommand>(label, line[1]);
        }
        
        if(InputCommand::isInputCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Input)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<InputCommand>(label, line[1]);
        }
        
        if(OutputCommand::isOutputCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Output)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<OutputCommand>(label, line[1]);
        }
        
        if(StopCommand::isStopCommand(line)) {
            
            if((int)line.size() != Command::size(CommandType::Stop)) {
                showErrorAndExit("Invalid number of arguments", line);
            }

            return make_shared<StopCommand>(label);
        }

        showErrorAndExit("Invalid instruction", line);
        return nullptr; // unreachable

    }

    bool isAnModule() {
        return (int)moduleName.size() > 0;
    }

    string toString() {
        string s = "SECTION TEXT"; 

        for(auto &d : commands) {
            s += "\n" + d.get()->toString();
        }

        return s;  
    }

};

struct PreProcessedText {

    vector<string> lines;

    PreProcessedText() = default;

    PreProcessedText(vector<vector<string>> parsedLines) {
        lines = vector<string>();

        vector<string> pastLabels;

        for(auto &line : parsedLines) {
            if((int)line.size() == 0) {
                continue;
            }

            string label = "";

            if(hasLabel(line)) {
                pastLabels.push_back(line[0]);
                line = split(line, 2, (int)line.size());
            }

            if((int)line.size() == 0) {
                continue;
            }

            string result = "";

            for(auto &x : pastLabels) {
                result += x + ": ";
            }

            // "instruction"
            result += line[0]; 

            for(int i = 1; i < (int)line.size(); i++) {
                if((int)result.size() && (result.back() == ',' || result.back() == '+')) {
                    result += line[i];
                } else if(line[i][0] == ',' || line[i][0] == '+') {
                    result += line[i];
                } else {
                    result += " " + line[i];
                }
            }

            lines.push_back(result);

            pastLabels.clear();

        }
    }

    string toString() {
        string s = "SECTION TEXT";

        for(int i = 0; i < (int)lines.size(); i++) {
            s += "\n" + lines[i];
        }
        
        return s;  
    }

};