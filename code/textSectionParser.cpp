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

            commands.push_back(ValidateAndCreateClassObj(label, line));

            if((int)label.size() == 0) {
                pastLabels = label;
                continue;
            }

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

        if(AddCommand::IsAddCommand(line)) {
            return make_shared<AddCommand>(label, line[1]);
        }

        if(SubCommand::IsSubCommand(line)) {
            return make_shared<SubCommand>(label, line[1]);
        }
        
        if(MultCommand::IsMultCommand(line)) {
            return make_shared<MultCommand>(label, line[1]);
        }
        
        if(DivCommand::IsDivCommand(line)) {
            return make_shared<DivCommand>(label, line[1]);
        }
        
        if(JmpCommand::IsJmpCommand(line)) {
            return make_shared<JmpCommand>(label, line[1]);
        }
        
        if(JmpnCommand::IsJmpnCommand(line)) {
            return make_shared<JmpnCommand>(label, line[1]);
        }
        
        if(JmppCommand::IsJmppCommand(line)) {
            return make_shared<JmppCommand>(label, line[1]);
        }
        
        if(JmpzCommand::IsJmpzCommand(line)) {
            return make_shared<JmpzCommand>(label, line[1]);
        }
        
        if(CopyCommand::IsCopyCommand(line)) {
            return make_shared<CopyCommand>(label, line[1], line[3]);
        }
        
        if(LoadCommand::isLoadCommand(line)) {
            return make_shared<LoadCommand>(label, line[1]);
        }
        
        if(StoreCommand::isStoreCommand(line)) {
            return make_shared<StoreCommand>(label, line[1]);
        }
        
        if(InputCommand::isInputCommand(line)) {
            return make_shared<InputCommand>(label, line[1]);
        }
        
        if(OutputCommand::isOutputCommand(line)) {
            return make_shared<OutputCommand>(label, line[1]);
        }
        
        if(StopCommand::isStopCommand(line)) {
            return make_shared<StopCommand>(label);
        }

        showErrorAndExit("Invalid instruction", line);
        return nullptr; // unreachable

    }

    string toString() {
        string s = "SECTION TEXT\n"; 

        for(auto &d : commands) {
            s += d.get()->toString() + "\n";
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

            // "instruction" + space if its different from stop
            result += line[0] + ((int)line.size() > 1 ? " " : ""); 

            // arguments in the same way as the input
            for(int i = 1; i < (int)line.size(); i++) {
                result += line[i];
            }

            lines.push_back(result);

            pastLabels.clear();

        }
    }

    string toString() {
        string s = "SECTION TEXT\n";

        for(int i = 0; i < (int)lines.size(); i++) {
            s += lines[i];
            if(i + 1 < (int)lines.size()) {
                s += "\n";
            }
        }
        
        return s;  
    }

};