#include <bits/stdc++.h>
using namespace std;

vector<string> split(string s, vector<char> keys) {
    vector<string> ans;
    string aux = "";

    set<char> keys_set(keys.begin(), keys.end());

    for (int i = 0; i < (int)s.size(); i++) {
        if (keys_set.find(s[i]) != keys_set.end()) {
            if (aux.size() > 0) {
                ans.push_back(aux);
                aux = "";
            }
        } else {
            aux += s[i];
        }
    }

    if ((int)aux.size() > 0) {
        ans.push_back(aux);
    }

    return ans;
}

string buildParsedLine(vector<string> tokens) {

    string result = "";

    // Deve ter espaço após ':' e após ',';
    set<string> specialChars = {":", ","};

    for(int i = 0; i < (int)tokens.size(); i++) {
        auto &t = tokens[i];
         
        result += t;

        if(i + 1 < (int)tokens.size() && specialChars.find(tokens[i + 1]) == specialChars.end()) {
            result += " ";
        } else if(specialChars.find(t) != specialChars.end()) {
            result += " ";
        } else {
            string lastChar = ""; 
            lastChar += t.back();
            
            if(specialChars.find(lastChar) != specialChars.end()) {
                result += " ";
            }
        }
    
    }

    return result;

}

string preProcessLine(string rawLine) {
    
    // 1. Remover comentarios
    auto commentStartPos = rawLine.find(";");

    if(commentStartPos != rawLine.npos) {
        rawLine = rawLine.substr(0, commentStartPos);
    }

    // 2. Remover espacos desnecessarios
    // 3. Remover tabs desnecessarios

    auto splitResult = split(rawLine, vector<char>{ ' ', '\t'});
    vector<string> nonEmptyParsedLines;

    for(auto &splittedLine: splitResult) {
        if(splittedLine.size() > 0) {
            nonEmptyParsedLines.push_back(splittedLine);
        }
    }

    auto result = buildParsedLine(nonEmptyParsedLines);
    return result;

    // TODO: enters desnecessarios
    // TODO: linhas em branco?

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
    }

    return out;

}

vector<string> preProcessFile(string path) {
    auto lines = readFile(path);

    vector<string> out;

    for(auto &line : lines) {
        auto postLine = preProcessLine(line);
        
        if((int)postLine.size() > 0) {
            out.push_back(postLine);
        }

    }

    return out;
}