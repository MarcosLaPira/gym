/*
 ============================================================================
 Name        : GYM.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/*


opciones
1 iniciar programa
2 nuevo alumno
3 modificar alumno
4 baja de alumno
5  clases de hoy   informe de clase de las 5    informe de clase de las 6   informe de clase de las 7
6  informe estadisticas gym    recaudacion del mes    cantidadad de alumnos
7

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



int main(void)
{
	setbuf(stdout, NULL);

	int opcion;
	int flagGuardado=0;////////////////////////
	int flagInicio=0;//////////////////////////

	 LinkedList* listaAlumnos = ll_newLinkedList();
	 // creo menu siempre que opcion sea diferente a 8
	 printf("hola");
	 do
	 {
	//PIDO EL INGRESO DE OPCION
		 if(utn_getNumero(&opcion,"\nSeleccione una opcion:\n\n 1-Inicio del programa\n 2-Nuevo alumno\n 3-Modficar Alumno\n "
						"4-Baja de alumno\n 5-Informes de clases\n 6-Estadisticas\n 7-Resetear datos\n 8-Guardar datos modo texto\n 9-Salir \n ",
						"Opcion invalida\n",1,9,3)==0)
		 {
				//inicio del programa
			switch(opcion)
			{
				case 1:
					 if(controladorIniciarPrograma(listaAlumnos,"pAlumnos.csv"))
					 {
						 printf("\n ** archivo cargado con exito ** \n");
						 flagInicio=1;
					 }
					 else
					 {
						 printf("\n **  ERROR, el archivo no pudo ser cargado ** \n");
					 }

					 break;
				// nuevo almuno
				case 2:
					if(flagInicio==1)
					{
						 if(controladorAgregarAlumno(listaAlumnos))
						 {
							 printf("\n ** alumno agregado con exito ** \n");
						 }
						 else
						 {
							 printf("\n **ERROR al agregar alumno ** \n");
						 }
					}
					else
					{
						printf("\n **ERROR el programa no fue iniciado ** \n");
					}
					 break;
				//modificaar alumno
				case 3:
					if(flagInicio==1)
					{
						controladorModificarAlumno(listaAlumnos);

					}
					else
					{
						printf("\n **ERROR el programa no fue iniciado ** \n");
					}
								 break;

				// baja de alumno
				case 4:
					if(flagInicio==1)
					{
						if(controladorBajaDeAlumno(listaAlumnos))
						{
							 printf("\n ** alumno eliminado con exito ** \n");
						}
						else
						{
							printf("\n **ERROR al eliminar alumno ** \n");
						}
					}
					else
					{
						printf("\n **ERROR el programa no fue iniciado ** \n");
					}
					 break;
				// int

				// informe
				case 5:
					if(flagInicio==1)
					{
						controladorInformes( listaAlumnos);
					}
					else
					{
						printf("\n **ERROR el programa no fue iniciado ** \n");
					}
					break;
				case 6:
					if(flagInicio==1)
					{
						controladorEstadisticas( listaAlumnos);
					}
					else
					{
						printf("\n **ERROR el programa no fue iniciado ** \n");
					}
					break;

				case 7:

					if(controlerResetearDatos( listaAlumnos))
					{
						printf("\n Estados de abono reseteados con exito \n ");
					}
					else
					{
						printf("\n ERROR al resetear estados \n ");
					}
					break;
					//guardar datos
				case 8:
					if(flagInicio==1)
					{
						if(controladrSalvar(listaAlumnos,"pAlumnos.csv"))
						{
							printf("exito en el guardado");
							flagGuardado=1;
						}
					}
					else
					{
						printf("\n **ERROR el programa no fue iniciado ** \n");
					}

					 break;
				// int controladrSalvar(LinkedList* listaAlumnos);

			 }
	 	 }

		 if(opcion == 9 && flagGuardado ==0)
		 {
				printf("\n **ERROR para finalizar el programa primero debe de guardar ** \n");
		 }

	 }while(  opcion != 9 && flagGuardado !=1 );

	return EXIT_SUCCESS;
}
