// https://codeforces.com/blog/entry/125435
#ifdef MAXWELL_LOCAL_DEBUG
#include "debug/debug_template.cpp"
#else
#define debug(...)
#define debugArr(arr, n)
#endif

#define dbg debug()

#include <bits/stdc++.h>
#include "code/ligadorProcess.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    auto e1 = argv[1];
    auto e2 = argv[2];
    SymbolsTable st_1(e1);
    SymbolsTable st_2(e2);
    CodigoMontado cm(e1);
    RelativeAddresses ra(e1);
    SymbolsTable stG = geraTabelaGlobal(st_1, st_2);
    for (const auto& symbol : stG.symbols) {
        cout << symbol.toString() << std::endl;         
    }
    
}