/*
 * parser.c
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

//char id[4096],nombre[4096],apellido[4096],abono[4096],horarioclase[8],estado abono[4096]; vencimiento
int parserAlumnoModoTexto(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = 0;
	int cant;


	int cont=0;
	char id[4096],nombre[4096],apellido[4096],sexo[4096],actividad[4096],abono[4096],horarioClase[8],fechaInicio[4096],estadoAbono[4096];

	eAlumnos* pAuxAlumno;
	if (pFile == NULL)
	{
		printf("\n Error al abrir el archivo dentro del parser");
		retorno = 0;
		exit (EXIT_FAILURE);
	}
	else
	{
		//lectura famtasma de primer linea
		//fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
								//id,nombre,apellido,sexo,actividad,abono,horarioClase,fechaInicio,estadoAbono);
		while(!feof(pFile))
		{
			cont++;
			cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					id,nombre,apellido,sexo,actividad,abono,horarioClase,fechaInicio,estadoAbono);
			if(cant!=9)  //if(cant!=9)
			{
				printf("\n error dentro del archivo, recibe mas datos de los que se pueden ");
				break;
			}
			else
			{
				pAuxAlumno = AlumnoNuevoParametroTxt(id,nombre,apellido,sexo,actividad,abono,horarioClase,fechaInicio,estadoAbono);

				if(pAuxAlumno != NULL)
				{
					ll_add(pArrayListPassenger,pAuxAlumno);
					retorno = 1;
				}
			}

		}
	}
    return retorno;
}
