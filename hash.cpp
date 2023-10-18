#include "hash.hpp"
#include <tuple>
#include <fstream>
#include <iostream>
#include <filesystem>
#define TAM_HASH_VECTOR 10


using std::cout, std::endl, std::string, std::tuple, std::stringstream, std::ifstream, std::getline;

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
bool HashTable::notEmpty(){
    for(int i = 0; i < tamanho; i++){
        if(childTable[i] != nullptr){
            return true;
        }
    }
    return false;
}
int HashTable::getSize(){
    return tamanho;
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
bool HashTable::remove(string c){
    int pos = hash(c);
    HashNode* aux = childTable[pos];
    if(aux == nullptr)
        return false; // a chave não existe
    HashNode* aux2 = aux->getProx();
    if(aux->getChave() == c){
        childTable[pos] = aux2;
        delete aux;
        return true; // a chave era a primeira
    }else{
        while(aux2 != nullptr){
            if(aux2->getChave() == c){
                aux->setProx(aux2->getProx());
                delete aux2;
                return true; // encontramos a chave depois de percorrer
            }
            aux = aux2;
            aux2 = aux2->getProx();
        }
    }
    return false; // tirar o warning
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
int HashTable::getHash(string c){
    return hash(c);
}
void HashTable::write(FILE* file, int parentPos){
    for(int cPos = 0; cPos < tamanho; cPos++){
        HashNode* aux = childTable[cPos];
        int nodePos = 0;
        while(aux != nullptr){
            fprintf(file, "%d %d %d %s %d\n", parentPos, cPos, nodePos, aux->getChave().c_str(), aux->getValor());
            nodePos++;
            aux = aux->getProx();
        }
        // cPos++;
    }
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
    return (soma*13) % tamanho;
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
bool HashTableVector::remove(string c){
    int pos = hash(c);
    return parentTable[pos]->remove(c);
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
    /*Retorna um nó a partir de uma string*/
    int pos = hash(c);
    return parentTable[pos]->getNode(c);
}
tuple<int, int> HashTableVector::getHash(string c){
    /*retorna posições das tabelas pai e filho*/
    int ParentPos = hash(c);
    int ChildPos = parentTable[ParentPos]->getHash(c);
    return {ParentPos, ChildPos};
}
void HashTableVector::write(FILE* file){
    /*Escreve em um arquivo existente
    da forma
    parentPos childPos filaPos Chave Valor*/
    HashTable* aux = parentTable[0];
    int childSize = aux->getSize();
    int totalSize = childSize * tamanho;

    fprintf(file, "%d %d %d\n", tamanho, childSize, totalSize);
    for(int i = 0; i < tamanho; i++){
        if(parentTable[i]->notEmpty()){
            parentTable[i]->write(file, i);
        }
    }
}
 // Por algum motivo ele não aceitou o ifstream como parâmetro
void HashTableVector::read(fstream& file){
    // Lê de um arquivo existente
    // da forma
    // parentPos childPos filaPos Chave Valor
    string linha;

    while(getline(file, linha)){
        stringstream ss(linha);
        string c1, c2, c3, c4, c5;
        getline(ss, c1, ' ');
        getline(ss, c2, ' ');
        getline(ss, c3, ' ');
        getline(ss, c4, ' ');
        getline(ss, c5, ' ');

        int parentPos = stoi(c1);
        string Chave = c4;
        int Valor = stoi(c5);

        c1.clear(); c2.clear(); c3.clear(); c4.clear(); c5.clear();

        HashNode* novoNo = new HashNode(Chave, Valor);
        parentTable[parentPos]->insert(novoNo);
    }
}
HashTableVector::~HashTableVector(){
    for(int i = 0; i < tamanho; i++){
        delete parentTable[i];
    }
    delete[] parentTable;
}