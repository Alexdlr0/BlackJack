#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

enum Tipo{TREBOLES = 1, DIAMANTES, CORAZONES, PICAS};

struct DatosCartas{
    int tipo;
    char nombre[20];
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

string tipoCarta(int tipo){
    switch(tipo){
        case 1:
            return "Treboles";
            break;
        case 2:
            return "Diamantes";
            break;
        case 3:
            return "Corazones";
            break;
        case 4:
            return "Picas";
            break;
        default:
            break;
    }
    return 0;
}

void crearBaraja(struct Cartas* cartas){
    int cant = cartas->cant;
    cartas->datosCartas = (struct DatosCartas*) malloc(cant * sizeof(struct DatosCartas));
    
    for(int i=0; i<cant; i++){
        int tipo = i / 13+1;
        int valor = i % 13 + 1;
        cartas->datosCartas[i].tipo = tipo;
        
        char nombreCarta[20];
        
        if(valor == 11){
            strcpy(nombreCarta, "J");
            cartas->datosCartas[i].valor = 10;
        }else if(valor == 12){
            strcpy(nombreCarta, "Q");
            cartas->datosCartas[i].valor = 10;
        }else if(valor == 13){
            strcpy(nombreCarta, "K");
            cartas->datosCartas[i].valor = 10;
        }else{
            snprintf(nombreCarta, sizeof(nombreCarta), "%d", valor);
            cartas->datosCartas[i].valor = valor;
        }
        
        char nombreFinal[20];
        snprintf(nombreFinal, sizeof(nombreFinal), "%s de %s", nombreCarta, tipoCarta(tipo).c_str());
        
        strcpy(cartas->datosCartas[i].nombre, nombreFinal);
        
    }
}

int main( ){
    Cartas cartas;
    crearBaraja(&cartas);
    
    cout<<" --- BLACKJACK --- \n";
    
    for(int i=0; i<cartas.cant; i++){
        cout<<"Nombre: "<<cartas.datosCartas[i].nombre<<" Valor: "<<cartas.datosCartas[i].valor<<endl;
    }
    
    return 0;
}
