// Caio Monteiro Sartori   NUSP: 15444598
// Mateus Henrique Jesus da Silva Carriel   NUSP: 15698362
// Murilo Augusto Jorge   NUSP: 15552251

// Grafo.cpp -> Implementação dos métodos da classe de Grafos

#include "Grafo.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <algorithm>

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

void Grafo::mostrarUsuario(const string& nome) {
    int i = indiceDe(nome);

    if (i == -1) {
        cout << "Usuario nao encontrado.\n";
        return;
    }

    cout << "Nome: " << usuarios[i].nome << "\n";
    cout << "Idade: " << usuarios[i].idade << "\n";
    cout << "Seguindo: " << usuarios[i].seguindo << "\n";
    cout << "Seguidores: " << usuarios[i].seguidores << "\n\n";

    cout << "Segue: ";
    bool temSeguindo = false;
    for (int j = 0; j < numVertices; j++) {
        if (matriz[i][j] == 1) {
            cout << usuarios[j].nome << ", ";
            temSeguindo = true;
        }
    }
    if (!temSeguindo) cout << "Ninguem";
    cout << "\n";

    cout << "Seguidores: ";
    bool temSeg = false;
    for (int j = 0; j < numVertices; j++) {
        if (matriz[j][i] == 1) {
            cout << usuarios[j].nome << ", ";
            temSeg = true;
        }
    }
    if (!temSeg) cout << "Nenhum";
    cout << "\n";
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
    if (u == v) {
        cout << "Um usuario nao pode seguir a si mesmo.\n";
        return;
    }

    int a = indiceDe(u);
    int b = indiceDe(v);

    if (a == -1 || b == -1) {
        cout << "Um dos usuarios nao existe.\n";
        return;
    }

    if (matriz[a][b] == 1) {
        cout << "Usuario '" << u << "' ja segue '" << v << "'.\n";
        return;
    }

    matriz[a][b] = 1;

    usuarios[a].seguindo++;
    usuarios[b].seguidores++;

    cout << "'" << u << "' agora segue '" << v << "'.\n";
}

void Grafo::removerVertice(const string& nome) {
    int idx = indiceDe(nome);

    if (idx == -1) {
        cout << "Usuario nao encontrado.\n";
        return;
    }

    for (int j = 0; j < numVertices; j++) {
        if (matriz[idx][j] == 1) {
            usuarios[j].seguidores--;
        }
    }

    for (int i = 0; i < numVertices; i++) {
        if (matriz[i][idx] == 1) {
            usuarios[i].seguindo--;
        }
    }

    for (int i = idx; i < numVertices - 1; i++)
        usuarios[i] = usuarios[i + 1];

    for (int i = idx; i < numVertices - 1; i++)
        matriz[i] = matriz[i + 1];

    for (int i = 0; i < numVertices - 1; i++)
        for (int j = idx; j < numVertices - 1; j++)
            matriz[i][j] = matriz[i][j + 1];

    for (int i = 0; i < numVertices; i++) {
        matriz[numVertices - 1][i] = 0;
        matriz[i][numVertices - 1] = 0;
    }

    numVertices--;

    cout << "Usuario '" << nome << "' removido.\n";
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

    usuarios[a].seguindo--;
    usuarios[b].seguidores--;

    cout << "Conexao removida.\n";
}

void Grafo::imprimirGrafo() {
    cout << "===== Lista de Usuarios =====\n";

    if (numVertices == 0) {
        cout << "Nao ha usuarios cadastrados.\n";
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        cout << usuarios[i].nome
             << " | Idade: " << usuarios[i].idade
             << " | Seguindo: " << usuarios[i].seguindo
             << " | Seguidores: " << usuarios[i].seguidores
             << "\n";
    }

    cout << "\n===== Matriz de Adjacencia (Direcionada) =====\n\n";

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
    vector<int> ordem;

    visitado[start] = true;
    fila.push(start);

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        ordem.push_back(atual);

        for (int i = 0; i < numVertices; i++) {
            if (matriz[atual][i] == 1 && !visitado[i]) {
                visitado[i] = true;
                fila.push(i);
            }
        }
    }

    cout << "\nBusca em largura a partir de '" << origem << "': ";
    for (size_t i = 0; i < ordem.size(); i++) {
        cout << usuarios[ordem[i]].nome;
        if (i < ordem.size() - 1) cout << ", ";
    }
    cout << "\n";
}

void Grafo::BFS_Caminho(const string& origem, const string& destino) {
    int start = indiceDe(origem);
    int end = indiceDe(destino);

    if (start == -1 || end == -1) {
        cout << "Origem ou destino nao encontrado.\n";
        return;
    }

    vector<bool> visitado(numVertices, false);
    vector<int> anterior(numVertices, -1);
    queue<int> fila;

    visitado[start] = true;
    fila.push(start);

    bool achou = false;

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        if (atual == end) {
            achou = true;
            break;
        }

        for (int i = 0; i < numVertices; i++) {
            if (matriz[atual][i] == 1 && !visitado[i]) {
                visitado[i] = true;
                anterior[i] = atual;
                fila.push(i);
            }
        }
    }

    if (!achou) {
        cout << "\nNao existe caminho de " << origem << " para " << destino << ".\n";
        return;
    }

    vector<int> caminho;
    for (int v = end; v != -1; v = anterior[v])
        caminho.push_back(v);

    reverse(caminho.begin(), caminho.end());

    cout << "\nCaminho de '" << origem << "' ate '" << destino << "': ";
    for (size_t i = 0; i < caminho.size(); i++) {
        cout << usuarios[caminho[i]].nome;
        if (i < caminho.size() - 1) cout << " -> ";
    }
    cout << "\n";
}

void Grafo::recomendarAmigos(const string& nome) {
    int u = indiceDe(nome);

    if (u == -1) {
        cout << "Usuario nao encontrado.\n";
        return;
    }

    vector<int> seguindo;
    for (int j = 0; j < numVertices; j++)
        if (matriz[u][j] == 1)
            seguindo.push_back(j);

    if (seguindo.empty()) {
        cout << nome << " nao segue ninguem, sem recomendacoes.\n";
        return;
    }

    vector<int> score(numVertices, 0);

    for (int s : seguindo) {
        for (int k = 0; k < numVertices; k++) {
            if (matriz[s][k] == 1) {
                score[k]++;
            }
        }
    }

    score[u] = 0;
    for (int s : seguindo) score[s] = 0;

    bool alguma = false;
    for (int i = 0; i < numVertices; i++)
        if (score[i] > 0)
            alguma = true;

    if (!alguma) {
        cout << "Nenhuma recomendacao para " << nome << ".\n";
        return;
    }

    cout << "Recomendacoes para " << nome << ":\n";
    for (int i = 0; i < numVertices; i++) {
        if (score[i] > 0) {
            cout << "- " << usuarios[i].nome
                 << " (seguido por " << score[i] << " pessoas que voce segue)\n";
        }
    }
}
