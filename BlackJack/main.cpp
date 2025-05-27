#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

enum Tipo{TREBOLES = 1, DIAMANTES, CORAZONES, PICAS};

struct DatosCartas{
    int tipo;
    int valor;
};
struct Cartas{
    int cant = 52;
    DatosCartas *datosCartas;
};

struct Jugador{
    //Nombre, puntos y juego
};

struct Casa{
    //puntos y juego
};

void crearBaraja(struct Cartas* cartas){
    int cant = cartas->cant;
    cartas->datosCartas = (struct DatosCartas*) malloc(cant * sizeof(struct DatosCartas));
    
    for(int i=0; i<cant; i++){
        if(i<13){
            cartas->datosCartas[i].tipo = 1;
            if(i<10){
                cartas->datosCartas[i].valor = i+1;
            }else{
                cartas->datosCartas[i].valor = 10;
            }
        }
        if(i>=13 && i<26){
            cartas->datosCartas[i].tipo = 2;
            if(i<23){
                cartas->datosCartas[i].valor = i+1-13;
            }else{
                cartas->datosCartas[i].valor = 10;
            }
        }
        if(i>=26 && i<39){
            cartas->datosCartas[i].tipo = 3;
            if(i<36){
                cartas->datosCartas[i].valor = i+1-26;
            }else{
                cartas->datosCartas[i].valor = 10;
            }

        }
        if(i>=39 && i<52){
            cartas->datosCartas[i].tipo = 4;
            if(i<49){
                cartas->datosCartas[i].valor = i+1-39;
            }else{
                cartas->datosCartas[i].valor = 10;
            }

        }
    }
    
}

string tipoCarta(){
    return 0;
};

int main( ){
    //srand((unsigned int)time(NULL));
    Cartas cartas;
    crearBaraja(&cartas);
    
    cout<<" --- BLACKJACK --- \n";
    
    for(int i=0; i<cartas.cant; i++){
        cout<<"Tipo: "<<cartas.datosCartas[i].tipo<<"  Valor: "<<cartas.datosCartas[i].valor<<endl;
    }
    
    return 0;
}
