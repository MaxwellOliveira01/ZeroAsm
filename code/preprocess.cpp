#include <bits/stdc++.h>

#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED
#include "util.cpp"
#endif

#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED
#include "debug.cpp"
#endif

#include "dataSectionParser.cpp"
#include "textSectionParser.cpp"

using namespace std;

struct PreProcessedProgram {
    PreProcessedData DataSection;
    PreProcessedText TextSection;

    PreProcessedProgram() = default;

    PreProcessedProgram(PreProcessedText text, PreProcessedData data) {
        DataSection = data;
        TextSection = text;
    }

    string toString() {
        return TextSection.toString() + "\n" + DataSection.toString(); 
    }

};

vector<string> getTokens(string line) {

    vector<string> tokens;

    string currentToken = "";
    
    set<char> ignore = {' ', '\t'};
    set<char> separators = {',', ':', ';'};

    auto pushIfNeeded = [&](bool resetAfter = false) {
        if(currentToken.size() > 0) {
            tokens.push_back(currentToken);
        }

        if(resetAfter) {
            currentToken = "";
        }
    };

    for(auto &c : line) {
        if(ignore.count(c)) {
            pushIfNeeded(true);
        } else {
            if(separators.count(c)) {
                pushIfNeeded(true);
                tokens.push_back(string(1, c));
            } else {
                currentToken += c;
            }
        }
    }

    if(currentToken.size() > 0) { // do we need to check something before push?
        tokens.push_back(currentToken);
    }

    return tokens;

}

vector<string> removeComments(vector<string> tokens) {
    vector<string> out;

    auto commentIndex = 0;

    while(commentIndex < (int)tokens.size() && tokens[commentIndex] != ";") {
        commentIndex++;
    }

    out = vector<string>(tokens.begin(), tokens.begin() + commentIndex);
    return out;
}

PreProcessedData getPreProcessedData(vector<string> lines) {

    auto parsedDataSectionLines = vector<vector<string>>();

    for(auto &line : lines) {
        parsedDataSectionLines.push_back(removeComments(getTokens(line)));
    }

    return PreProcessedData(parsedDataSectionLines);

}

PreProcessedText getPreProcessedText(vector<string> lines){

    auto parsedTextSectionLines = vector<vector<string>>();

    for(auto &line : lines) {
        parsedTextSectionLines.push_back(removeComments(getTokens(line)));
    }

    return PreProcessedText(parsedTextSectionLines);

}

array<int, 4> getTextAndDataSectionIndexes(vector<string>& file) {

    int dataSectionStartIndex = -1, textSectionStartIndex = -1;

    for(int i = 0; i < (int)file.size(); i++) {
        auto normalizedLine = toLower(file[i]);  
        auto parsedLine = removeComments(getTokens(normalizedLine));

        if(isDataSection(parsedLine)) {
            dataSectionStartIndex = i;
        }

        if(isTextSection(parsedLine)) {
            textSectionStartIndex = i;
        }
    }

    if(dataSectionStartIndex == -1 || textSectionStartIndex == -1) {
        showErrorAndExit("Data or text section not found");
    }

    int dataSectionEndIndex = -1, textSectionEndIndex = -1;

    if(dataSectionStartIndex < textSectionStartIndex) {
        dataSectionEndIndex = textSectionStartIndex; // 1 after
        textSectionEndIndex = (int)file.size();
    } else if(textSectionStartIndex < dataSectionStartIndex) {
        textSectionEndIndex = dataSectionStartIndex;
        dataSectionEndIndex = (int)file.size(); // 1 after
    }

    return {dataSectionStartIndex, dataSectionEndIndex, textSectionStartIndex, textSectionEndIndex};

}

PreProcessedProgram preProcessFile(string path) {

    auto file = readFile(path);

    auto [dataSectionStartIndex, dataSectionEndIndex, textSectionStartIndex, textSectionEndIndex] 
        = getTextAndDataSectionIndexes(file);

    auto dataSectionLines = split(file, dataSectionStartIndex + 1, dataSectionEndIndex);
    auto data = getPreProcessedData(dataSectionLines);

    auto textSectionLines = split(file, textSectionStartIndex + 1, textSectionEndIndex);
    auto text = getPreProcessedText(textSectionLines);

    return PreProcessedProgram(text, data);

}