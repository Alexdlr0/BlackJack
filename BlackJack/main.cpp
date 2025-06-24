#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<fstream>
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
    }
    cout<<endl;
    srand(time(NULL));
        for (int i = 51; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(cartasBarajeadas[i], cartasBarajeadas[j]);
        }
}

void crearPartidas(struct Juego* juego, struct Cartas* cartas){
    juego->partida = (struct Partida*) malloc(juego->cantidad * sizeof(struct Partida));
}


int darCarta(struct Cartas* cartas, struct Juego* juego, bool turno, int ronda){
    int indice = cartasBarajeadas[conteo++];
    int valor = cartas->datosCartas[indice].valor;

    cout<<cartas->datosCartas[indice].nombre<<endl;

    //Assss
    if(valor == 1 && turno == 0) {
        int valorAs = 0;
        do{
            cout<<" --- Qué valor eliges? 1 o 11: ";
            cin>>valorAs;
        }while(valorAs != 1 && valorAs != 11);
        valor = valorAs;
    }

    if(turno == 0) {
        juego->partida[ronda].puntosJug += valor;
    }else{
        if(valor == 1 && (juego->partida[ronda].puntosCasa + 11 <= 21)){
            valor = 11;
        }
        juego->partida[ronda].puntosCasa += valor;
    }
    return valor;
}

void rondasJuego(struct Juego* juego, struct Jugador* jugador, struct Cartas* cartas){
    
    fstream file;
    file.open("../resultados.txt", ios::app);
    if(!file){
        cout<<"Error al abrir archivo\n";
    }
    file<<endl;
    time_t now = time(0);
        tm *ltm = localtime(&now);
        file <<"\nFecha: "
             <<1900 + ltm->tm_year << "/"
             <<1 + ltm->tm_mon << "/"
             <<ltm->tm_mday << " "
             <<ltm->tm_hour << ":"
             <<(ltm->tm_min < 10 ? "0" : "") << ltm->tm_min
             <<"\n";
    file<<jugador->nombre<<" Partidas: "<<juego->cantidad;
    
    for(int i=0; i<juego->cantidad; i++){
        bool turno = 0; // 0 jugador, 1 casa

        cout<<"\n --- Ronda " <<i + 1<< " ---\n";
        juego->partida[i].puntosJug = 0;
        juego->partida[i].puntosCasa = 0;

        // Jugador
        cout<<"\nMazo del jugador:\n";
        turno = 0;
        int posJug = 0;
        juego->partida[i].mazoJug[posJug++] = darCarta(cartas, juego, turno, i);
        juego->partida[i].mazoJug[posJug++] = darCarta(cartas, juego, turno, i);
        cout<<"Puntos jugador: "<<juego->partida[i].puntosJug<<endl;

        char opcion;
        while(juego->partida[i].puntosJug < 21){
            cout<<"\nQuieres otra carta? (s/n): ";
            cin>>opcion;
            if(opcion == 's' || opcion == 'S'){
                juego->partida[i].mazoJug[posJug++] = darCarta(cartas, juego, turno, i);
                cout<<"Puntos jugador: "<<juego->partida[i].puntosJug<<endl;
            }else {
                break;
            }
        }

        // Casa
        cout<<"\nMazo de la casa:\n";
        turno = 1;
        int posCasa = 0;
        juego->partida[i].mazoCasa[posCasa++] = darCarta(cartas, juego, turno, i);
        juego->partida[i].mazoCasa[posCasa++] = darCarta(cartas, juego, turno, i);
        cout<<"Puntos casa: "<<juego->partida[i].puntosCasa<<endl;

        while(juego->partida[i].puntosCasa < 17){
            cout<<"Casa pide otra carta...\n";
            juego->partida[i].mazoCasa[posCasa++] = darCarta(cartas, juego, turno, i);
            cout<<"Puntos casa: "<<juego->partida[i].puntosCasa<<endl;
        }
        int pj = juego->partida[i].puntosJug;
        int pc = juego->partida[i].puntosCasa;

        cout<<"\n--- Resultado ronda " <<i + 1<< " ---\n";
        if(pj > 21){
            cout<<"Te pasaste de 21. Gana la casa.\n";
            file<<endl<<"Perdio";
        }else if(pc > 21){
            cout<<"La casa se pasó de 21. ¡Ganas!\n";
            file<<endl<<"Gano";
        }else if(pj > pc){
            cout << "Ganas esta ronda!\n";
            file<<endl<<"Gano";
        }else if(pc > pj){
            cout<<"Gana la casa.\n";
            file<<endl<<"Perdio";
        }else{
            cout<<"Empate.\n";
            file<<endl<<"Empate";
        }
    }
    file.close();
}

int main( ){
    Cartas cartas;
    Juego juego;
    Jugador jugador;
    
    crearBaraja(&cartas);
    
    cout<<" --- BLACKJACK --- \n";

    
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
    
    cout<<endl;
    return 0;
}
