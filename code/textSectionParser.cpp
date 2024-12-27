#include <bits/stdc++.h>

#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
#endif

#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED
#include "debug.cpp"
#endif

using namespace std;

enum CommandType {
    INSTRUCTION, 
    DIRECTIVE
};

struct Command { // abstract
    string label;
    CommandType type;
    virtual ~Command() = default;
    virtual string toString() = 0;
}; 

struct AddCommand : Command {
    string value;

    AddCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    AddCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsAddCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "add";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "ADD " + value; 
    }
};

struct SubCommand : Command {
    string value;

    SubCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    SubCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsSubCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "sub";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "SUB " + value; 
    }
};

struct MultCommand : Command {
    string value;

    MultCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    MultCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsMultCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "mult";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "MULT " + value; 
    }
};

struct DivCommand : Command {
    string value;

    DivCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    DivCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsDivCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "div";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "DIV " + value; 
    }
};

struct JmpCommand : Command {
    string value;

    JmpCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    JmpCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsJmpCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmp";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "JMP " + value; 
    }
};

struct JmpnCommand : Command {
    string value;

    JmpnCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    JmpnCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsJmpnCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmpn";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "JMPN " + value; 
    }
};

struct JmppCommand : Command {
    string value;

    JmppCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    JmppCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsJmppCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmpp";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "JMPP " + value; 
    }
};

struct JmpzCommand : Command {
    string value;

    JmpzCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    JmpzCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static IsJmpzCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmpz";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "JMPZ " + value; 
    }
};

struct CopyCommand : Command {
    string value1, value2;
    
    CopyCommand(string label_, string value1_, string value2_) {
        label = label_;
        value1 = value1_;
        value2 = value2_;
        type = INSTRUCTION;
    };

    CopyCommand(string value1_, string value2_) {
        label = "";
        value1 = value1_;
        value2 = value2_;
        type = INSTRUCTION;
    };

    bool static IsCopyCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "copy";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "COPY " + value1 + "," + value2; 
    }
};

struct LoadCommand : Command {
    string value;

    LoadCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    LoadCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static isLoadCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "load";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "LOAD " + value; 
    }
};

struct StoreCommand : Command {
    string value;

    StoreCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    StoreCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static isStoreCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "store";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "STORE " + value; 
    }
};

struct InputCommand : Command {
    string value;

    InputCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    InputCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static isInputCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "input";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "INPUT " + value; 
    }
};

struct OutputCommand : Command {
    string value;

    OutputCommand(string label_, string value_) {
        label = label_;
        value = value_;
        type = INSTRUCTION;
    };

    OutputCommand(string value_) {
        label = "";
        value = value_;
        type = INSTRUCTION;
    };

    bool static isOutputCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "output";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "OUTPUT " + value; 
    }
};

struct StopCommand : Command {
    StopCommand(string label_) {
        label = label_;
        type = INSTRUCTION;
    };

    bool static isStopCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "stop";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "STOP"; 
    }
};

struct Text {
    vector<shared_ptr<Command>> commands;

    Text() = default;

    Text(vector<vector<string>> parsedLines) {
        commands = vector<shared_ptr<Command>>();

        // vector<string> pastLabels;
        string pastLabels = "";

        for(auto &line : parsedLines) {

            if((int)line.size() == 0) {
                continue;
            }

            string label = "";

            if(hasLabel(line)) {
                if((int)pastLabels.size()) {
                    // more than one labels in a row
                    throw runtime_error("More than one label in a row: " + pastLabels + " and " + line[0]);
                } else {
                    label = line[0];
                    line = split(line, 2, (int)line.size());
                    
                    if((int)line.size() == 0) {
                        pastLabels = label;
                        continue;
                    }

                }
            } else if((int)pastLabels.size()) {
                label = pastLabels;
                pastLabels = "";
            }

            if(AddCommand::IsAddCommand(line)) {
                commands.push_back(make_unique<AddCommand>(label, line[1]));
                continue;
            } 
            
            if(SubCommand::IsSubCommand(line)) {
                commands.push_back(make_unique<SubCommand>(label, line[1]));
                continue;
            }
            
            if(MultCommand::IsMultCommand(line)) {
                commands.push_back(make_unique<MultCommand>(label, line[1]));
                continue;
            }
            
            if(DivCommand::IsDivCommand(line)) {
                commands.push_back(make_unique<DivCommand>(label, line[1]));
                continue;
            }
            
            if(JmpCommand::IsJmpCommand(line)) {
                commands.push_back(make_unique<JmpCommand>(label, line[1]));
                continue;
            }
            
            if(JmpnCommand::IsJmpnCommand(line)) {
                commands.push_back(make_unique<JmpnCommand>(label, line[1]));
                continue;
            }
            
            if(JmppCommand::IsJmppCommand(line)) {
                commands.push_back(make_unique<JmppCommand>(label, line[1]));
                continue;
            }
            
            if(JmpzCommand::IsJmpzCommand(line)) {
                commands.push_back(make_unique<JmpzCommand>(label, line[1]));
                continue;
            }
            
            if(CopyCommand::IsCopyCommand(line)) {
                commands.push_back(make_unique<CopyCommand>(label, line[1], line[3]));
                continue;
            }
            
            if(LoadCommand::isLoadCommand(line)) {
                commands.push_back(make_unique<LoadCommand>(label, line[1]));
                continue;
            }
            
            if(StoreCommand::isStoreCommand(line)) {
                commands.push_back(make_unique<StoreCommand>(label, line[1]));
                continue;
            }
            
            if(InputCommand::isInputCommand(line)) {
                commands.push_back(make_unique<InputCommand>(label, line[1]));
                continue;
            }
            
            if(OutputCommand::isOutputCommand(line)) {
                commands.push_back(make_unique<OutputCommand>(label, line[1]));
                continue;
            }
            
            if(StopCommand::isStopCommand(line)) {
                commands.push_back(make_unique<StopCommand>(label));
                continue;
            } 

            if((int)label.size() == 0) {
                //pastLabels.push_back(label);
                pastLabels = label;
                continue;
            }

            string lineStr = "";
            for(auto &x : line) lineStr += x + " ";
            throw runtime_error("Invalid instruction: " + lineStr);

        }

        // if((int)pastLabels.size()) {
        //     throw runtime_error("Invalid label localtion: " + pastLabels);
        // }

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



