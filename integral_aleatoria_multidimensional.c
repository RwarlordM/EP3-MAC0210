#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <float.h>

long double f(long double x){
    return sin(x);
}

long double g(long double x){
    return pow(x, 3);
}

long double h(long double x){
    return exp(-x);
}

int p(long double x, long double y) {
    if (pow(x,2) + pow(y,2) <= 1)
        return 1;
    else 
        return 0;
}

long double aproximacao_integral_monte_carlo_uni_f(double a, double b, int n){
    long double integral = 0.0;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        long double valor = rand() % 100000;
        valor = valor/100000;
        integral += f(valor);
    }
    return integral / n;
}

long double aproximacao_integral_monte_carlo_uni_g(double a, double b, int n){
    long double integral = 0.0;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        long double valor = rand() % 100000;
        valor = (b-a)*valor/100000+a;
        integral += g(valor)/n;
    }
    return (b-a) * integral;
}

long double aproximacao_integral_monte_carlo_uni_h(double a, double b, int n){
    long double integral = 0.0;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        long double valor = rand() % 1000000;
        //valor = valor/100000;
        integral += h(valor);
    }
    return (b-a) * integral / n;
}

long double aproximacao_integral_monte_carlo_multi(int n){
    long double aproximacao_integral = 0.0;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        long double U_1 = rand() % 100000;
        long double U_2 = rand() % 100000;
        U_1 /= 100000;
        U_2 /= 100000;
        aproximacao_integral += p(U_1, U_2);
    }
    return aproximacao_integral / n;
}

int main(){

    // Testes Monte Carlo Unidimensional:
    // 1) sin(x)
    printf("Aproximação da integral do seno de 0 a 1: %Lf\n", 
           aproximacao_integral_monte_carlo_uni_f(0.0, 1.0, 100000));
    // 2) x ^ 3
    printf("Aproximação da integral de x^3 de 3 a 7: %Lf\n", 
           aproximacao_integral_monte_carlo_uni_g(3.0, 7.0, 1000000));
    // 3) e^(-x)
    printf("Aproximação da integral de e^(-x) de 0 a +inf: %Lf\n", 
           aproximacao_integral_monte_carlo_uni_h(0.0, 1000000.0, 10000000));

    // Teste Monte Carlo Multidimensional:
    printf("Aproximação do valor de PI: %Lf\n", 
           4 * aproximacao_integral_monte_carlo_multi(500000));

    return 0;
}