// https://codeforces.com/blog/entry/125435
#ifdef MAXWELL_LOCAL_DEBUG
#include "debug/debug_template.cpp"
#else
#define debug(...)
#define debugArr(arr, n)
#endif

#define dbg debug()

#include "code/preprocess.cpp"

#include "code/assembler.cpp"

#include <bits/stdc++.h>

using namespace std;

// ./montador < input.asm > input.pre
// ./montador < input.pre > input.obj

int main(int argc, char *argv[]) {

    auto path = argv[1];
    auto [fileName, extension] = parseFileName(path);

    if(toLower(extension) == "asm") {
        string outputName = fileName + ".pre"; 
        writeToFile(outputName, ""); // just create an empty file for now
        auto preProcessedResult = preProcessFile(path);
        writeToFile(outputName, preProcessedResult.toString());
    } else if(toLower(extension) == "pre") {
        
        auto preProcessedResult = preProcessFile(path);
        auto program = getProgram(preProcessedResult.DataSection, preProcessedResult.TextSection);

    } else {
        showErrorAndExit("Invalid file extension, it must be .asm or .pre");
    }

    return 0;

}