#include "hash.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using std::string, std::cerr, std::cout, std::endl, std::getline;

int main(int argc, char** argv){
    if(argc == 1){
        cerr << "Quantidade de argumentos inválida!\nUtilize ./input.exe \"string1\" \"string2\", ..." << endl;
    }
    int ArgumentsSize = argc - 1;

    string keys[ArgumentsSize];
    for(int i = 1; i < argc; i++){
        keys[i - 1] = argv[i];
    }

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

    HashNode* aux = new HashNode();
    for (int i = 0; i < ArgumentsSize; i++){
        aux = hv->getNode(keys[i]);
        if(aux != nullptr){
            cout << "Nó encontrado!" << endl;
            aux->info();
        }else{
            continue;
        }
        cout << endl;
    }

    file.close();
    delete hv;
    return 0;
}