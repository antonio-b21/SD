#include <iostream>
#include <string>

template <class T>
struct tree {
    T info = T();
    tree* left = nullptr;
    tree* right = nullptr;
};

template <class T>
void inorder(tree<T>* current, std::streamsize level = 0) {
    if (current != nullptr) {
        inorder(current->left, level + 1);
        std::cout.width(level * 4);
        std::cout << "";
        std::cout << current->info << "\n";
        inorder(current->right, level + 1);
    }
}

template <class T>
void preorder(tree<T>* current, std::streamsize level = 0) {
    if (current != nullptr) {
        std::cout.width(level * 4);
        std::cout << "";
        std::cout << current->info << "\n";
        preorder(current->left, level + 1);
        preorder(current->right, level + 1);
    }
}

template <class T>
tree<T>* insert(tree<T>* current, T key) {
    if (current == nullptr) {
        current = new tree<T>;
        current->info = key;
    } else if (key < current->info) {
        current->left = insert(current->left, key);
    } else if (key >= current->info) {
        current->right = insert(current->right, key);
    }
    return current;
}

template <class T>
bool search(tree<T>* current, T key) {
    if (current == nullptr) {
        return false;
    } else if (key < current->info) {
        return search(current->left, key);
    } else if (key > current->info) {
        return search(current->right, key);
    } else {
        return true;
    }
}

template <class T>
tree<T>* erase(tree<T>* current, T key) {
    if (current == nullptr) {
        return current;
    } else if (key < current->info) {
        current->left = erase(current->left, key);
        return current;
    } else if (key > current->info) {
        current->right = erase(current->right, key);
        return current;
    } else {
        if (current->left == nullptr and current->right == nullptr) {
            delete current;
            return nullptr;
        } else if (current->left != nullptr and current->right == nullptr) {
            tree<T>* aux = current->left;
            delete current;
            return aux;
        } else if (current->right != nullptr and current->left == nullptr) {
            tree<T>* aux = current->right;
            delete current;
            return aux;
        } else {
            tree<T>* right = current->right;
            while (right->left != nullptr) {
                right = right->left;
            }
            current->info = right->info;
            current->right = erase(current->right, current->info);
            return current;
        }
    }
}

void ex1() {
    tree<int>* root = nullptr;
    root = insert(root, 6); insert(root, 4); insert(root, 9); insert(root, 9); insert(root, 2); insert(root, 1); insert(root, 5); insert(root, 3); insert(root, 7); insert(root, 8);
    std::cout << search(root, 5) << " " << search(root, 10) << "\n";
    root = erase(root, 6);
    inorder(root);  std::cout << "------------------\n";
    preorder(root); std::cout << "------------------\n";
}

void ex2() {
    std::string words[10] = { "f", "b", "e", "i", "h", "d", "a", "g", "j", "c" };
    tree<std::string>* root = nullptr;
    for (int i = 0; i < 10; i++) { root = insert(root, words[i]); }
    inorder(root);
}

template <class T>
void between(tree<T>* current, T lower, T upper, std::streamsize level = 0) {
    if (current != nullptr) {
        if (lower < current->info) {
            between(current->left, lower, upper, level + 1);
        }
        if (lower < current->info and current->info < upper) {
            std::cout.width(level * 4);
            std::cout << "";
            std::cout << current->info << "\n";
        }
        if (current->info < upper) {
            between(current->right, lower, upper, level + 1);
        }
    }
}

void ex3() {
    tree<int>* root = nullptr;
    root = insert(root, 6); insert(root, 4); insert(root, 9); insert(root, 9); insert(root, 2); insert(root, 1); insert(root, 5); insert(root, 3); insert(root, 7); insert(root, 8);
    between(root, 2, 7);
}

int main()
{
    ex1();
    ex2();
    ex3();

    return 0; 
}
