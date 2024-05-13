#include <iostream>
#include <vector>
#include <deque>
using namespace std;

using Iterador = vector<int>::iterator;

bool EsImpar(int value) {
    return value % 2 != 0;
}

bool EsPar(int value) {
    return value % 2 == 0;
}

template<typename T>
bool MayorA6(T value) {
    return value > 6;
}

// Puntero a funcion
using Callable = bool (*) (int);


auto crear_vector(Iterador inicio, Iterador fin, Callable condicion) {
    vector<Iterador::value_type> result;
    for (auto it = inicio; it != fin; ++it)
        if(condicion(*it)) {
            result.emplace_back(*it);
        }
    return result;
}

template<template<typename...>class TContainer = vector, typename Iterator, typename Unary>
auto crear_container(Iterator inicio, Iterator fin, Unary condicion) {
    TContainer<typename Iterator::value_type> result;
    for (auto it = inicio; it != fin; ++it)
        if(condicion(*it)) {
            result.emplace_back(*it);
        }
    return result;
}

void ejemplo_crear_vector() {
    vector<double> v1 = {10, 2, 4, 7, 3, 10, 6, 9, 8};
    // auto v2 = crear_vector(begin(v1), end(v1), MayorA6);
    auto v2 = crear_container(begin(v1), end(v1), MayorA6<double>);
    for (const auto& item: v2) {
        cout << item << " ";
    }
}

template <template<typename...>class TContainer = vector, typename T>
void print(ostream& os, const TContainer<T>& v) {
    for (const auto& item: v)
        os << item << " ";
}

void crear_puntero_a_print() {
    void (*ptr_fun)(ostream&, const vector<int>&) = nullptr;

    vector<int> v1 = {10, 2, 4, 7, 3, 10, 6, 9, 8};
    ptr_fun = print<vector, int>;
    ptr_fun(cout, v1);

}

int main() {
    // ejemplo_crear_vector();
    crear_puntero_a_print();
    return 0;
}
