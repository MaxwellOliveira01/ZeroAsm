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
    CodigoMontado cm_1(e1);
    CodigoMontado cm_2(e2);
    RelativeAddresses ra_1(e1);
    RelativeAddresses ra_2(e2);
    int fatorDeCorrecao = cm_1.values.size();
    SymbolsTable stG = geraTabelaGlobal(fatorDeCorrecao, st_1, st_2);
    corrigeEnderecos(cm_1, cm_2, stG, st_1, st_2, ra_2);
}