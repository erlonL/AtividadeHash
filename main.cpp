#include "hash.hpp"
#include <iostream>

using std::cout, std::endl;

int main(void){
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

    cout << endl;

    hv.log();

    
    delete a7;
    return 0;
}