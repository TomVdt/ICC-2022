#include <iostream>
#include <string>

struct Tree {
    char value;
    Tree *left;
    Tree *right;
};

// Retourne vrai si le caractère passé en paramètre est un opérateur unaire, faux sinon
bool is_unary_operator(char c) {
    return c == '+' || c == '-';
}

// Retourne vrai si le caractère passé en paramètre est un opérateur binaire, faux sinon
bool is_binary_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Retourne la priorité de l'opérateur passé en paramètre (les opérateurs de plus haute priorité ont une priorité plus faible)
int operator_priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

std::string remove_useless_parentheses(Tree *tree) {
    if (tree == nullptr) return "";
    if (tree->left == nullptr && tree->right == nullptr) return std::string(1, tree->value);
    if (tree->left != nullptr && tree->right != nullptr) {
        std::string left = remove_useless_parentheses(tree->left);
        std::string right = remove_useless_parentheses(tree->right);

        if (is_binary_operator(tree->left->value) && operator_priority(tree->left->value) == operator_priority(tree->value)) {
            left = left.substr(1, left.length() - 2);
        }

        if (is_binary_operator(tree->right->value) && operator_priority(tree->right->value) == operator_priority(tree->value)) {
            right = right.substr(1, right.length() - 2);
        }

        return "(" + left + tree->value + right + ")";
    }
    return "";
}

// Fonction pour créer un arbre binaire à partir d'une valeur et de deux sous-arbres
Tree *create_tree(char value, Tree *left, Tree *right) {
    Tree *tree = new Tree();
    tree->value = value;
    tree->left = left;
    tree->right = right;
    return tree;
}

// Fonction pour afficher un arbre binaire sous forme parenthésée
void print_tree(Tree *tree) {
    if (tree == nullptr) return;

    std::cout << remove_useless_parentheses(tree) << std::endl;

    // std::cout << " (";
    // print_tree(tree->left);
    // std::cout << tree->value;
    // print_tree(tree->right);
    // std::cout << ") ";
}

Tree *derive(Tree *tree) {
    if (tree == nullptr) return nullptr;

    // Cas où l'arbre est une feuille (contient une valeur)
    if (tree->left == nullptr && tree->right == nullptr) {
        // Si la valeur est x, la dérivée est 1, sinon elle est 0
        char value = (tree->value == 'x') ? '1' : '0';
        return create_tree(value, nullptr, nullptr);
    }

    // Cas où l'arbre est un opérateur binaire
    if (tree->left != nullptr && tree->right != nullptr) {
        // On calcule la dérivée des sous-arbres
        Tree *left = derive(tree->left);
        Tree *right = derive(tree->right);

        // Selon l'opérateur, on utilise les règles de dérivation pour calculer la dérivée de l'expression
        switch (tree->value) {
            case '+':
            case '-':
                // Pour les opérateurs + et -, la dérivée est la somme des dérivées des sous-arbres
                return create_tree('+', left, right);
            case '*':
                // Pour l'opérateur *, la dérivée est le produit des sous-arbres avec les dérivées des sous-arbres en tant que sous-arbres
                return create_tree('+', create_tree('*', left, tree->right), create_tree('*', tree->left, right));
            case '/':
                // Pour l'opérateur /, la dérivée est la différence des produits des sous-arbres avec les dérivées des sous-arbres en tant que sous-arbres
                // divisée par le carré du sous-arbre droit
                return create_tree(
                    '/',
                    create_tree('-', create_tree('*', left, tree->right), create_tree('*', right, tree->left)),
                    create_tree('*', tree->right, tree->right));
            case '^':
                // Pour l'opérateur ^, la dérivée est le produit de la valeur de l'arbre gauche élevée à la valeur de l'arbre droit
                // moins 1 avec la dérivée du sous-arbre gauche multipliée par la valeur de l'arbre droit
                return create_tree(
                    '*',
                    create_tree('^', tree->left, create_tree('-', tree->right, create_tree('1', nullptr, nullptr))),
                    create_tree('*', tree->right, left));
            default:
                // Si l'opérateur n'est pas reconnu, on retourne nullptr
                return nullptr;
        }
    }

    return nullptr;
}

Tree *simplify(Tree *tree) {
    if (tree == nullptr) return nullptr;

    // Si l'arbre est une feuille (contient une valeur), on le retourne tel quel
    if (tree->left == nullptr && tree->right == nullptr) return tree;

    // Si l'arbre est un opérateur binaire, on calcule la simplification des sous-arbres
    if (tree->left != nullptr && tree->right != nullptr) {
        Tree *left = simplify(tree->left);
        Tree *right = simplify(tree->right);

        // Selon l'opérateur, on utilise des règles de simplification pour calculer la simplification de l'expression
        switch (tree->value) {
            case '+':
                // Pour l'opérateur +, si un des sous-arbres est 0, on retourne l'autre sous-arbre
                if (left->value == '0') return right;
                if (right->value == '0') return left;
                break;
            case '-':
                // Pour l'opérateur -, si le sous-arbre droit est 0, on retourne le sous-arbre gauche
                if (right->value == '0') return left;
                break;
            case '*':
                // Pour l'opérateur *, si un des sous-arbres est 0, on retourne 0
                if (left->value == '0' || right->value == '0') return create_tree('0', nullptr, nullptr);
                // Si un des sous-arbres est 1, on retourne l'autre sous-arbre
                if (left->value == '1') return right;
                if (right->value == '1') return left;
                break;
            case '/':
                // Pour l'opérateur /, si le sous-arbre droit est 1, on retourne le sous-arbre gauche
                if (right->value == '1') return left;
            case '^':
                // Pour l'opérateur ^, si le sous-arbre droit est 0, on retourne 1
                if (right->value == '0') return create_tree('1', nullptr, nullptr);
                // Si le sous-arbre droit est 1, on retourne le sous-arbre gauche
                if (right->value == '1') return left;
                break;
            default:
                // Si l'opérateur n'est pas reconnu, on retourne nullptr
                return nullptr;
        }

        // Si aucune simplification n'a été effectuée, on retourne l'arbre avec les sous-arbres simplifiés
        return create_tree(tree->value, left, right);
    }

    // Si l'arbre n'a qu'un sous-arbre, on retourne la simplification de ce sous-arbre
    return simplify(tree->left != nullptr ? tree->left : tree->right);
}

int main() {
    // Création des arbres représentant les expressions a, b et x
    Tree *a = create_tree('a', nullptr, nullptr);
    Tree *b = create_tree('b', nullptr, nullptr);
    Tree *x = create_tree('x', nullptr, nullptr);

    // Création de l'arbre représentant l'expression (x + a) * (x + b)
    // Tree *tree = create_tree('*', create_tree('+', x, a), create_tree('+', x, b));
    Tree *tree = create_tree('/', create_tree('+', x, a), create_tree('-', x, b));

    // Calcul de la dérivée de l'expression
    Tree *derivative = derive(tree);

    Tree *simplified = simplify(derivative);

    // Affichage de la dérivée
    print_tree(tree);
    std::cout << std::endl;
    print_tree(derivative);
    std::cout << std::endl;
    print_tree(simplified);
    std::cout << std::endl;

    Tree *no = create_tree('*', create_tree('*', x, a), create_tree('/', x, b));

    print_tree(simplify(no));
    std::cout << std::endl;

    return 0;
}