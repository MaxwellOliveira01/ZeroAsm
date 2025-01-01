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

vector<string> CommandTypeStrings = {
    "ADD",
    "SUB",
    "MULT",
    "DIV",
    "JMP",
    "JMPN",
    "JMPP",
    "JMPZ",
    "COPY",
    "LOAD",
    "STORE",
    "INPUT",
    "OUTPUT",
    "STOP",
};

struct Command { // abstract
    string label;
    string arg;
    int shift = 0;
    CommandType type;
    virtual ~Command() = default;
    
    virtual string toString() {
        return ((int)label.size() ? label + ": " : "") + CommandTypeStrings[type] + " " + arg + (shift > 0 ? "+" + to_string(shift) : "");
    }
    
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

    AddCommand(string label_, string value_): Command(label_, CommandType::Add) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsAddCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "add";
    }
};

struct SubCommand : Command {

    SubCommand(string label_, string value_): Command(label_, CommandType::Sub) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsSubCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "sub";
    }
};

struct MultCommand : Command {

    MultCommand(string label_, string value_): Command(label_, CommandType::Mult) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsMultCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "mult";
    }

};

struct DivCommand : Command {

    DivCommand(string label_, string value_): Command(label_, CommandType::Div) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsDivCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "div";
    }

};

struct JmpCommand : Command {

    JmpCommand(string label_, string value_): Command(label_, CommandType::Jmp) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsJmpCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmp";
    }

};

struct JmpnCommand : Command {

    JmpnCommand(string label_, string value_): Command(label_, CommandType::Jmpn) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsJmpnCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmpn";
    }

};

struct JmppCommand : Command {

    JmppCommand(string label_, string value_): Command(label_, CommandType::Jmpp) {
        tie(arg, shift) = parseCommandShift(value_);

    };

    bool static IsJmppCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmpp";
    }

};

struct JmpzCommand : Command {

    JmpzCommand(string label_, string value_): Command(label_, CommandType::Jmpz) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static IsJmpzCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "jmpz";
    }

};

struct CopyCommand : Command {
    string arg2;
    int shift2;
    
    CopyCommand(string label_, string value1_, string value2_): Command(label_, CommandType::Copy) {
        tie(arg, shift) = parseCommandShift(value1_);
        tie(arg2, shift2) = parseCommandShift(value2_);
    };

    bool static IsCopyCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "copy";
    }

    string toString() override {
        return (!label.empty() ? label + ": " : "") + "COPY " + arg + (shift > 0 ? "+" + to_string(shift) : "")
            + "," + arg2 + (shift2 > 0 ? "+" + to_string(shift2) : "");
    }
};

struct LoadCommand : Command {

    LoadCommand(string label_, string value_): Command(label_, CommandType::Load) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static isLoadCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "load";
    }

};

struct StoreCommand : Command {

    StoreCommand(string label_, string value_): Command(label_, CommandType::Store) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static isStoreCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "store";
    }

};

struct InputCommand : Command {

    InputCommand(string label_, string value_): Command(label_, CommandType::Input) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static isInputCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "input";
    }

};

struct OutputCommand : Command {

    OutputCommand(string label_, string value_): Command(label_, CommandType::Output) {
        tie(arg, shift) = parseCommandShift(value_);
    };

    bool static isOutputCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "output";
    }

};

struct StopCommand : Command {

    StopCommand(string label_): Command(label_, CommandType::Stop) {
    
    };

    bool static isStopCommand(vector<string> line) {
        return (int)line.size() && toLower(line[0]) == "stop";
    }

    string toString() override {
        return (!label.empty() ? label + ": " : "") + "STOP"; 
    }
};