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
        cout << "6. Buscar conexao\n";
        cout << "7. Imprimir grafo completo\n";
        cout << "8. Busca em largura (a partir de um usuario)\n";
        cout << "9. Mostrar componentes conexas\n";
        cout << "0. Sair\n\n";
        cout << "Escolha: ";
        while (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Valor invalido! Digite um numero inteiro: ";
        }
        cout << endl;

        switch (opcao) {
        case 1:
            cin.ignore();
            cout << "Nome: ";
            getline(cin, nome);
            cout << "Idade: ";
            while (!(cin >> idade)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Valor invalido! Digite um numero inteiro: ";
            }
            cout << endl;
            g.adicionarVertice(nome, idade);
            break;

        case 2:
            cin.ignore();
            cout << "Usuario 1: ";
            getline(cin, nome);
            cout << "Usuario 2: ";
            getline(cin, nome2);
            cout << endl;
            g.adicionarAresta(nome, nome2);
            break;

        case 3:
            cin.ignore();
            cout << "Nome do usuario: ";
            getline(cin, nome);
            cout << endl;
            g.removerVertice(nome);
            break;

        case 4:
            cin.ignore();
            cout << "Usuario 1: ";
            getline(cin, nome);
            cout << "Usuario 2: ";
            getline(cin, nome2);
            cout << endl;
            g.removerAresta(nome, nome2);
            break;

        case 5:
            cin.ignore();
            cout << "Nome do usuario: ";
            getline(cin, nome);
            cout << endl;
            if (g.existeVertice(nome)) {
                cout << "Usuario encontrado:\n";
                g.mostrarUsuario(nome);
            } else {
                cout << "Usuario nao existe.\n";
            }
            break;

        case 6:
            cin.ignore();
            cout << "Usuario 1: ";
            getline(cin, nome);
            cout << "Usuario 2: ";
            getline(cin, nome2);
            cout << endl;

            if (g.existeAresta(nome, nome2)) {
                cout << "Conexao existe entre '" << nome << "' e '" << nome2 << "'.\n\n";

                cout << "=== Dados do Usuario 1 ===\n";
                g.mostrarUsuario(nome);
                cout << endl;

                cout << "=== Dados do Usuario 2 ===\n";
                g.mostrarUsuario(nome2);
            } else {
                cout << "Conexao nao existe.\n";
            }
            break;

        case 7:
            g.imprimirGrafo();
            break;

        case 8:
            cin.ignore();
            cout << "Origem: ";
            getline(cin, nome);
            g.BFS(nome);
            break;

        case 9:
            g.componentesConexas();
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
