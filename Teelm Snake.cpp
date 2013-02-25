/*
    Teelm Snake: minijuego libre bajo licencia Gnu para fines pedagógicos
    compartiendo conocimientos, promoviendo el aprendizaje y habilidades
    de programación en C++.

    Juan Valadez, www.grupo-teelm.tk
*/

// Version 1.0

#include <stdlib.h> // Incluye funcion <rand> (Valores aleatorio)
#include "miniwin.h" // Libreria grafica
using namespace std;
using namespace miniwin;

#define PX 15 // Tamaño cuadrado
#define LIMX 30 // Limite X (Horizontal)
#define LIMY 20 // Limite Y (Vertical)

// Tupla (agrupación de variables)
// Propiedades Snake
struct t_sn {
    // Ejes, largo, direccion
    int x[500], y[500], num, dir;
};

// Propiedades comida
struct t_pts {
    // Ejes
    int x, y;
    // Disponible <si> o <no>
    bool d;
};

t_sn sn; // Declarando snake
t_pts cm; // Declara Comida

void juego_inicializar() {
    sn.dir=12; // Direccion: arriba
    sn.num=3; // 3 Cuadros de largo
    // Centrar ejes
    for (int i=0; i<3; i++) {
        sn.x[i]=LIMX/2;
        sn.y[i]=LIMY/2;
    }
}

void juego_terminado() {
    espera(1000);
    juego_inicializar();
}

 // Pinta cuadrado (15*15 pixeles)
void cuadrado(int x, int y) {
    rectangulo_lleno(1+x*PX,1+y*PX,(x+1)*PX,(y+1)*PX);
}

void lm_pinta() {
    color_rgb(100,100,100); // Gris
    // Horizontales
    for (int x=0; x<LIMX; x++) {
        cuadrado(x,0); // Arriba
        cuadrado(x,LIMY-1); // Abajo
    }
    // Verticales
    for (int y=0; y<LIMY; y++) {
        cuadrado(0,y); // Izquierda
        cuadrado(LIMX-1,y); // Derecha
    }
}

void sn_control(int k) {
    // Teclas
    if (k==ARRIBA && sn.dir!=6)    sn.dir=12;
    else if (k==DERECHA && sn.dir!=9)   sn.dir=3;
    else if (k==ABAJO && sn.dir!=12)    sn.dir=6;
    else if (k==IZQUIERDA && sn.dir!=3) sn.dir=9;
    // Repinta cola
    for (int i=sn.num; i>0; i--) {
        sn.x[i]=sn.x[i-1];
        sn.y[i]=sn.y[i-1];
    }
    // Mover cabeza
    if (sn.dir==6 && sn.y[0]<LIMY-2)  sn.y[0]++;
    else if (sn.dir==9 && sn.x[0]>1)  sn.x[0]--;
    else if (sn.dir==12 && sn.y[0]>1) sn.y[0]--;
    else if (sn.dir==3 && sn.x[0]<LIMX-2)  sn.x[0]++;
    // Juego termina
    else juego_terminado();
    for (int i=1; i<sn.num; i++) {
        if (sn.x[0]==sn.x[i] && sn.y[0]==sn.y[i]) juego_terminado();
    }
    // Coge punto
    if (sn.x[0]==cm.x && sn.y[0]==cm.y) {
        sn.num++;
        cm.d=0;
    }
}

void sn_pinta() {
    color_rgb(0,200,0); // Verde
    for (int i=0; i<sn.num; i++)
        cuadrado(sn.x[i],sn.y[i]);
}

void cm_genera() {
    // Genera ejes
    cm.x=1+rand()%(LIMX-3);
    cm.y=1+rand()%(LIMY-3);
    cm.d=1; // Punto si existe
}

void cm_pinta() {
    color_rgb(200,0,0);// Rojo
    cuadrado(cm.x, cm.y);
}

int main() {
    srand(time(0)); // Semilla aleatoria
    // Tamaño ventana
    vredimensiona(LIMX*PX+1,LIMY*PX+1);
    int key=tecla(); // Tecla
    juego_inicializar();
    while(key!=ESCAPE) {
        key=tecla(); // Lee tecla
        borra(); // Limpia
        sn_control(key); // Snake control
        sn_pinta(); // Snake pinta
        cm_pinta(); // Comida pinta
        lm_pinta(); // Limites pinta
        refresca();
        if (cm.d==0) // Comida detecta
            cm_genera();
        espera(100); // Milisegundos
    }
    vcierra(); // Ventana cierra
    return 0;
}
