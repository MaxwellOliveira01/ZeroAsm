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

#include<memory>

// TODO: fix name conventions

enum DirectiveType {
    SPACE,
    CONST,
};

struct Directives { // abstract
    string label;
    DirectiveType type;
    virtual ~Directives() = default;
    virtual string toString() = 0;
};

struct ConstDirective : Directives {
    
    // TODO: change it to int
    string value; // needs to handle decimal, hexadecimal and binary

    ConstDirective(string label_, string value_) {
        label = label_;
        value = value_;
        type = CONST;
    };

    string toString() {
        return label + ": CONST " + value;
    }

};

struct SpaceDirective : Directives {

    string value; // str?

    SpaceDirective(string label_, string value_) {
        label = label_;
        value = value_;
        type = SPACE;
    }

    SpaceDirective(string label_) {
        label = label_;
        value = "";
        type = SPACE;
    }

    string toString() {
        auto s = label + ": SPACE";
        
        if((int)value.size()) {
            s += " " + value;
        }

        return s;
    }
    
};

string toLower(string s) {
    auto t = s;
    transform(t.begin(), t.end(), t.begin(), ::tolower);
    return t;
}

bool isConstDirective(vector<string> line) {
    return (int)line.size() == 4 && toLower(line[2]) == "const";
}

bool isSpaceDirective(vector<string> line) {
    return ((int)line.size() == 3 || (int)line.size() == 4) && toLower(line[2]) == "space";
}

struct Data {

    vector<shared_ptr<Directives>> directives;

    Data() = default;

    Data(vector<vector<string>> parsedLines) {
        directives = vector<shared_ptr<Directives>>();
        for(auto &line : parsedLines) {
            if(isConstDirective(line)) {
                directives.push_back(make_unique<ConstDirective>(line[0], line.back()));
            } else if(isSpaceDirective(line)){

                auto d = (int)line.size() == 4 ?
                    SpaceDirective(line[0], line.back()) :
                    SpaceDirective(line[0]);

                directives.push_back(make_unique<SpaceDirective>(d));
            } else {
                string message = "Invalid directive: ";
                for(auto &x: line) message += x + " ";
                throw runtime_error(message);
            }
        }
    }

    string toString() {
        string s = "SECTION DATA\n"; 

        for(auto &d : directives) {
            s += d.get()->toString() + "\n";
        }

        return s;        
    }

};

struct Text {

    string toString() {
        return "";
    }

};

struct Program {
    Data DataSection;
    // Text TextSection;

    Program() = default;

    Program(Data data, Text text) {
        DataSection = data;
        // TextSection = text;
    }

    string toString() {
        return DataSection.toString();
        // return TextSection.toString() + "/n" + DataSection.toString(); 
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

vector<string> removeComments(vector<string> tokens) {
    vector<string> out;

    auto commentIndex = 0;

    while(commentIndex < (int)tokens.size() && tokens[commentIndex] != ";") {
        commentIndex++;
    }

    out = vector<string>(tokens.begin(), tokens.begin() + commentIndex);
    return out;
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

    int dataSectionStartIndex = -1, dataSectionEndIndex = -1;

    for(int i = 0; i < (int)file.size(); i++) {
        auto normalizedLine = toLower(file[i]);  
        auto parsedLine = getTokens(normalizedLine);

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

    auto parsedDataSectionLines = vector<vector<string>>();

    for(auto &line : dataSectionLines) {
        parsedDataSectionLines.push_back(removeComments(getTokens(line)));
    }

    // debug(parsedDataSectionLines);

    auto data = Data(parsedDataSectionLines);
    auto s = data.toString();    
    debug(s);

    return Program();

}