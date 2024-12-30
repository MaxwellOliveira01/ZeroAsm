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

using namespace std;

enum CommandType {
    Add,
    Sub,
    Mult,
    Div,
    Jmp,
    Jmpn,
    Jmpp,
    Jmpz,
    Copy,
    Load,
    Store,
    Input,
    Output,
    Stop,
};

struct Command { // abstract
    string label;
    CommandType type;
    virtual ~Command() = default;
    virtual string toString() = 0;
    Command(string label_, CommandType type_) : label(label_), type(type_) {}
    Command(CommandType type_) : label(""), type(type_) {}
}; 

struct AddCommand : Command {
    string value;

    AddCommand(string label_, string value_): Command(label_, CommandType::Add), value(value_) {

    };

    AddCommand(string value_): Command(CommandType::Add), value(value_) {

    };

    bool static IsAddCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "add";
    }

    string toString() override {
        return (!label.empty() ? label + ": " : "") + "ADD " + value; 
    }
};

struct SubCommand : Command {
    string value;

    SubCommand(string label_, string value_): Command(label_, CommandType::Sub), value(value_) {

    };

    SubCommand(string value_): Command(CommandType::Sub), value(value_) {

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

    MultCommand(string label_, string value_): Command(label_, CommandType::Mult), value(value_) {

    };

    MultCommand(string value_): Command(CommandType::Mult), value(value_) {

    };

    bool static IsMultCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "mult";
    }

    string toString() override {
        return (!label.empty() ? label + ": " : "") + "MULT " + value; 
    }
};

struct DivCommand : Command {
    string value;

    DivCommand(string label_, string value_): Command(label_, CommandType::Div), value(value_) {

    };

    DivCommand(string value_): Command(CommandType::Div), value(value_) {

    };

    bool static IsDivCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "div";
    }

    string toString() override {
        return (!label.empty() ? label + ": " : "") + "DIV " + value; 
    }
};

struct JmpCommand : Command {
    string value;

    JmpCommand(string label_, string value_): Command(label_, CommandType::Jmp), value(value_) {

    };

    JmpCommand(string value_): Command(CommandType::Jmp), value(value_) {

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

    JmpnCommand(string label_, string value_): Command(label_, CommandType::Jmpn), value(value_) {

    };

    JmpnCommand(string value_): Command(CommandType::Jmpn), value(value_) {

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

    JmppCommand(string label_, string value_): Command(label_, CommandType::Jmpp), value(value_) {

    };

    JmppCommand(string value_): Command(CommandType::Jmpp), value(value_) {

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

    JmpzCommand(string label_, string value_): Command(label_, CommandType::Jmpz), value(value_) {

    };

    JmpzCommand(string value_): Command(CommandType::Jmpz), value(value_) {

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
    
    CopyCommand(string label_, string value1_, string value2_): Command(label_, CommandType::Copy), value1(value1_), value2(value2_) {

    };

    CopyCommand(string value1_, string value2_): Command(CommandType::Copy), value1(value1_), value2(value2_) {

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

    LoadCommand(string label_, string value_): Command(label_, CommandType::Load), value(value_) {

    };

    LoadCommand(string value_): Command(CommandType::Load), value(value_) {

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

    StoreCommand(string label_, string value_): Command(label_, CommandType::Store), value(value_) {

    };

    StoreCommand(string value_): Command(CommandType::Store), value(value_) {

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

    InputCommand(string label_, string value_): Command(label_, CommandType::Input), value(value_) {

    };

    InputCommand(string value_): Command(CommandType::Input), value(value_) {

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

    OutputCommand(string label_, string value_): Command(label_, CommandType::Output), value(value_) {

    };

    OutputCommand(string value_): Command(CommandType::Output), value(value_) {

    };

    bool static isOutputCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "output";
    }

    string toString() {
        return (!label.empty() ? label + ": " : "") + "OUTPUT " + value; 
    }
};

struct StopCommand : Command {

    StopCommand(string label_): Command(label_, CommandType::Stop) {

    };

    StopCommand(): Command(CommandType::Stop) {

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

    Text() {
        commands = vector<shared_ptr<Command>>();
    }

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
                    // more than one labels in a row, should not happen since the file is preprocessed
                    showErrorAndExit("More than one label in a row: " + pastLabels + " and " + line[0]);
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

            commands.push_back(ValidateAndCreateClassObj(line, label));

            if((int)label.size() == 0) {
                pastLabels = label;
                continue;
            }

        }

        // if((int)pastLabels.size()) {
        //     throw runtime_error("Invalid label localtion: " + pastLabels);
        // }

    }

    void AddLine(vector<string> line) {

        if((int)line.size() == 0) {
            return;
        }

        commands.push_back(ValidateAndCreateClassObj(line));

    }

    shared_ptr<Command> ValidateAndCreateClassObj(vector<string> line, string label = "") {

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

        showErrorAndExit("Invalid instruction at text section", line);
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