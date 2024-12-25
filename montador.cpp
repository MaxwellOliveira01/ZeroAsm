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

int main(int argc, char *argv[]) {

    // ./montador < input.asm > input.pre
    // ./montador < input.pre > input.obj

    auto preProcess = preProcessFile(argv[1]);
    return 0;

}