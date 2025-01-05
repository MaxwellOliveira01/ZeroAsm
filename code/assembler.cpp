#include <bits/stdc++.h>

#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
#endif

#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED
#include "debug.cpp"
#endif

#ifndef DATASECTION_INCLUDED
#define DATASECTION_INCLUDED
#include "dataSectionParser.cpp"
#endif

#ifndef TEXT_INCLUDED
#define TEXT_INCLUDED
#include "textSectionParser.cpp"
#endif

#ifndef PROGRAM_INCLUDED
#define PROGRAM_INCLUDED
#include "classes/program.cpp"
#endif

using namespace std;

Text validateAndParseText(PreProcessedText givenText) {

    vector<vector<string>> parsedLines;

    for(auto &dataLine : givenText.body) {
        // parsedLine should be the same as dataLine, 
        // since givenText is already pre processed
        auto parsedLine = removeComments(getTokens(dataLine));
        parsedLines.push_back(parsedLine);
    }

    return Text(parsedLines);

}

Data validateAndParseData(PreProcessedData givenData) {

    vector<vector<string>> parsedLines;

    for(auto &dataLine: givenData.lines) {
        // parsedLine should be the same as dataLine, 
        // since givenText is already pre processed
        auto parsedLine = removeComments(getTokens(dataLine));
        parsedLines.push_back(parsedLine);
    }

    return Data(parsedLines);
}

Program getProgram(PreProcessedData givenData, PreProcessedText givenText) {

    auto data = validateAndParseData(givenData);
    auto text = validateAndParseText(givenText);
    auto program = Program(data, text);

    // before return we need to do some checks

    auto symbolsTable = program.createSymbolsTable();

    for(auto &cmdpointer: program.text.commands) {
        auto command = cmdpointer.get();

        if(command->type == CommandType::Stop) {
            continue;
        }

        vector<string> args = { command->arg };

        if(command->type == CommandType::Copy) {
            auto copyCommand = dynamic_cast<CopyCommand*>(command);
            args.push_back(copyCommand->arg2);
        }

        for(auto &arg : args) {
            if(symbolsTable.find(arg) == symbolsTable.end()) {
                showErrorAndExit("'" + arg + "' is not defined");
            } else {
                // do we need to block the case of A + x, where A is CONST?
                // do we need to block the case of A + 1, when A is just an label on text section?
                // do we need to block the case of A + 10, when A is an label to SPACE 5?
            }
        }

    }

    // if is not an module, it shouldnt have public or extern

    return program;
}