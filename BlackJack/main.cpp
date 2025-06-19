#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

enum Tipo{TREBOLES = 1, DIAMANTES, CORAZONES, PICAS};

int cartasBarajeadas[52] = {0};
int conteo = 0;

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
    string nombre;
    int puntos = 0;
};

struct Partida{
    //puntos y juego
    int mazoJug[10] = {0};
    int puntosJug = 0;
    int mazoCasa[10] = {0};
    int puntosCasa = 0;
};

struct Juego{
    int cantidad;
    Partida *partida;
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
            return "Desconocido";
            break;
    }
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

void barajeo( ){
    for (int i=0; i<52; i++){
        cartasBarajeadas[i] = i;
        cout<<cartasBarajeadas[i]<<endl;
    }
    cout<<endl;
    srand(time(NULL));
        for (int i = 51; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(cartasBarajeadas[i], cartasBarajeadas[j]);
        }
    cout << "\nCartas barajeadas (índices):\n";
        for (int i = 0; i < 52; i++) {
            cout << cartasBarajeadas[i] <<endl;
        }
}

void crearPartidas(struct Juego* juego, struct Cartas* cartas){
    juego->partida = (struct Partida*) malloc(juego->cantidad * sizeof(struct Partida));
}

int darCarta(struct Cartas* cartas){
    int valorAs=0;
    if(cartas->datosCartas[cartasBarajeadas[conteo]].valor == 1){
        do{
            cout<<"Que valor eliges?, 1 o 11: ";
            cin>>valorAs;
        }while(valorAs != 1 && valorAs != 11);
    }
    return cartasBarajeadas[conteo++];
}

void rondasJuego(struct Juego* juego, struct Jugador* jugador, struct Cartas* cartas){
    //Rondas de BlackJack
    for(int i = 0; i<juego->cantidad; i++){
        
        //ronda i
        //reparto 2 cartas cada uno
        juego->partida[i].mazoJug[0] = darCarta(cartas);
        juego->partida[i].mazoCasa[0] = darCarta(cartas);
        juego->partida[i].mazoJug[1] = darCarta(cartas);
        juego->partida[i].mazoCasa[1] = darCarta(cartas);
        
        cout<<"Carta jugador: \n"<< cartas->datosCartas[ juego->partida[i].mazoJug[0]].nombre <<endl
                               <<cartas->datosCartas[ juego->partida[i].mazoJug[1]].nombre <<endl;
        cout<<"Carta casa: \n"<< cartas->datosCartas[ juego->partida[i].mazoCasa[0]].nombre <<endl
                            <<cartas->datosCartas[ juego->partida[i].mazoCasa[1]].nombre <<endl;
        
    }
}

int main( ){
    Cartas cartas;
    Juego juego;
    Jugador jugador;
    
    crearBaraja(&cartas);
    
    cout<<" --- BLACKJACK --- \n";
    
    for(int i=0; i<cartas.cant; i++){
        cout<<"Nombre: "<<cartas.datosCartas[i].nombre<<" Valor: "<<cartas.datosCartas[i].valor<<endl;
    }
    
    cout<<"\nIngresa tu nombre: ";
    getline(cin, jugador.nombre);
    
    do{
        cout<<"\nCuantas rondas quieres jugar "<<jugador.nombre<<": ";
        cin>>juego.cantidad;
    } while(juego.cantidad<1);
    
    crearPartidas(&juego, &cartas);
    barajeo();
    rondasJuego(&juego, &jugador, &cartas);
    
    free(juego.partida);
    free(cartas.datosCartas);
    return 0;
}
