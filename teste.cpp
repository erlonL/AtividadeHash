#include "hash.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using std::cout, std::endl, std::ifstream;

int main(void){
    fstream file("hashDB.txt");
    if(!file.is_open()){
        cout << "Não foi possível abrir o arquivo!" << endl;
        exit(1);
    }
    // utiliza o cabeçalho para alocar memória
    string linha;

    getline(file, linha);
    std::stringstream ss(linha);
    string c1, c2, c3;
    getline(ss, c1, ' ');
    getline(ss, c2, ' ');
    getline(ss, c3, ' ');
    // cout << c1 << " " << c2 << " " << c3 << endl;
    c1.clear(); c2.clear();

    int n = stoi(c3);
    c3.clear();

    HashTableVector* hv = new HashTableVector(n);

    hv->read(file);

    hv->log();

    file.close();
    delete hv;
    return 0;
}