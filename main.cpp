#include <iostream>

using namespace std;

// Definição da estrutura do nó da árvore
struct Node {
        int key;
        Node *left;
        Node *right;
        int height;
};

// Função para obter a altura do nó
int height(Node *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Função para obter o máximo entre dois valores
int max(int a, int b) { return (a > b) ? a : b; }

// Função para criar um novo nó
Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // novo nó é inicialmente adicionado na folha
    return node;
}

// Rotação à direita
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Realizando rotação
    x->right = y;
    y->left = T2;

    // Atualizando alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retornando novo raiz
    return x;
}

// Rotação à esquerda
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Realizando rotação
    y->left = x;
    x->right = T2;

    // Atualizando alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retornando novo raiz
    return y;
}

// Obter o fator de balanceamento do nó
int getBalance(Node *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Função de inserção
Node *insert(Node *node, int key) {
    // Passo 1: Realiza a inserção normal na árvore de busca binária
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas
        return node;

    // Atualiza a altura deste ancestral nó
    node->height = 1 + max(height(node->left), height(node->right)));

    // Obtém o fator de balanceamento deste ancestral nó para verificar se ficou
    // desbalanceado
    int balance = getBalance(node);

    // Se o nó ficar desbalanceado, então existem 4 casos

    // Caso 1: Rotação à direita
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso 2: Rotação à esquerda
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso 3: Rotação esquerda-direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Rotação direita-esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retorna o ponteiro do nó (inalterado)
    return node;
}

// Função de busca na árvore
Node *search(Node *root, int key) {
    // Caso base: root é nulo ou o chave é o mesmo que o root
    if (root == nullptr || root->key == key)
        return root;

    // Chave é maior que o chave do root
    if (root->key < key)
        return search(root->right, key);

    // Chave é menor que o chave do root
    return search(root->left, key);
}

// Função para imprimir a árvore em ordem
void inorder(Node *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node *root = nullptr;

    // Inserindo dados na árvore
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Imprimindo a árvore em ordem
    cout << "A árvore em ordem é: ";
    inorder(root);
    cout << endl;

    // Exemplo de busca
    int key = 30;
    Node *result = search(root, key);
    if (result != nullptr) {
        cout << "Chave " << key << " encontrada na árvore." << endl;
    } else {
        cout << "Chave " << key << " não encontrada na árvore." << endl;
    }

    return 0;
}
