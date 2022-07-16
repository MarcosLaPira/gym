/*
 * controlador.c
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

////INFORMES
static int informeCompleto(LinkedList* listaAlumnos);
static int informePersonalizado(LinkedList* listaAlumnos);
static int informeFuncional(LinkedList* listaAlumnos);
static int informeFutbol(LinkedList* listaAlumnos);
static int informeCrossfit(LinkedList* listaAlumnos);
static void  controlador_printAlumno(eAlumnos* pAlumno);
static void  controlador_printEspecifico(eAlumnos* pAlumno);

int controladorIniciarPrograma(LinkedList* listaAlumnos,char* path)
{
	int retorno=0;
	FILE* pFile;


	if (listaAlumnos != NULL && path != NULL)
	{
		pFile = fopen(path,"r");
		if (pFile == NULL)
		{
			printf("\nERROR al abrir el archivo.\n");
		}
		else
		{
			if(parserAlumnoModoTexto(pFile, listaAlumnos))
			{
				retorno = 1;
			}
		}
	}

	fclose(pFile);
	return retorno;
}

int controladorAgregarAlumno(LinkedList* listaAlumnos)
{
	eAlumnos* pNuevoAlumno;

	int retorno=0;

	int auxId;

	char auxNombre[LENNOMBRE];
	char auxApellido[LENNOMBRE];

	int auxSexo;
	char descripcionSexo;

	int auxActividad;
	char descripcionActividad[LENNOMBRE];

	float auxAbono;

	int auxHorarioClase;

	char auxFechaInicio[LENFECHAINICIO];

	int auxEstadoAbono;
	char descripcionEstadoAbono[LENNOMBRE];

	if(listaAlumnos != NULL )
	{
		auxId = controller_idSubSiguiente(listaAlumnos);

		if(
				utn_getNombre(auxNombre,LENNOMBRE,"\n Ingresar nombre del alumno \n","\nError \n", 2) == 0 &&
				utn_getNombre(auxApellido,LENNOMBRE,"\n Ingresar el apellido del alumno\n","\nError \n", 2) == 0 &&
				utn_getNumero(&auxSexo,"\n Ingresar sexo del alumno:\n 1-Masculino \n 2-Femenino ","\nError.\n",1,2,2)==0 &&
				utn_getNumero(&auxActividad,"\n Ingresar actividad:\n 1-Personalizado \n 2-Funcional \n 3-Futbol \n 4-Crossfit","\nError.\n",1,4,2)==0 &&
				getNumeroFlotante(&auxAbono,"\n Ingresar cuota a pagar por el alumno","\nError.\n",1.0,500000.0,2)==0 &&
				utn_getNumero(&auxHorarioClase,"\n Ingresar el horario de la clase","\nError.\n",0,24,2)==0 &&
				getFechaInicio(auxFechaInicio,"\n Ingresar la fecha de inicio\n","\nError \n",LENFECHAINICIO, 2) == 0 &&
				utn_getNumero(&auxEstadoAbono,"\n Indicar el estado del abono:\n 1-Activo\n 2-Vencido\n","\nError.\n",1,2,2)==0
			)
		{

			//sexo
			switch(auxSexo)
			{
			case 1:
				descripcionSexo='m';
				break;
			case 2:
				descripcionSexo='f';
			break;
			}

			//actividad		1-Personalizado \n 2-Funcional \n 3-Futbol \n 3-Crossfit"
			//sexo
			switch(auxActividad)
			{
				case 1:
					strncpy(descripcionActividad,"personalizado",LENNOMBRE);
					break;
				case 2:
					strncpy(descripcionActividad,"funcional",LENNOMBRE);
					break;
				case 3:
					strncpy(descripcionActividad,"futbol",LENNOMBRE);
					break;
				case 4:
					strncpy(descripcionActividad,"crossfit",LENNOMBRE);
					break;
			}

			switch(auxEstadoAbono)
			{
				case 1:
					strncpy(descripcionEstadoAbono,"activo",LENNOMBRE);
					break;
				case 2:
					strncpy(descripcionEstadoAbono,"inactivo",LENNOMBRE);
					break;
			}
			auxId++;

			pNuevoAlumno=AlumnoNuevoParametro(auxId,auxNombre,auxApellido,descripcionSexo,descripcionActividad,auxAbono,auxHorarioClase,auxFechaInicio,descripcionEstadoAbono);

			if(pNuevoAlumno != NULL)
			{

				ll_add(listaAlumnos,pNuevoAlumno);
				retorno=1;
			}
			else
			{
				free(pNuevoAlumno);
			}


		}

	}


	return retorno;
}

int controladorModificarAlumno( LinkedList* listaAlumnos)
{
	int retorno=0;
	int idMax;
	int bufferId;
	int bufferIndice;
	int subMenu;

	char auxNombre[LENNOMBRE];
	char auxApellido[LENNOMBRE];

	float auxAbono;

	int auxActividad;
	char descripcionActividad[LENNOMBRE];

	int auxHorarioClase;

	char auxFechaInicio[LENFECHAINICIO];

	int auxEstadoAbono;
	char descripcionEstadoAbono[LENNOMBRE];

	eAlumnos* pAlumno;
	//validar lista
	if(listaAlumnos != NULL)
	{
		//obtener id maximo
		idMax=controller_idSubSiguiente ( listaAlumnos);
		//imprimir alumnos
		informeCompleto(listaAlumnos);
		//pedir id a modificar
		if(utn_getNumero(&bufferId,"\n \n \n ingrese el numero de id que desea modificar","\n error",1,idMax,2)==0)
		{
			//retorno indice con el id
			bufferIndice=controller_findById(listaAlumnos,bufferId) ;
			if(bufferIndice >= 0)
			{
				// obtenemos el nodo llget
				pAlumno= ll_get(listaAlumnos,bufferIndice);
				if(pAlumno != NULL)
				{
					//creo submenu
					do
					{
						//pregunto que desea modificar
						if(utn_getNumero(&subMenu,"\n Ingrese opcion que desea modificar:"
							"\n1-Nombre\n 2-Apellido \n 3- Abono \n 4- Horario clase \n 5- Actividad \n "
							"6- Fecha inicio \n 7- Estado Abono \n 8- Volver al menu \n ","\n error",1,8,2)==0)
						switch(subMenu)
						{
							case  1://nombre
								if(utn_getNombre(auxNombre,LENNOMBRE,"\n Ingrese el nombre. \n","\nError. \n", 2)== 0)
								{
									if(alumno_setNombre(pAlumno,auxNombre))
										{
											printf("\n Nombre modificado con exito \n ");
										}
								}
								break;
							case  2://apellido
								if(utn_getNombre(auxApellido,LENNOMBRE,"\n Ingrese el apellido. \n","\nError. \n", 2)== 0)
								{
									if(alumno_setApellido(pAlumno,auxApellido))
										{
											printf("\n Apellido modificado con exito \n ");
										}
								}
								break;
							case  3://abono
								if(getNumeroFlotante(&auxAbono,"\n Ingrese el nuevo abono.","\nError. \n",1.0,500000.0,2)==0)
									{
										if(alumno_setAbono(pAlumno,auxAbono))
										{
											printf("\n Abono modificado con exito  \n ");
										}
									}
								break;
							case  4://horario Clase
								if(utn_getNumero(&auxHorarioClase,"Ingrese nuevo horario","\n error",1,24,2)==0)
								{
									if(alumno_setHorarioClase(pAlumno,auxHorarioClase))
									{
										printf("\n Horario modificado con exito \n ");
									}
								}

								break;
							case 5 ://actividad
								if(utn_getNumero(&auxActividad,"\n Ingresar nueva actividad :\n 1-Personalizado \n 2-Funcional \n 3-Futbol \n 4-Crossfit","\nError.\n",1,4,2)==0)
								{
									switch(auxActividad)
									{
										case 1:
											strncpy(descripcionActividad,"personalizado",LENNOMBRE);
											break;
										case 2:
											strncpy(descripcionActividad,"funcional",LENNOMBRE);
											break;
										case 3:
											strncpy(descripcionActividad,"futbol",LENNOMBRE);
											break;
										case 4:
											strncpy(descripcionActividad,"crossfit",LENNOMBRE);
											break;
									}
									if(alumno_setActividad(pAlumno,descripcionActividad))
									{
										printf("\n Actividad modificada con exito \n ");
									}
								}

								break;
							case  6: //fecha inicio
								if(getFechaInicio(auxFechaInicio,"\n Ingresar la fecha de inicio\n","\nError \n",LENFECHAINICIO, 2) == 0 )
								{
									if(alumno_setFechaInicio(pAlumno,auxFechaInicio))
									{
										printf("\n Fecha de inicio modificada con exito \n ");
									}
								}
								break;
							case  7: //estado abono
								if(utn_getNumero(&auxEstadoAbono,"\n Indicar el estado del abono:\n 1- Activo\n 2-Inactivo\n","\nError.\n",1,2,2)==0)
								{
									switch(auxEstadoAbono)
									{
										case 1:
											strncpy(descripcionEstadoAbono,"activo",LENNOMBRE);
											break;
										case 2:
											strncpy(descripcionEstadoAbono,"inactivo",LENNOMBRE);
											break;
									}
									if(alumno_setEstadoAbono(pAlumno,descripcionEstadoAbono))
									{
										printf("\n Estado abono modificado con exito \n ");
									}

								}
								break;
							case 8:
								if(controlerResetearDatos( listaAlumnos))
								{
									printf("\n Estados de abono reseteados con exito \n ");
								}
								else
								{
									printf("\n ERROR al resetear estados \n ");
								}
								break;

						}
					}while(subMenu != 8);
				}


			}
		}
	}
	return retorno;
}

int controladorBajaDeAlumno(LinkedList* listaAlumnos)
{
	int retorno=0;
	int idMax;
	int bufferId;
	int bufferIndice;
	eAlumnos* pAlumno;

//validar linkelist
	if(listaAlumnos != NULL)
	{
		//obtener id maximo
		idMax=controller_idSubSiguiente ( listaAlumnos);
		//imprimir alumnos
		informeCompleto(listaAlumnos);
		//pedir id a modificar
		if(utn_getNumero(&bufferId,"\n ingrese el numero de id que desea eliminar","\n error",1,idMax,2)==0)
		{
			//busco indice de id
			bufferIndice=controller_findById(listaAlumnos,bufferId) ;
			if(bufferIndice >= 0)
			{
				// obtenemos el nodo llget pasando el indice
				pAlumno= ll_get(listaAlumnos,bufferIndice);
				if(pAlumno != NULL)
				{
					//eliminamos alumno
					ll_remove(listaAlumnos,bufferIndice);
					retorno=1;
				}
			}
		}
	}

	return retorno;
}

int controladorInformes(LinkedList* listaAlumnos)
{
	int retorno=0;
	int opcion;

	if(listaAlumnos != NULL)
	{
		do
		{
			if(utn_getNumero(&opcion,"\n \n Ingrese lo que desea ver:\n 1-Lista completa de alumnos\n 2-Lista Personlizados\n 3-Lista Funcional\n 4-Lista Futbol\n 5-Lista crossfit\n 6-Volver al menu \n","\nError.\n",1,6,2)==0)
			{
				switch(opcion)
				{
				case 1 :
			//informe completo
					informeCompleto( listaAlumnos);

					break;
				case 2 :
					informePersonalizado( listaAlumnos);

					break;
				case 3 :
					informeFuncional( listaAlumnos);

					break;
				case 4 :
					informeFutbol( listaAlumnos);

					break;
				case 5 :
					informeCrossfit( listaAlumnos);

					break;
				}
			}
		}while(opcion != 6);
		//tamanio = ll_len(pArrayListPassenger);
	}
	return retorno;
}

int controladorEstadisticas(LinkedList* listaAlumnos)
{
	int retorno=0;
	int cantidadAlumnos;

	float auxAbono;
	float recaudacionTotal=0;

	char auxSexo;
	int contadorHombres=0;
	int contadorMujeres=0;
	int porcentajeHombres=0;
	int porcentajeMujeres=0;

	char descripcionActividad[LENNOMBRE];
	int contadorPerzonalisados=0;
	int contadorFuncional=0;
	int contadorFutbol=0;
	int contadorCrossfit=0;
//porcentaje de alumnos
	int porcentajePerzonalisados=0;
	int porcentajeFuncional=0;
	int porcentajeFutbol=0;
	int porcentajeCrosffit=0;
//porcentaje de abonos
	int porcentajeAbonosPerzonalisados=0;
	int porcentajeAbonosFuncional=0;
	int porcentajeAbonosFutbol=0;
	int porcentajeAbonosCrosffit=0;


	int recaudacionPersonalizados=0;
	int recaudacionFuncional=0;
	int recaudacionFutbol=0;
	int recaudacionCrossfit=0;

	eAlumnos*  pAlumno;

	if(listaAlumnos != NULL)
	{
		cantidadAlumnos=ll_len(listaAlumnos);
		for (int i = 0; i<cantidadAlumnos;i++ )
		{
			pAlumno = ll_get(listaAlumnos,i);
			if(pAlumno != NULL)
			{
				if
				(
					alumno_getAbono(pAlumno,&auxAbono)  &&
					alumno_getSexo(pAlumno,&auxSexo)  &&
					alumno_getActividad(pAlumno,descripcionActividad)

				)
				{

					recaudacionTotal=  auxAbono + recaudacionTotal;

					switch(auxSexo)
					{
						case 'm':
							contadorHombres++;

							break;

						case 'f':
							contadorMujeres++;
							break;
					}


					if(strcmp(descripcionActividad,"personalizado")==0)
					{
						contadorPerzonalisados++;
						 recaudacionPersonalizados= recaudacionPersonalizados+auxAbono;
					}
					else
					{
						if(strcmp(descripcionActividad,"funcional")==0)
						{
							contadorFuncional++;
							recaudacionFuncional=recaudacionFuncional+auxAbono;
						}
						else
						{
							if(strcmp(descripcionActividad,"futbol")==0)
							{
								contadorFutbol++;
								recaudacionFutbol=recaudacionFutbol+auxAbono;
							}
							else
							{
								 contadorCrossfit++;
								 recaudacionCrossfit=recaudacionCrossfit+auxAbono;
							}
						}
					}
				}
			}
		}

				printf("\n Cantidad de alumnos: %d",cantidadAlumnos);
				//recaudacion
				printf("\n Recaudacion total: %.2f",recaudacionTotal);
				printf("\n ");
				//hombres
				porcentajeHombres = (contadorHombres*100)/cantidadAlumnos;
				printf("\n**HOMBRES**");
				printf("\n Cantidad de hombres: %d			Porcentaje:%d",contadorHombres,porcentajeHombres);
				printf("\n ");
				//mujeres
				porcentajeMujeres = (contadorMujeres*100)/cantidadAlumnos;
				printf("\n**MUJERES**");
				printf("\n Cantidad de mujeres: %d			Porcentaje:%d",contadorMujeres,porcentajeMujeres);
				printf("\n ");


				//recaudaciones de actividades y porcentajes
				porcentajePerzonalisados = (contadorPerzonalisados*100)/cantidadAlumnos;
				porcentajeFuncional	= (contadorFuncional*100)/cantidadAlumnos;
				porcentajeFutbol =(contadorFutbol*100)/cantidadAlumnos;
			    porcentajeCrosffit	= (contadorCrossfit*100)/cantidadAlumnos;

			    porcentajeAbonosPerzonalisados= ( recaudacionPersonalizados*100)/recaudacionTotal;
			    porcentajeAbonosFuncional=( recaudacionFuncional*100)/recaudacionTotal;
			    porcentajeAbonosFutbol=(recaudacionFutbol*100)/recaudacionTotal;
			    porcentajeAbonosCrosffit=( recaudacionCrossfit*100)/recaudacionTotal;

				printf("\n**PERSONALIZADO**");
				printf("\n Cantidad Alumnos:%d			Porcentaje %d ",contadorPerzonalisados,porcentajePerzonalisados);
				printf("\n Recaudacion:%d			Porcentaje %d  ", recaudacionPersonalizados, porcentajeAbonosPerzonalisados);
				printf("\n ");

				printf("\n**FUNCIONAL**");
				printf("\n Cantidad Alumnos:%d			Porcentaje %d  ",contadorFuncional,porcentajeFuncional);
				printf("\n Recaudacion:%d				Porcentaje %d  ", recaudacionFuncional, porcentajeAbonosFuncional);
				printf("\n ");

				printf("\n**FUTBOL**");
				printf("\n Cantidad Alumnos:%d			Porcentaje %d  ",contadorFutbol, porcentajeFutbol);
				printf("\n Recaudacion:%d				Porcentaje %d  ", 	recaudacionFutbol,porcentajeAbonosFutbol);
				printf("\n ");

				printf("\n**CROSSFIT**");
				printf("\n Cantidad Alumnos:%d			Porcentaje %d  ",contadorCrossfit, porcentajeCrosffit);
				printf("\n Recaudacion:%d				Porcentaje %d  ",  porcentajeAbonosCrosffit,porcentajeAbonosCrosffit);
				printf("\n ");
				printf("\n ");

	}



	return retorno;
}
int controladrSalvar(LinkedList* listaAlumnos,char* path)
{
	int retorno = 0;
	int auxId;
	char auxNombre[LENNOMBRE];
	char auxApellido[LENNOMBRE];
	char sexo;
	char descripcionActividad[LENNOMBRE];
	float auxAbono;
	int auxHorarioClase;
	char auxFechaInicio[LENFECHAINICIO];
	char descripcionEstadoAbono[LENNOMBRE];

	eAlumnos*  pAlumno;
	FILE* pFile;

	if (path != NULL && listaAlumnos != NULL)
	{
		pFile = fopen("pAlumnos.csv","w");
		if(pFile == NULL)
		{
			printf("\nEl archivo no pudo abrirse.\n");
			system("pause");
			exit (EXIT_FAILURE);
		}
		for (int i = 0; i< ll_len(listaAlumnos);i++ )
		{
			pAlumno = ll_get(listaAlumnos,i);
			if (pAlumno != NULL &&
				alumno_getId(pAlumno,&auxId)  &&
				alumno_getNombre(pAlumno,auxNombre)  &&
				alumno_getApellido(pAlumno,auxApellido)  &&
				alumno_getSexo(pAlumno,&sexo)  &&
				alumno_getActividad(pAlumno,descripcionActividad)  &&
				alumno_getAbono(pAlumno,&auxAbono)  &&
				alumno_getHorarioClase(pAlumno,&auxHorarioClase)  &&
				alumno_getFechaInicio(pAlumno,auxFechaInicio)  &&
				alumno_getEstadoAbono(pAlumno,descripcionEstadoAbono)
				)
				{
				//ESCRIBO E ARCHIVO
				fprintf(pFile,"%d,%s,%s,%c,%s,%.2f,%d,%s,%s\n",auxId,auxNombre,auxApellido,
					sexo,descripcionActividad,auxAbono,auxHorarioClase,auxFechaInicio,descripcionEstadoAbono);
				retorno = 1;
			}
		}
	}
	fclose(pFile);
	return retorno;
}

int controller_idSubSiguiente (LinkedList* pArrayListaAlumnos)
{
	eAlumnos*  pAuxAlumnos =NULL;
	int siguienteId;
	int id;
	int tamanio;
	if ( pArrayListaAlumnos != NULL)
	{
		tamanio = ll_len( pArrayListaAlumnos);
		for(int i = 0;i<tamanio; i++)
		{
			 pAuxAlumnos = ll_get( pArrayListaAlumnos,i);

			if( pAuxAlumnos != NULL)
			{
				alumno_getId( pAuxAlumnos,&id);
				if(id > siguienteId || i == 0)
				{
					siguienteId = id;
				}
			}
		}
	}


	return siguienteId;
}

static int informeCompleto(LinkedList* listaAlumnos)
{
	int retorno=0;
	int limite;
	eAlumnos*  pAuxAlumno;

	if( listaAlumnos != NULL)
	{
		limite= ll_len(listaAlumnos);

		printf("\n*****************************************************************************************************************************************************");
		printf("\n ID		NOMBRE		APELLIDO	SEXO		ACTIVIDAD		ABONO		HORARIO		FECHA INICIO	ESTADO ABONO	");
		printf("\n*****************************************************************************************************************************************************");
		for(int i=0;i<limite;i++)
		{
			 pAuxAlumno = ll_get(listaAlumnos,i); //???
			 if( pAuxAlumno != NULL)
			 {
				 controlador_printAlumno( pAuxAlumno);
			 }

		}
		retorno =1;
	}

	return retorno;
}
static int informePersonalizado(LinkedList* listaAlumnos)
{
	int retorno=0;
	int limite;
	eAlumnos*  pAuxAlumno;

	if( listaAlumnos != NULL)
	{
		limite= ll_len(listaAlumnos);

		printf("\n 				  **LISTADO PERSONALIZADO** \n");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n ID	 	NOMBRE		 APELLIDO		HORARIO");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");

		for(int i=0;i<limite;i++)
		{
			 pAuxAlumno = ll_get(listaAlumnos,i); //???
			 if( pAuxAlumno != NULL &&  strcmp(pAuxAlumno->actividad,"personalizado")==0)
			 {
				 controlador_printEspecifico( pAuxAlumno);
			 }

		}
		retorno =1;
	}

	return retorno;
}
static int informeFuncional(LinkedList* listaAlumnos)
{
	int retorno=0;
	int limite;
	eAlumnos*  pAuxAlumno;

	if( listaAlumnos != NULL)
	{
		limite= ll_len(listaAlumnos);

		printf("\n 				  **LISTADO FUNCIONAL** \n");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n ID	 	NOMBRE		 APELLIDO		HORARIO");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");

		for(int i=0;i<limite;i++)
		{
			 pAuxAlumno = ll_get(listaAlumnos,i); //???
			 if( pAuxAlumno != NULL &&  strcmp(pAuxAlumno->actividad,"funcional")==0)
			 {
				 controlador_printEspecifico( pAuxAlumno);
			 }

		}
		retorno =1;
	}

	return retorno;
}
static int informeFutbol(LinkedList* listaAlumnos)
{
	int retorno=0;
	int limite;
	eAlumnos*  pAuxAlumno;

	if( listaAlumnos != NULL)
	{
		limite= ll_len(listaAlumnos);

		printf("\n 				  **LISTADO FUTBOL** \n");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n ID	 	NOMBRE		 APELLIDO		HORARIO");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");

		for(int i=0;i<limite;i++)
		{
			 pAuxAlumno = ll_get(listaAlumnos,i); //???
			 if( pAuxAlumno != NULL &&  strcmp(pAuxAlumno->actividad,"futbol")==0)
			 {
				 controlador_printEspecifico( pAuxAlumno);
			 }

		}
		retorno =1;
	}

	return retorno;
}
static int informeCrossfit(LinkedList* listaAlumnos)
{
	int retorno=0;
	int limite;
	eAlumnos*  pAuxAlumno;

	if( listaAlumnos != NULL)
	{
		limite= ll_len(listaAlumnos);

		printf("\n 				  **LISTADO CROSSFIT** \n");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n ID	 	NOMBRE		 APELLIDO		HORARIO");
		printf("\n --------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<limite;i++)
		{
			 pAuxAlumno = ll_get(listaAlumnos,i); //???
			 if( pAuxAlumno != NULL &&  strcmp(pAuxAlumno->actividad,"crossfit")==0)
			 {
				 controlador_printEspecifico( pAuxAlumno);
			 }

		}
		retorno =1;
	}

	return retorno;
}
static void  controlador_printAlumno(eAlumnos* pAlumno)
{
	int auxId;
	char auxNombre[LENNOMBRE];
	char auxApellido[LENNOMBRE];
	char descripcionSexo;
	//char descripcionSexo[LENNOMBRE];
	char descripcionActividad[LENNOMBRE];
	float auxAbono;
	int auxHorarioClase;
	char auxFechaInicio[LENFECHAINICIO];
	char descripcionEstadoAbono[LENNOMBRE];

	if(pAlumno != NULL)
	{
		if(
				alumno_getId(pAlumno,&auxId)  &&
				alumno_getNombre(pAlumno,auxNombre)  &&
				alumno_getApellido(pAlumno,auxApellido)  &&
				alumno_getSexo(pAlumno,&descripcionSexo)  &&
				alumno_getActividad(pAlumno,descripcionActividad)  &&
				alumno_getAbono(pAlumno,&auxAbono)  &&
				alumno_getHorarioClase(pAlumno,&auxHorarioClase)  &&
				alumno_getFechaInicio(pAlumno,auxFechaInicio)  &&
				alumno_getEstadoAbono(pAlumno,descripcionEstadoAbono)
			)
		{


			printf(" \n %d		%s		%s		%c		%s		%.2f		%d		%s	%s",
					auxId,auxNombre,auxApellido,descripcionSexo,descripcionActividad,auxAbono,auxHorarioClase,auxFechaInicio,descripcionEstadoAbono);
		}
	}
}
static void  controlador_printEspecifico(eAlumnos* pAlumno)
{
	int auxId;
	char auxNombre[LENNOMBRE];
	char auxApellido[LENNOMBRE];
	int auxHorarioClase;

	if(pAlumno != NULL)
	{
		if(
				alumno_getId(pAlumno,&auxId)  &&
				alumno_getNombre(pAlumno,auxNombre)  &&
				alumno_getApellido(pAlumno,auxApellido)  &&
				alumno_getHorarioClase(pAlumno,&auxHorarioClase)

			)
		{


			printf("\n %d		%s		%s			%d hs",
					auxId,auxNombre,auxApellido,auxHorarioClase);
		}
	}
}

int controller_findById(LinkedList* pArrayListPassenger,int idABuscar)
{
	eAlumnos* pAlumno=NULL;
	int bufferId;
	int tamanio;
	int retorno = 0;
	if (pArrayListPassenger != NULL && idABuscar>0)
	{
		tamanio = ll_len(pArrayListPassenger);
		for(int i = 0;i<tamanio; i++)
		{
			pAlumno= ll_get(pArrayListPassenger,i);
			if(pAlumno!= NULL)
			{
				alumno_getId(pAlumno,&bufferId);\
				if(idABuscar == bufferId )
				{
					retorno=i;
					break;
				}
			}

		}
	}
	return retorno;
}
int controlerResetearDatos(LinkedList* listaAlumnos)
{
	eAlumnos* pAlumno=NULL;
	int tamanio;
	int retorno = -1;
	char estadoAbono[LENNOMBRE];
	if (listaAlumnos != NULL )
	{
		strcpy(estadoAbono,"inactivo");
		tamanio = ll_len(listaAlumnos);
		retorno=1;
		for(int i = 0;i<tamanio; i++)
		{
			pAlumno= ll_get(listaAlumnos,i);
			if(pAlumno != NULL)
			{
				alumno_setEstadoAbono(pAlumno,estadoAbono);
			}
		}
	}
	return retorno;

}
