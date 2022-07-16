/*
 * controlador.h
 *
 *  Created on: 28 jun. 2022
 *      Author: lapir
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "alumnos.h"
#include "laibrery.h"
#include "controlador.h"
#include "parser.h"

int controladorIniciarPrograma( LinkedList* listaAlumnos,char* path);

int controladorAgregarAlumno( LinkedList* listaAlumnos);

int controladorModificarAlumno( LinkedList* listaAlumnos);

int controladorBajaDeAlumno(LinkedList* listaAlumnos);

int controladorInformes(LinkedList* listaAlumnos);

int controladorEstadisticas(LinkedList* listaAlumnos);

int controladrSalvar(LinkedList* listaAlumnos,char* path);

int controller_idSubSiguiente (LinkedList* pArrayListaAlumnos);

int controller_findById(LinkedList* pArrayListPassenger,int idABuscar);

int controlerResetearDatos(LinkedList* pArrayListPassenger);

#endif /* CONTROLADOR_H_ */
