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