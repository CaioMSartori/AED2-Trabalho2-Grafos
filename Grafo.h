#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>

using namespace std;

struct Usuario {
    string nome;
    int idade;
    int conexoes;   // Número de conexões

    Usuario(string n = "", int i = 0) {   // Inicializador de usuário vazio
        nome = n;
        idade = i;
        conexoes = 0;
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

    void BFS(const string& origem);   // Método de busca em largura
    void componentesConexas();   // Método de geração de componentes conexos do grafo usando busca em largura
};

#endif
