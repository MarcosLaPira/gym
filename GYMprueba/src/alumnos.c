/*
 * alumnos.c
 *
 *  Created on: 28 jun. 2022
 *      Author: lapir
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "alumnos.h"
#include "laibrery.h"
#include "controlador.h"
#include "parser.h"

static int isValidNombre(char* cadena,int longitud);
static int esNumerica(char* cadena, int limite);
static int isFechaInicio(char* cadena,int limite);

eAlumnos* nuevoAlumno()
{
	eAlumnos* alumnoNuevo = NULL;

	alumnoNuevo = (eAlumnos*)malloc(sizeof(eAlumnos));

	if(alumnoNuevo != NULL)
	{
		alumnoNuevo->id = 0;
		strncpy(alumnoNuevo->nombre," ",LENNOMBRE);
		strncpy(alumnoNuevo->apellido," ",LENNOMBRE);
		//strcpy(alumnoNuevo->sexo,"");
		alumnoNuevo->sexo='c';
		strncpy(alumnoNuevo->actividad," ",LENNOMBRE);
		alumnoNuevo-> abono= 0.0;
		alumnoNuevo ->horarioClase=0;
		strncpy(alumnoNuevo-> fechaInicio," ",LENFECHAINICIO);
		strncpy(alumnoNuevo-> estadoAbono," ",LENNOMBRE);

	}
	else
	{
		free(alumnoNuevo);
		alumnoNuevo=NULL;
	}

	return alumnoNuevo;
}

eAlumnos* AlumnoNuevoParametroTxt(char* idTxt,char* nombreTxt,char* apellidoTxt,char* sexoTxt,char* actividadTxt,char* abonoTxt,char* horarioClaseTxt, char*  fechaInicioTxt,char* estadoAbonoTxt)
{

	eAlumnos* alumnoNuevo = nuevoAlumno ();
	if (alumnoNuevo != NULL)
	{
		if(
			alumno_setIdTxt(alumnoNuevo,idTxt)==0 || ///////////////////////////
			alumno_setNombre(alumnoNuevo,nombreTxt)==0 ||
			alumno_setApellido(alumnoNuevo,apellidoTxt)==0 ||
			alumno_setSexoTxt(alumnoNuevo,sexoTxt)==0 ||
			alumno_setActividad(alumnoNuevo,actividadTxt)==0 ||
			alumno_setAbonoTxt(alumnoNuevo,abonoTxt) ==0 ||
			alumno_setHorarioClaseTxt(alumnoNuevo,horarioClaseTxt) ==0 ||
			alumno_setFechaInicio(alumnoNuevo,fechaInicioTxt)==0 ||
			alumno_setEstadoAbono(alumnoNuevo,estadoAbonoTxt)==0

		)
		{
			free(alumnoNuevo);
			alumnoNuevo = NULL;
		}
	}
	return alumnoNuevo;
}
eAlumnos* AlumnoNuevoParametro(int id,char* nombre,char* apellido,char sexo,char* actividad,float abono,int horarioClase, char* fechaInicio,char* estadoAbono)
{
	eAlumnos* alumnoNuevo = nuevoAlumno ();
	if( id >= 0 && nombre != NULL && apellido != NULL &&  actividad != NULL && abono >= 0 && horarioClase >= 0  && fechaInicio != NULL && estadoAbono != NULL )
	{
		if
		(
			alumno_setId(alumnoNuevo,id)&& ///////////////////////////
			alumno_setNombre(alumnoNuevo,nombre)&&
			alumno_setSexo(alumnoNuevo,sexo)&&
			alumno_setApellido(alumnoNuevo,apellido)&&
			alumno_setActividad(alumnoNuevo,actividad)&&
			alumno_setAbono(alumnoNuevo,abono)&&
			alumno_setHorarioClase(alumnoNuevo,horarioClase)&&
			alumno_setFechaInicio(alumnoNuevo,fechaInicio)&&
			alumno_setEstadoAbono(alumnoNuevo,estadoAbono)
		)
		{

		}
		else
		{
			free(alumnoNuevo);
			alumnoNuevo=NULL;
		}

	}
	return alumnoNuevo;
}
int alumno_setIdTxt(eAlumnos* this,char* id)   /////////////////////////////////
{
	int retorno = 0;
	int auxId;
	if(this != NULL && id != NULL)
	{
		if(esNumerica(id,3))
		{
			retorno = 1;
			auxId=atoi(id);
			this->id =auxId;
		}
	}
	return retorno;
}

int alumno_setId(eAlumnos*  this,int id)
{
	int retorno = 0;
	if(this != NULL && id > 0)
	{
		this->id = id;
		retorno = 1;
	}
	return retorno;
}
int alumno_getId(eAlumnos* this,int* id)
{
	int retorno = 0;
	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 1;
	}
	return retorno;
}

int alumno_setNombre(eAlumnos* this,char* nombre)
{
	int retorno = 0;
	if(this != NULL && nombre!= NULL && isValidNombre(nombre, LENNOMBRE))
	{
		strncpy(this->nombre,nombre,LENNOMBRE);
		retorno = 1;
	}
	return retorno;
}
int alumno_getNombre(eAlumnos* this,char* nombre)
{
	int retorno = 0;
	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre,this->nombre,LENNOMBRE);
		retorno = 1;
	}
	return retorno;
}
int alumno_setApellido(eAlumnos* this,char* apellido)
{
	int retorno = 0;
	if(this != NULL &&  apellido != NULL && isValidNombre( apellido, LENNOMBRE) )
	{
		strncpy(this->apellido,apellido,LENNOMBRE);
		retorno = 1;
	}
	return retorno;
}
int alumno_getApellido(eAlumnos* this, char* apellido)
{
	int retorno = 0;
	if(this != NULL && apellido != NULL)
	{
		strncpy(apellido,this->apellido,LENNOMBRE);
		retorno = 1;
	}
	return retorno;
}
int alumno_setSexoTxt(eAlumnos* this,char* sexo)
{
	int retorno = 0;
	char auxSexo;
	if(this != NULL )
	{
		auxSexo= sexo[0];
		this->sexo=auxSexo;
		retorno = 1;
	}
	return retorno;
}

int alumno_setSexo(eAlumnos* this,char sexo)
{
	int retorno = 0;
	if(this != NULL )
	{
		this->sexo=sexo;
		retorno = 1;
	}
	return retorno;
}
int alumno_getSexo(eAlumnos* this,char* sexo)
{
	int retorno = 0;
	if(this != NULL &&  sexo!= NULL)
	{
		*sexo=this->sexo;
		retorno = 1;
	}
	return retorno;
}
int alumno_setActividad(eAlumnos* this,char* actividad)
{

	int retorno = 0;
	if(this != NULL && actividad != NULL && isValidNombre(actividad,LENNOMBRE))
	{
		strncpy(this->actividad,actividad,LENNOMBRE);
		retorno = 1;
	}
	return retorno;
}
int alumno_getActividad(eAlumnos* this,char* actividad)
{
	int retorno = 0;
	if(this != NULL &&   actividad != NULL)
	{
		strncpy( actividad,this->actividad,LENNOMBRE);
		retorno = 1;
	}
	return retorno;
}
int alumno_setAbonoTxt(eAlumnos* this,char* abono)
{
	int retorno = 0;
	float auxiliarPrecio;
	if(this != NULL && abono != NULL )
	{
	//if(esFlotante(precio,10)==0)									/////////////////////////////
		auxiliarPrecio = atof(abono);
		if(auxiliarPrecio >= 0)
		{
			retorno = 1;
			this->abono= auxiliarPrecio;
		}
	}
	return retorno;
}
int alumno_setAbono(eAlumnos* this,float abono)
{
	int retorno = 0;
	if(this != NULL &&  abono>= 1 && abono <= 100000)
	{
		this->abono = abono;
		retorno = 1;
	}
	return retorno;
}
int alumno_getAbono(eAlumnos* this,float* abono)
{
	int retorno = 0;
	if(this != NULL && abono != NULL)
	{
		*abono = this->abono;
		retorno = 1;
	}
	return retorno;
}
int alumno_setHorarioClaseTxt(eAlumnos* this,char* horarioClase)   /////////////////////////////////
{

	int retorno = 0;
	int auxHorario;
	if(this != NULL && horarioClase != NULL)
	{
		if(esNumerica(horarioClase,3))
		{
			auxHorario = atoi(horarioClase);
			this->horarioClase =auxHorario;
			retorno = 1;
		}
	}
	return retorno;
}

int alumno_setHorarioClase(eAlumnos* this,int horarioClase)
{
	int retorno = 0;
	if(this != NULL && horarioClase >= 1 && horarioClase <= 24)
	{
		this->horarioClase = horarioClase;

		retorno = 1;
	}
	return retorno;
}
int alumno_getHorarioClase(eAlumnos* this,int* horarioClase)
{
	int retorno = 0;
	if(this != NULL && horarioClase!= NULL)
	{
		*horarioClase= this->horarioClase;
		retorno = 1;
	}
	return retorno;
}


int alumno_setFechaInicio(eAlumnos* this, char* fechaInicio)
{
	int retorno = 0;
	if(this != NULL && fechaInicio != NULL /*&& isFechaInicio(fechaInicio, LENFECHAINICIO)*/)
	{
		strncpy(this->fechaInicio,fechaInicio,LENFECHAINICIO);
		retorno = 1;
	}
	return retorno;
}
int alumno_getFechaInicio(eAlumnos* this,char* fechaInicio)
{
	int retorno = 0;
	if(this != NULL && fechaInicio != NULL)
	{
		strcpy( fechaInicio,this-> fechaInicio);

		retorno = 1;
	}
	return retorno;
}
int alumno_setEstadoAbono(eAlumnos* this,char* estadoAbono)
{
	int retorno = 0;
	if(this != NULL && estadoAbono != NULL && isValidNombre( estadoAbono, LENNOMBRE) )
	{
		strcpy(this->estadoAbono,estadoAbono);
		retorno = 1;
	}
	return retorno;
}
int alumno_getEstadoAbono(eAlumnos* this, char* estadoAbono)
{
	int retorno = 0;
	if(this != NULL &&  estadoAbono != NULL)
	{
		strcpy(estadoAbono,this->estadoAbono);
		retorno = 1;
	}
	return retorno;
}
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int isValidNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			cadena[i] =tolower(cadena[i]);

			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es numerica, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int esNumerica(char* cadena, int limite)
{
	int retorno = -1; // ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
			//CONTINUE
		}
		//BREAK
	}
	return retorno;
}

static int isFechaInicio(char* cadena,int limite)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && limite> 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < limite; i++)
		{
			if(cadena[i]=='/')
			{
				continue;
			}
			if(isalpha(cadena[i]))
			{
				retorno = 0;
				break;
			}

		}
	}
	return retorno;
}
/*
static int esFlotante(char* cadena,int limite)
 {
 	int retorno = 1;
 	int flagDecimal=1;
 	int i;
 	if(cadena != NULL && limite>0)
 	{
 		for(i=0; i < limite && cadena[i] != '\0';i++)
 		{
 			if(flagDecimal==1 && i !=0 && cadena[i]=='.')
 			{
 				flagDecimal=0;
 				continue;
 			}
 			if(cadena[i] < '0' || cadena[i] > '9')
 			{
 				retorno = 0;
 				break;
 			}
 		}
 	}
 	return retorno;
 }
*/
/**********************************************************************/

int printeoNombre(char* Auxnombre)
{
	int retorno=1;

	printf("nombre es: %s",Auxnombre);
		return retorno;
}
