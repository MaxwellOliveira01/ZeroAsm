// https://codeforces.com/blog/entry/125435
#ifdef MAXWELL_LOCAL_DEBUG
#include "debug/debug_template.cpp"
#else
#define debug(...)
#define debugArr(arr, n)
#endif

#define dbg debug()

#include <bits/stdc++.h>
#include "code/preprocess.cpp"

using namespace std;

// ./montador < input.asm > input.pre
// ./montador < input.pre > input.obj

int main(int argc, char *argv[]) {

    auto [fileName, extension] = parseFileName(argv[1]);

    if(toLower(extension) == "asm") {

        string outputName = fileName + ".pre"; 

        // just create an empty file for now
        ofstream empty(outputName);
        empty.close();

        auto preProcessedResult = preProcessFile(argv[1]);

        ofstream res(outputName);
        res << preProcessedResult.toString();
        res.close();

    } else if(toLower(extension) == "pre") {

    } else {
        showErrorAndExit("Invalid file extension, it must be .asm or .pre");
    }

    return 0;

}