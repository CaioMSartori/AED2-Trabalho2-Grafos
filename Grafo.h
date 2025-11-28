// Caio Monteiro Sartori   NUSP: 15444598
// Mateus Henrique Jesus da Silva Carriel   NUSP: 15698362
// Murilo Augusto Jorge   NUSP: 15552251

// Grafo.h -> Definição da classe de Grafos

#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>

using namespace std;

struct Usuario {
    string nome;
    int idade;
    int seguindo;
    int seguidores;

    Usuario(string n = "", int i = 0) {   // Inicializador de usuário vazio
        nome = n;
        idade = i;
        seguindo = 0;
        seguidores = 0;
    }
};

class Grafo {
private:
    int maxVertices;   // Tamanho máximo de usuários na rede
    int numVertices;   // Tamanho atual de usuários na rede

    vector<Usuario> usuarios;   // Vetor de usuários
    vector<vector<int>> matriz;   // Matriz de adjacência

    int indiceDe(const string& nome);   // Retorna índice de usuário na matriz

public:
    Grafo(int maxV);   // Construtor da classe

    void imprimirGrafo();   // Método de impressão do grafo/rede social
    void mostrarUsuario(const string& nome);   // Método de exibição de dados do usuário

    bool existeVertice(const string& nome);   // Método de busca de usuário
    bool existeAresta(const string& u, const string& v);   // Método de busca de conexão

    void adicionarVertice(const string& nome, int idade);   // Método de inserção de usuário
    void adicionarAresta(const string& u, const string& v);   // Método de inserção de conexão

    void removerVertice(const string& nome);   // Método de remoção de usuário
    void removerAresta(const string& u, const string& v);   // Método de remoção de conexão

    void BFS(const string& origem);   // Método de busca em largura geral
    void BFS_Caminho(const string& origem, const string& destino);   // Método de busca em largura com usuário final
    void recomendarAmigos(const string& nome);   // Método de recomendação de amigos com BFS
};

#endif
