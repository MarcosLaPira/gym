/*
 * alumnos.h
 *
 *  Created on: 28 jun. 2022
 *      Author: lapir
 */

#ifndef ALUMNOS_H_
#define ALUMNOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "alumnos.h"
#include "laibrery.h"
#include "controlador.h"
#include "parser.h"

#define LENSEXO 15
#define LENNOMBRE 51
#define LENFECHAINICIO 15
typedef struct
{
	int id;
	char nombre[LENNOMBRE];
	char apellido[LENNOMBRE];
	char sexo;   //char sexo[LENSEXO];
	float abono;
	int horarioClase;
	char actividad[LENNOMBRE];
	char fechaInicio[LENFECHAINICIO];
	char estadoAbono[LENNOMBRE];
}eAlumnos;



eAlumnos* nuevoAlumno();
eAlumnos* AlumnoNuevoParametroTxt(char* idTxt,char* nombreTxt,char* apellidoTxt,char* sexoTxt,char* actividadTxt,char* abonoTxt,char* horarioClaseTxt, char*  fechaInicioTxt,char* estadoAbonoTxt);
//eAlumnos* AlumnoNuevoParametro(int id,char* nombre,char* apellido,char* sexo,char* actividad,float abono,int horarioClase, char* fechaInicio,char* estadoAbono);
eAlumnos* AlumnoNuevoParametro(int id,char* nombre,char* apellido,char sexo,char* actividad,float abono,int horarioClase, char* fechaInicio,char* estadoAbono);
int alumno_setIdTxt(eAlumnos* this,char* id) ;  /////////////////////////////////
int alumno_setId(eAlumnos*  this,int id);
int alumno_getId(eAlumnos* this,int* id);

int alumno_setNombre(eAlumnos* this,char* nombre);
int alumno_getNombre(eAlumnos* this,char* nombre);

int alumno_setApellido(eAlumnos* this,char* apellido);
int alumno_getApellido(eAlumnos* this, char* apellido);

int alumno_setSexoTxt(eAlumnos* this,char* sexo);
int alumno_setSexo(eAlumnos* this,char sexo);
int alumno_getSexo(eAlumnos* this,char* sexo);
/*
int alumno_setSexo(eAlumnos* this,char* sexo);
int alumno_getSexo(eAlumnos* this,char* sexo);
*/
int alumno_setActividad(eAlumnos* this,char* actividad);
int alumno_getActividad(eAlumnos* this,char* actividad);

int alumno_setAbonoTxt(eAlumnos* this,char* abono);
int alumno_setAbono(eAlumnos* this,float abono);
int alumno_getAbono(eAlumnos* this,float* abono);

int alumno_setHorarioClaseTxt(eAlumnos* this,char* horario) ;  /////////////////////////////////
int alumno_setHorarioClase(eAlumnos*  this,int horario);
int alumno_getHorarioClase(eAlumnos* this,int* horario);

int alumno_setFechaInicioTxt(eAlumnos* this,char* fechaInicio);
int alumno_setFechaInicio(eAlumnos* this,char* fechaInicio);
int alumno_getFechaInicio(eAlumnos* this,char* fechaInicio);

int alumno_setEstadoAbono(eAlumnos* this,char* estadoAbono);
int alumno_getEstadoAbono(eAlumnos* this, char* apellido);


int printeoNombre(char* Auxnombre);

#endif /* ALUMNOS_H_ */
