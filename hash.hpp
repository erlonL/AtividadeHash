#pragma once
#include <iostream>
#include <tuple>
#include <fstream>

using std::string, std::tuple, std::fstream;

class HashNode{
    string chave;
    int valor;
    HashNode* prox;
public:
    HashNode(string c, int v);
    HashNode();
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
    bool notEmpty();
    int getSize();
    void insert(string c, int v);
    void insert(HashNode* N);
    bool remove(string c);
    void print();
    void log();
    HashNode* getNode(string c);
    int getHash(string c);
    void write(FILE* file, int parentPos);
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
    bool remove(string c);
    void print();
    void log();
    HashNode* getNode(string c);
    tuple<int, int> getHash(string c);
    void write(FILE* file);
    void read(fstream& file);
    ~HashTableVector();
};