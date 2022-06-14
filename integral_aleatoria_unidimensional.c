#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

long double f(long double x){
    return exp(x);
}

long double g(long double x){
    return sin(x);
}

long double aproximacao_integral(double n){
    long double integral = 0.0;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        long double valor = rand() % 100000;
        valor = valor/100000;
        integral += g(valor)/n;
    }
    return integral;
}

int main(){
    printf("O valor da integral é: %Lf",aproximacao_integral(100000));
    return 0;
}