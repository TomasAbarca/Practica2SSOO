//
//  LineaR.h
//  SSOO2C
//
//  Created by Tomás Abarca Cerro.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>


#ifndef LineaR_h
#define LineaR_h

using namespace std;
/*Clase LineaR: Esta clase incluye el objeto LineaR, este objeto es la linea donde se encuentra la palabra que el usuario ha introducido*/
class LineaR{
private:
    int n_hilo;
    int linea_ini;
    int linea_fin;
    int n_linea;
    string palabra_a;
    string palabra;
    string palabra_d;
public:
    LineaR(int,int,int,int,string,string,string);
    void mostrarResultado();
};
/*Constructor del objeto LineaR, cada objeto tiene su numero de hilo, la linea inicial y final que cada hilo lee,
 el numero de linea donde se ha encontrado la palabra, la palabra anterior a la palabra elegida, la palabra elegida y la palabra posterior*/
LineaR::LineaR(int _n_hilo,int _linea_ini, int _linea_fin,int _n_linea,string _palabra_a, string _palabra, string _palabra_d){
    n_hilo=_n_hilo;
    linea_ini=_linea_ini;
    linea_fin=_linea_fin;
    n_linea=_n_linea;
    palabra_a=_palabra_a;
    palabra=_palabra;
    palabra_d=_palabra_d;
}
/*LineaR::mostrarResultado(): Este metodo muestra un objeto LineaR por pantalla segun el formato de salida establecido*/
void LineaR::mostrarResultado(){
    cout<<"[Hilo "<<n_hilo<<" inicio: "<<linea_ini<<" - final: "<<linea_fin<<"] :: linea "<<n_linea<<" :: ... "<<palabra_a<<" "<<palabra<<" "<<palabra_d<<" ..."<<endl;
    /*FORMATO DE SALIDA: [Hilo 1 inicio:0 – final: 25] :: línea 12 :: ... el castillo antiguo ...*/
}

#endif /* LineaR_h */
