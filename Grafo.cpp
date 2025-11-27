#include "Grafo.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

Grafo::Grafo(int maxV) {
    maxVertices = maxV;
    numVertices = 0;

    usuarios.resize(maxV);
    matriz.assign(maxV, vector<int>(maxV, 0));
}

int Grafo::indiceDe(const string& nome) {
    for (int i = 0; i < numVertices; i++)
        if (usuarios[i].nome == nome)
            return i;
    return -1;
}

bool Grafo::existeVertice(const string& nome) {
    return indiceDe(nome) != -1;
}

bool Grafo::existeAresta(const string& u, const string& v) {
    int a = indiceDe(u);
    int b = indiceDe(v);

    if (a == -1 || b == -1) return false;
    return matriz[a][b] == 1;
}

void Grafo::adicionarVertice(const string& nome, int idade) {
    if (numVertices == maxVertices) {
        cout << "Limite maximo de usuarios atingido.\n";
        return;
    }

    if (existeVertice(nome)) {
        cout << "Usuario '" << nome << "' ja existe.\n";
        return;
    }

    usuarios[numVertices] = Usuario(nome, idade);
    numVertices++;

    cout << "Usuario '" << nome << "' adicionado com sucesso.\n";
}

void Grafo::adicionarAresta(const string& u, const string& v) {
    int a = indiceDe(u);
    int b = indiceDe(v);

    if (a == -1 || b == -1) {
        cout << "Um dos usuarios nao existe.\n";
        return;
    }

    if (matriz[a][b] == 1) {
        cout << "Conexao ja existe.\n";
        return;
    }

    matriz[a][b] = 1;
    matriz[b][a] = 1;

    usuarios[a].conexoes++;
    usuarios[b].conexoes++;

    cout << "Conexao criada entre '" << u << "' e '" << v << "'.\n";
}

void Grafo::removerVertice(const string& nome) {
    int idx = indiceDe(nome);

    if (idx == -1) {
        cout << "Usuario nao encontrado.\n";
        return;
    }

    // Remover conexões com os outros usuários
    for (int i = 0; i < numVertices; i++) {
        if (matriz[idx][i] == 1)
            usuarios[i].conexoes--;
    }

    // Deslocar usuários
    for (int i = idx; i < numVertices - 1; i++)
        usuarios[i] = usuarios[i + 1];

    // Deslocar linhas para cima
    for (int i = idx; i < numVertices - 1; i++)
        matriz[i] = matriz[i + 1];

    // Deslocar colunas para a esquerda
    for (int i = 0; i < numVertices - 1; i++)
        for (int j = idx; j < numVertices - 1; j++)
            matriz[i][j] = matriz[i][j + 1];

    for (int i = 0; i < numVertices; i++) {
        matriz[numVertices - 1][i] = 0;  // zera última linha
        matriz[i][numVertices - 1] = 0;  // zera última coluna
    }

    numVertices--;

    cout << "Usuario '" << nome << "' removido da rede.\n";
}

void Grafo::removerAresta(const string& u, const string& v) {
    int a = indiceDe(u);
    int b = indiceDe(v);

    if (a == -1 || b == -1) {
        cout << "Um dos usuarios nao existe.\n";
        return;
    }

    if (matriz[a][b] == 0) {
        cout << "Conexao nao existe.\n";
        return;
    }

    matriz[a][b] = 0;
    matriz[b][a] = 0;

    usuarios[a].conexoes--;
    usuarios[b].conexoes--;

    if (usuarios[a].conexoes < 0) usuarios[a].conexoes = 0;
    if (usuarios[b].conexoes < 0) usuarios[b].conexoes = 0;

    cout << "Conexao removida.\n";
}

void Grafo::imprimirGrafo() {
    cout << "\n===== Lista de Usuarios =====\n";

    if (numVertices == 0) {
        cout << "Nao ha usuarios cadastrados.\n";
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        cout << usuarios[i].nome
             << " | Idade: " << usuarios[i].idade
             << " | Conexoes: " << usuarios[i].conexoes
             << "\n";
    }

    cout << "\n===== Matriz de Adjacencia =====\n\n";

    int largura = 10;
    cout << setw(largura) << " ";

    for (int i = 0; i < numVertices; i++)
        cout << setw(largura) << usuarios[i].nome;
    cout << "\n";

    for (int i = 0; i < numVertices; i++) {
        cout << setw(largura) << usuarios[i].nome;
        for (int j = 0; j < numVertices; j++)
            cout << setw(largura) << matriz[i][j];
        cout << "\n";
    }
}

void Grafo::BFS(const string& origem) {
    int start = indiceDe(origem);

    if (start == -1) {
        cout << "Usuario nao encontrado.\n";
        return;
    }

    vector<bool> visitado(numVertices, false);
    queue<int> fila;

    visitado[start] = true;
    fila.push(start);

    cout << "\nBusca em largura a partir de '" << origem << "': ";

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        cout << usuarios[atual].nome << " ";

        for (int i = 0; i < numVertices; i++) {
            if (matriz[atual][i] == 1 && !visitado[i]) {
                visitado[i] = true;
                fila.push(i);
            }
        }
    }

    cout << "\n";
}
