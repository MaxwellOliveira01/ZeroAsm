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

bool isConstDirective(vector<string> line) {
    return (int)line.size() == 4 && toLower(line[2]) == "const";
}

bool isSpaceDirective(vector<string> line) {
    return ((int)line.size() == 3 || (int)line.size() == 4) 
        && toLower(line[2]) == "space";
}

bool hasLabel(vector<string> line) {
    return (int)line.size() >= 2 && line[1] == ":";
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

    return {name, extension};

}
