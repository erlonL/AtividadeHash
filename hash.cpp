#include "hash.hpp"
#define TAM_HASH_VECTOR 10

using std::cout, std::endl, std::string;

HashNode::HashNode(string c, int v){
    chave = c;
    valor = v;
    prox = nullptr;
}
string HashNode::getChave(){
    return chave;
}
int HashNode::getValor(){
    return valor;
}
HashNode* HashNode::getProx(){
    return prox;
}
void HashNode::setProx(HashNode* n){
    prox = n;
}
string HashNode::toString(){
    return '{' + chave + " : " + std::to_string(valor) + '}';
}
void HashNode::info(){
    cout << "Chave: " << chave << endl;
    cout << "Valor: " << valor << endl;
}

//

HashTable::HashTable(int n){
    tamanho = n;
    childTable = new HashNode*[tamanho];
    for(int i = 0; i < tamanho; i++){
        childTable[i] = nullptr;
    }
}
int HashTable::hash(string c){
    int soma = 0;
    for(int i = 0; i < c.size(); i++){
        soma += c[i];
    }
    return soma % tamanho;
}
void HashTable::insert(string c, int v){
    int pos = hash(c);
    HashNode* novoNo = new HashNode(c, v);
    if(childTable[pos] == nullptr){
        childTable[pos] = novoNo;
    }else{
        HashNode* aux = childTable[pos];
        while(aux->getProx() != nullptr){
            aux = aux->getProx();
        }
        aux->setProx(novoNo);
    }
}
void HashTable::insert(HashNode* N){
    int pos = hash(N->getChave());
    if(childTable[pos] == nullptr){
        childTable[pos] = N;
    }else{
        HashNode* aux = childTable[pos];
        while(aux->getProx() != nullptr){
            aux = aux->getProx();
        }
        aux->setProx(N);
    }
}
void HashTable::print(){
    for(int i = 0; i < tamanho; i++){
        if(childTable[i] != nullptr){
            cout << i << " => ";
            HashNode* aux = childTable[i];
            while(aux != nullptr){
                cout << aux->toString() << " -> ";
                aux = aux->getProx();
            }
            cout << "NULL" << endl;
        }
    }
}
void HashTable::log(){
    for(int i = 0; i < tamanho; i++){
        cout << i << " => ";
        HashNode* aux = childTable[i];
        while(aux != nullptr){
            cout << aux->toString() << " -> ";
            aux = aux->getProx();
        }
        cout << "NULL" << endl;
    }
}
HashNode HashTable::getNode(string c){
    int pos = hash(c);
    HashNode* aux = childTable[pos];
    while(aux != nullptr){
        if(aux->getChave() == c){
            return *aux;
        }
        aux = aux->getProx();
    }
    if(aux == nullptr){
        cout << "Nó com chave '" << c << "' não encontrado!" << endl;
        return HashNode("", 0);
    }
    return *aux;
}
HashTable::~HashTable(){
    delete[] childTable;
}

//

HashTableVector::HashTableVector(int n){
    /* n -> tamanho total de pessoas
    TAM_HASH_VECTOR fixo como 10*/ 
    tamanho = TAM_HASH_VECTOR;
    parentTable = new HashTable*[tamanho];
    int ChildHashSize = n/TAM_HASH_VECTOR;
    for(int i = 0; i < tamanho; i++){
        parentTable[i] = new HashTable(ChildHashSize);
    }
}
int HashTableVector::hash(string c){
    int soma = 0;
    for(int i = 0; i < c.size(); i++){
        soma += c[i];
    }
    return soma*13 % tamanho;
}
void HashTableVector::insert(string c, int v){
    int pos = hash(c);
    HashNode* novoNo = new HashNode(c, v);
    parentTable[pos]->insert(novoNo);
}
void HashTableVector::insert(HashNode* N){
    int pos = hash(N->getChave());
    parentTable[pos]->insert(N);
}
void HashTableVector::print(){
    for(int i = 0; i < tamanho; i++){
        cout << "\033[1m" << "Tabela " << i << "\033[0m" << endl;
        parentTable[i]->print();
    }
}
void HashTableVector::log(){
    /*Mostra toda a tabela
    pai e filha.*/
    cout << "\033[1m" << "**TABELA COMPLETA**" << "\033[0m" << endl;
    for(int i = 0; i < tamanho; i++){
        cout << "\033[1m" << "Tabela " << i << "\033[0m" << endl;
        parentTable[i]->log();
    }
}
HashNode HashTableVector::getNode(string c){
    int pos = hash(c);
    return parentTable[pos]->getNode(c);
}
HashTableVector::~HashTableVector(){
    for(int i = 0; i < tamanho; i++){
        delete parentTable[i];
    }
    delete[] parentTable;
}