#include "hash.hpp"
#include <iostream>
#include <tuple>
#include <vector>
#include <filesystem>
#include <fstream>

using std::cout, std::endl, std::string, std::cerr, 
std::tuple, std::get, std::cin, std::stringstream, std::ifstream, std::vector, std::getline;

namespace fs = std::filesystem;

int main(void){


    int op1;

    cout << "Seja bem vindo ao " << "\033[1m" << "Sistema de Hash!" << "\033[0m" << endl;
    cout << "OBS.: O número de Tabelas Pai é 10!\n" << endl;
    // cout << "Deseja alocar espaço para quantos nós? ";
    cout << "Escolha uma das opções abaixo: " << endl;
    cout << "1 - Criar nova tabela" << endl;
    cout << "2 - Ler de um arquivo" << endl;

    cin >> op1;

    HashTableVector* hv;


    if(op1 == 1){
        int n;
        cout << "Digite o número de nós: ";
        cin >> n;
        hv = new HashTableVector(n);
    }else if(op1 == 2){
        vector<string> txtFiles;

        fs::path currentDir = fs::current_path();
        for(const auto& entry : fs::directory_iterator(currentDir)){
            if(entry.is_regular_file() && entry.path().extension() == ".txt"){
                txtFiles.push_back(entry.path().filename().string());
            }
        }

        if(txtFiles.size() == 0){
            cout << "Não há arquivos .txt no diretório atual!" << endl;
            exit(1);
        }

        cout << "Aqui estão os arquivos .txt encontrados na pasta:" << endl;
        for(int i = 0; i < txtFiles.size(); i++){
            cout << "(" << i+1 << ") - '" << txtFiles[i] << "'" << endl;
        }

        // Solicia ao usuário que escolha um arquivo
        cout << "Digite o número do arquivo que deseja abrir: ";
        int escolha;
        cin >> escolha;

        // Verifica se a escolha é válida
        if((escolha >= 1) && (escolha <= txtFiles.size())){
            cout << "\nVocê escolheu o arquivo: " << txtFiles[escolha - 1] << endl;
        } else {
            cout << "\nEscolha inválida" << endl;
            exit(1);
        }

        string arquivoEscolhido = txtFiles[escolha - 1];

        // Lê o arquivo txt
        fstream newFile(arquivoEscolhido);
        if(!newFile.is_open()){
            cerr << "Erro ao abrir o arquivo!" << endl;
            return 1;
        }

        string line;
        getline(newFile, line);
        stringstream ss(line);

        // cout << ss.str() << endl;
        int n;
        string c1, c2, c3;

        getline(ss, c1, ' ');
        getline(ss, c2, ' ');
        getline(ss, c3, ' ');
        n = stoi(c3);

        c1.clear();
        c2.clear();
        c3.clear();

        hv = new HashTableVector(n);

        while(getline(newFile, line)){
            stringstream ss(line);
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
            hv->insert(novoNo);
        }

        hv->print();
    }



    int op;
    do{
        cout << "TABELA DE OPÇÕES" << endl;
        cout << "1 - Inserir um nó" << endl;
        cout << "2 - Buscar um nó" << endl;
        cout << "3 - Remover um nó" << endl;
        cout << "4 - Imprimir a tabela" << endl;
        cout << "5 - Salvar em um arquivo" << endl;
        cout << "6 - Sair" << endl;
        cout << "Digite a opção desejada: " << endl;
        cin >> op;
        cout << endl;
        switch(op){
            case(1):{
                string chave;
                int valor;
                cout << "Digite a chave: ";
                cin >> chave;
                cout << "Digite o valor: ";
                cin >> valor;
                hv->insert(chave, valor);
                cout << "Nó inserido!" << endl;
                cout << endl;
                break;
            }
            case(2):{
                string chave;
                cout << "Digite a chave: ";
                cin >> chave;
                HashNode* aux = new HashNode();
                aux = hv->getNode(chave);
                if(aux != nullptr){
                    cout << "Nó encontrado!" << endl;
                    aux->info();
                    cout << endl;
                }else{
                    cout << "Nó não encontrado!" << endl;
                    cout << endl;
                }
                break;
            }
            case(3):{
                string chave;
                cout << "Digite a chave: ";
                cin >> chave;

                if(hv->remove(chave)){
                    cout << "Nó removido!" << endl;
                    cout << endl;
                }else{
                    cout << "Nó não encontrado!" << endl;
                    cout << endl;
                }
                break;
            }
            case(4):{
                hv->print();
                break;
            }
            case(5):{
                FILE* file = fopen("hashDB.txt", "w");
                if(file == nullptr){
                    cerr << "Erro ao abrir o arquivo!" << endl;
                    return 1;
                }
                hv->write(file);
                fclose(file);
                break;
            }
            case(6):{
                cout << "Saindo..." << endl;
                op = 6;
                break;
            }
            default:{
                cout << "Opção inválida!" << endl;
                break;
            }
        }
    }while(op != 6);

    return 0;
}