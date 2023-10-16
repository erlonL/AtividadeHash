#pragma once
#include <iostream>

using std::string;

class HashNode{
    string chave;
    int valor;
    HashNode* prox;
public:
    HashNode(string c, int v);
    string getChave();
    int getValor();
    HashNode* getProx();
    void setProx(HashNode* n);
    string toString();
    void info();
};

class HashTable{
    int tamanho;
    HashNode** childTable;
public:
    HashTable(int n = 10);
    int hash(string c);
    void insert(string c, int v);
    void insert(HashNode* N);
    void print();
    void log();
    HashNode getNode(string c);
    ~HashTable();
};


class HashTableVector{
    int tamanho;
    HashTable** parentTable;
public:
    HashTableVector(int n = 50);
    int hash(string c);
    void insert(string c, int v);
    void insert(HashNode* N);
    void print();
    void log();
    HashNode getNode(string c);
    ~HashTableVector();
};