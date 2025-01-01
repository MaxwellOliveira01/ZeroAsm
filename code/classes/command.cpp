#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
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
    
    int size() {
        if(type == CommandType::Copy) {
            return 3;
        }

        if(type == CommandType::Stop) {
            return 1;
        }

        return 2;
    };

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