#include <bits/stdc++.h>
using namespace std;

string toLower(string s) {
    auto t = s;
    transform(t.begin(), t.end(), t.begin(), ::tolower);
    return t;
}

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

template <typename T>
vector<T> split(vector<T>& arr, int l, int r) { // [l,r)
    vector<T> ans;
    for(int i = l; i < r; i++) {
        ans.push_back(arr[i]);
    }
    return ans;
}

bool isDataSection(vector<string> normalizedTokens) {
    return normalizedTokens.size() == 2 && normalizedTokens[0] == "section" 
        && normalizedTokens[1] == "data";
}

bool isTextSection(vector<string> normalizedTokens) {
    return normalizedTokens.size() == 2 && normalizedTokens[0] == "section"
        && normalizedTokens[1] == "text";
}

bool hasLabel(vector<string> line) {
    return (int)line.size() >= 2 && line[1] == ":";
}

void showErrorAndExit(string message) {
    cout << message << "\n";
    exit(-1);
}

void showErrorAndExit(string message, vector<string> tokens) {
    cout << message << "\nTokens=[";

    for(int i = 0; i < (int)tokens.size(); i++) {
        cout << "'" << tokens[i] << "'";
        if(i + 1 < (int)tokens.size()) {
            cout << ", ";
        }
    }

    cout << "]\n";
    exit(-1);
}

pair<string, string> parseFileName(string path) {

    string res = "";

    int idx = (int)path.size() - 1;

    while(idx >= 0 && path[idx] != '/') {
        res += path[idx];
        idx--;
    }

    reverse(res.begin(), res.end());

    string name = "", extension = "";

    bool ponto = false;

    for(auto &x : res) {
        if(x == '.') {
            ponto = true;
            continue;
        }

        if(ponto) {
            extension += x;
        } else {
            name += x;
        }
    }

    return { name, extension };

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

void writeToFile(string path, string content) {

    ofstream file(path);

    if(file.is_open()) {
        file << content;
        file.close();
    } else {
        cout << "Unable to open file " << path << "\n";
        exit(1);
    }

}

bool isLabelNameValid(string label) {
    // cannot starts with a number
    if(label[0] >= '0' && label[0] <= '9') {
        return false;
    }

    for(auto &c : label) { // if char is not a letter or number, it must be an underscore
        if(!isalnum(c) && c != '_') {
            return false;
        }
    }

    return true;
}

bool isDecNumber(string number, int& value) { // Add tests!!!

    if((int)number.size() == 0) {
        return false;
    }

    bool neg = false;

    if(number[0] == '-') {
        neg = true;
        number = number.substr(1);
    }

    for(auto &c : number) {
        if(!isdigit(c)) {
            return false;
        }
    }

    value = stoi(number);

    if(neg) value = -value;

    return true;

}

bool isHexNumber(string number, int& value) { // add TESTS!!!!

    if((int)number.size() == 0) {
        return false;
    }

    bool neg = false;

    if(number[0] == '-') {
        neg = true;
        number = number.substr(1);
    }

    if((int)number.size() < 3 || number[0] != '0' || tolower(number[1]) != 'x') {
        return false;
    }

    number = number.substr(2);

    try {
        value = stoi(number, 0, 16);
        if(neg) value = -value;
        return true;
    } catch(...) {
        return false;
    }

}