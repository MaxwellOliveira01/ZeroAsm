// https://codeforces.com/blog/entry/125435
#ifdef MAXWELL_LOCAL_DEBUG
#include "../debug/debug_template.cpp"
#else
#define debug(...)
#define debugArr(arr, n)
#endif

#define dbg debug()

#include <bits/stdc++.h>
using namespace std;

// TODO: fix name conventions

// enum DataType {
//     SPACE,
//     CONST,
// };

struct Data {

    Data() = default;

    Data(vector<string>& lines) {

    }

    string toString() {
        return "";        
    }

};

struct Text {

    string toString() {
        return "";
    }

};

struct Program {
    Data DataSection;
    Text TextSection;

    Program() = default;

    Program(Data data, Text text) {
        DataSection = data;
        TextSection = text;
    }

    string toString() {
        return TextSection.toString() + "/n" + DataSection.toString(); 
    }

};

vector<string> readFile(string path) {

    vector<string> out;

    ifstream file(path);

    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            out.push_back(line);
        }
        file.close();
    } else {
        cout << "Unable to open file " << path << "\n";
        exit(1);
    }

    return out;

}

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

bool isDataSection(vector<string> normalizedTokens) {
    return normalizedTokens.size() == 2 && normalizedTokens[0] == "section" 
        && normalizedTokens[1] == "data";
}

bool isTextSection(vector<string> normalizedTokens) {
    return normalizedTokens.size() == 2 && normalizedTokens[0] == "section"
        && normalizedTokens[1] == "text";
}

template <typename T>
vector<T> split(vector<T>& arr, int l, int r) { // [l,r)
    vector<T> ans;
    for(int i = l; i < r; i++) {
        ans.push_back(arr[i]);
    }
    return ans;
}

Program preProcessFile(string path) {

    auto file = readFile(path);

    vector<string> dataSection, textSection;

    int dataSectionStartIndex = -1, dataSectionEndIndex = -1;

    for(int i = 0; i < (int)file.size(); i++) {
        auto normalizedLine = file[i];
        
        transform(normalizedLine.begin(), normalizedLine.end(), 
            normalizedLine.begin(), ::tolower);
        
        auto parsedLine = getTokens(normalizedLine);

        debug(parsedLine);

        if(isDataSection(parsedLine)) {
            dataSectionStartIndex = i;
            dataSectionEndIndex = (int)file.size(); // 1 after, exclusive index
        }

        if(isTextSection(parsedLine)) {
            if(dataSectionStartIndex != -1) {
                dataSectionEndIndex = i;  // 1 after, exclusive index
            }
        }
    }

    auto dataSectionLines = split(file, dataSectionStartIndex + 1, dataSectionEndIndex);
    
    debug(dataSectionStartIndex, dataSectionEndIndex);
    debug(dataSectionLines);

    // auto data = Data(dataSectionLines);

    return Program();

}
