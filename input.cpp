#include "hash.hpp"
#include <iostream>

using std::string, std::cerr, std::cout, std::endl;

int main(int argc, char** argv){
    if(argc == 1){
        cerr << "Quantidade de argumentos inválida!\nUtilize ./input.exe \"string1\" \"string2\", ..." << endl;
    }
    int ArgumentsSize = argc - 1;

    string keys[ArgumentsSize];
    for(int i = 1; i < argc; i++){
        keys[i - 1] = argv[i];
    }

    HashNode a1("Maria", 12);
    HashNode a2("João", 6);
    HashNode a3("José", 24);
    HashNode a4("Lucas", 36);
    HashNode a5("Matheus", 3);
    HashNode a6("Simão", 7);
    HashNode* a7 = new HashNode("Pedro", 9);

    HashTableVector hv(50);

    hv.insert(&a1);
    hv.insert(&a2);
    hv.insert(&a3);
    hv.insert(&a4);
    hv.insert(&a5);
    hv.insert(&a6);
    hv.insert(a7);
    hv.insert("Ana", 10);
    hv.insert("Mathuis", 35);

    for (int i = 0; i < ArgumentsSize; i++){
        HashNode aux = hv.getNode(keys[i]);
        if(aux.getValor() != 0){
            cout << "Nó encontrado!" << endl;
            aux.info();
        }else{
            continue;
        }
        cout << endl;
    }


    delete a7;
    return 0;
}