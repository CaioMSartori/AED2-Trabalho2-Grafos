#include "Grafo.h"
#include <iostream>

using namespace std;

int main() {
    Grafo g(50);   // Capacidade máxima

    int opcao;
    string nome, nome2;
    int idade;

    do {
        cout << "\n===== MENU - REDE SOCIAL =====\n";
        cout << "1. Adicionar usuario\n";
        cout << "2. Adicionar conexao\n";
        cout << "3. Remover usuario\n";
        cout << "4. Remover conexao\n";
        cout << "5. Buscar usuario\n";
        cout << "6. Imprimir grafo completo\n";
        cout << "7. Busca em largura (a partir de um usuario)\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Nome: ";
            cin >> nome;
            cout << "Idade: ";
            cin >> idade;
            g.adicionarVertice(nome, idade);
            break;

        case 2:
            cout << "Usuario 1: ";
            cin >> nome;
            cout << "Usuario 2: ";
            cin >> nome2;
            g.adicionarAresta(nome, nome2);
            break;

        case 3:
            cout << "Nome do usuario: ";
            cin >> nome;
            g.removerVertice(nome);
            break;

        case 4:
            cout << "Usuario 1: ";
            cin >> nome;
            cout << "Usuario 2: ";
            cin >> nome2;
            g.removerAresta(nome, nome2);
            break;

        case 5:
            cout << "Nome do usuario: ";
            cin >> nome;
            if (g.existeVertice(nome))
                cout << "Usuario encontrado.\n";
            else
                cout << "Usuario nao existe.\n";
            break;

        case 6:
            g.imprimirGrafo();
            break;

        case 7:
            cout << "Origem: ";
            cin >> nome;
            g.BFS(nome);
            break;

        case 0:
            cout << "Encerrando...\n";
            break;

        default:
            cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}
