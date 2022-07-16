/*
 * laibrery.h
 *
 *  Created on: 11 may. 2022
 *      Author: lapir
 */

#ifndef LAIBRERY_H_
#define LAIBRERY_H_



//

int myGets(char* cadena, int tamanio);

int utn_getNombre(char array [], int tamanio, char* mensaje, char* mensajeError, int reintentos );

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

int getNumeroFlotante(float* pResultado, char mensaje[], char errorMensaje[], float minimo, float maximo, int reintentos);


int getAlfanumerico(char* inPut,char mensaje[], char errorMensaje[],int tamano, int reintentos);

int getCadenaTelefonica(char inPut[],char mensaje[], char errorMensaje[],int tamano, int reintentos);

int esLetraConEspacio(char inPut[],char mensaje[], char errorMensaje[],int tamano, int reintentos);
int esSoloLetra(char inPut[],char mensaje[], char errorMensaje[],int tamano, int reintentos);

int getFechaInicio(char* inPut,char mensaje[], char errorMensaje[],int tamano, int reintentos);


/*



// ordenamiento
int ordenamientoArrayEfectivoDecendente(int array[], int tamanio); //EFECTIVA

int ordenamientoArrayEfectivoAscendente(int array[], int tamanio); //EFECTIVA


int ordenamientoArrayAscendente (int array[], int tamanio); // NO efectiva 2 for

int ordenamientoArrayDecendente (int array[], int tamanio); // NO efectiva 2 for

void insertionAscendente(int array[],int tamanio);

void insertionDecendente(int array[],int tamanio);


int mostrarArrayDecendente (int array[], int tamanio);

int mostrarArrayAscendente (int array[], int tamanio);

int promedioArray (int array[], int tamanio , float* pResultadoPromedio);


//
int buscarLibre(char espacio[], int tamanio, int* lugar);
*/
#endif /* LAIBRERY_H_ */
