#include <iostream>
#include <vector>
#include <deque>
using namespace std;


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
using Iterador = vector<int>::iterator;
using Callable = bool (*) (int);


auto crear_vector(Iterador inicio, Iterador fin, Callable condicion) {
    vector<Iterador::value_type> result;
    for (auto it = inicio; it != fin; ++it)
        if(condicion(*it)) {
            result.emplace_back(*it);
        }
    return result;
}

template<template<typename...>class TContainer = vector, typename Iterator, typename UnaryPredicate>
auto crear_container(Iterator inicio, Iterator fin, UnaryPredicate condicion) {
    TContainer<typename Iterator::value_type> result;
    for (auto it = inicio; it != fin; ++it)
        if(condicion(*it)) {
            result.emplace_back(*it);
        }
    return result;
}

void ejemplo_crear_vector() {
    vector<int> v1 = {10, 2, 4, 7, 3, 10, 6, 9, 8};
    auto v2 = crear_vector(begin(v1), end(v1), EsPar);
    auto v3 = crear_container(begin(v1), end(v1), MayorA6<double>);
    for (const auto& item: v2) {
        cout << item << " ";
    }
}

void ejemplo_crear_container() {
    vector<double> v1 = {10, 2, 4, 7, 3, 10, 6, 9, 8};
    auto v2 = crear_container(begin(v1), end(v1), [](auto v) { return v > 6; });
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

void crear_lambda() {
    auto lambda_sumar = [](auto a, auto b) { return a + b; };
    cout << lambda_sumar(10, 30) << endl;

    cout << [](auto a, auto b) { return a + b; }(10, 20);

    double pi = 3.1415;
    auto calcular_area_elipse = [pi](auto a, auto b) mutable {
//        pi = 3.14;
        return a*b*pi;
    };
    cout << calcular_area_elipse(10, 20);
    pi = 3.141596;
    cout << calcular_area_elipse(10, 20);
}

class calcular_area_elipse {
    const double pi;
public:
    explicit calcular_area_elipse(double pi): pi(pi) {}
    double operator()(double a, double b) const { return a*b*pi; }
};

void ejemplo_funcion_objeto() {
    double pi = 3.1415;
    auto cae = calcular_area_elipse(pi);
    cout << cae(10, 20);
};

int main() {
//    ejemplo_crear_vector();
//    ejemplo_crear_container();
    ejemplo_funcion_objeto();
//    crear_puntero_a_print();
    return 0;
}
