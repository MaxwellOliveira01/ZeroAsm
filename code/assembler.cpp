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

struct Program {

    Data data;
    Text text;

    Program(Data data_, Text text_): data(data_), text(text_) {

    };

};

Text validateAndParseText(PreProcessedText givenText) {

    auto text = Text();

    for(auto &dataLine : givenText.lines) {
        auto parsedLine = removeComments(getTokens(dataLine));
        text.AddLine(parsedLine);
    }

    return text;

}

Data validateAndParseData(PreProcessedData givenData) {

    auto data = Data();

    for(auto &dataLine: givenData.lines) {
        auto parsedLine = removeComments(getTokens(dataLine));
        data.AddLine(parsedLine);
    }

    return data;
}

Program getProgram(PreProcessedData givenData, PreProcessedText givenText) {

    // validating data section
    auto data = validateAndParseData(givenData);

    auto text = validateAndParseText(givenText);

    return Program(data, text);
}