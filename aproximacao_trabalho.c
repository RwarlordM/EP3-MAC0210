#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define tamanho 7 

long double valores_x[] = {0,5,10,15,20,25,30};
long double valores_gx[] = {0.0000,1.5297,9.5120,8.7025,2.8087,1.0881,0.3537};
long double pesos_lagrange[tamanho]; 
long double pesos_y_lagrange[tamanho]; 
long double matriz_diferencas_divididas[tamanho][tamanho];

void calcula_pesos_lagrange(){
    for(int i = 0; i < tamanho; i++){
        long double produtorio = 1.0;
        for(int j = 0; j < tamanho; j++){
            if(i != j) produtorio *= (valores_x[j] - valores_x[i]);
        }
        pesos_lagrange[i] = 1/produtorio;
        pesos_y_lagrange[i] = (1/produtorio) * valores_gx[i];
    }
    for(int i = 0; i < tamanho; i++){
        printf("valor: %Lf\n",pesos_lagrange[i]);
    }
}

long double interpolacao_lagrange(long double x){
    long double dividendo = 0.0, divisor = 0.0;
    for(int i = 0; i < tamanho; i++){
        dividendo += pesos_y_lagrange[i]/(x - valores_x[i]);
        divisor += pesos_lagrange[i]/(x - valores_x[i]);
    }
    //if(isnan(dividendo)) printf("dividendo: %Lf", x);
    //if(isnan(divisor)) printf("dividendo: %Lf", x);
    //if(isnan(dividendo/divisor)) printf("divisao: %Lf", x);
    return dividendo/divisor;
}

void calcula_matriz_newton(){
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0) matriz_diferencas_divididas[i][j] = valores_gx[i];
            else{
                matriz_diferencas_divididas[i][j] = (matriz_diferencas_divididas[i][j-1]-matriz_diferencas_divididas[i-1][j-1])/(valores_x[i]-valores_x[i-j]);
            }
        }
    }
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j <= i; j++){
            printf("%Lf ",matriz_diferencas_divididas[i][j]);
        }
        printf("\n");
    }
}

long double interpolacao_newton(long double x){
    long double total = 0.0;
    for(int i = 0; i < tamanho; i++){
        long double val = matriz_diferencas_divididas[i][i];
        for(int j = 0; j < i; j++){
            val *= (x - valores_x[j]);
        }
        total += val;
    }
    return total;
}

long double trapezio_composto_newton(long double h){
    long double integral = interpolacao_newton(0) + interpolacao_newton(30);
    long double i = 0.05;
    while(i < 30){
        integral += 2*interpolacao_newton(i);
        i += h;
    }
    return (h/2)*integral;
}

long double trapezio_composto_lagrange(long double h){
    long double integral = valores_gx[0] + valores_gx[7];
    long double i = 0.05;
    while(i < 30){
        integral += 2*interpolacao_lagrange(i);
        /*if(isnan(integral)){
            printf("i: %Lf\n",i);
        }*/
        i += h;
    }
    return (h/2)*integral;
}

long double simpson_composto_newton(long double h){
    long double integral = interpolacao_newton(0) + interpolacao_newton(30);
    long double i = 0.05;
    bool impar = false;
    while(i < 30){
        if(impar){
            integral += 2*interpolacao_newton(i);
            impar = false;
        }
        else{
            integral += 4*interpolacao_newton(i);
            impar = true;
        }
        i += h;
    }
    return (h/3)*integral;
}

long double simpson_composto_lagrange(long double h){
    long double integral = valores_gx[0] + valores_gx[7];
    long double i = 0.05;
    bool impar = false;
    while(i < 30){
        if(impar){
            /*if(5 - h < i < 5 + h || 10 - h < i < 10 + h || 15 - h < i < 15 + h || 20 - h < i < 20 + h || 25 - h < i < 25 + h) {
                //printf("valoriii %Lf",i);
                integral += 2*valores_gx[(int) i/5];
            }
            else {
                integral += 2*interpolacao_lagrange(i);
            }*/
            integral += 2*interpolacao_lagrange(i);
            impar = false;
        }
        else{
            /*if(5 - h < i < 5 + h || 10 - h < i < 10 + h || 15 - h < i < 15 + h || 20 - h < i < 20 + h || 25 - h < i < 25 + h) {
                //printf("valoriii %Lf",i);
                integral += 4*valores_gx[(int) i/5];
            }
            else {
                integral += 4*interpolacao_lagrange(i);
            }*/
            integral += 4*interpolacao_lagrange(i);
            impar = true;
        }
        i += h;
    }
    return (h/3)*integral;
}

int main(){
    calcula_pesos_lagrange();
    calcula_matriz_newton();
    printf("Aproximação com Trapézio Composto e Interpolação com Polinômios de Lagrange: %Lf\n",trapezio_composto_lagrange(0.1));
    printf("Aproximação com Trapézio Composto e Interpolação com Polinômios de Newton: %Lf\n",trapezio_composto_newton(0.1));
    printf("Aproximação com Simpson Composto e Interpolação com Polinômios de Lagrange: %Lf\n",simpson_composto_lagrange(0.1));
    printf("Aproximação com Simpson Composto e Interpolação com Polinômios de Newton: %Lf\n",simpson_composto_newton(0.1));
    return 0;
}