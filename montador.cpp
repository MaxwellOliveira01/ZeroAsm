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

    // if(argc != 2) {
    //     cout << "Usage: ./montador <input_file.asm> or ./montador <input_file.pre>\n"; ;
    //     return 1;
    // }

    auto preProcess = preProcessFile(argv[1]);

    for(auto &line : preProcess) {
        debug(line);
    }

    // TODO: mover section de data para o final do arquivo (se necessario)

    return 0;

}