/*
 * laibrery.c
 *
 *  Created on: 11 may. 2022
 *      Author: lapir
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "laibrery.h"



 static	int getNombre (char pResultado[], int tamanio);
 static	int esNombre (char array [], int tamanio);


 static int getInt(int* pResultado);
 static int esNumerica (char* cadena, int tamanio);

 static int getFloat(float* pResultado);
 static int esFlotante(char* cadena,int limite);



	//  recibe el tamanio y la cadena y nos dice  si es disponible del buffer esta ok (no lo desborda)
	// lee tod0 hasta un \0 o hasta que llegue al limite

	int myGets(char* cadena, int tamanio)
	{ // NOMBRE

		int retorno = -1;
		char bufferString [4096];//**********************************************

		if (cadena != NULL && tamanio >0 ){

			fflush(stdin);
			if(fgets(bufferString,sizeof (bufferString),stdin) != NULL){

				if (bufferString [strnlen (bufferString,sizeof (bufferString) )-1] == '\n'){

					bufferString [strnlen (bufferString, sizeof (bufferString))-1] = '\0';
				}
				if (strnlen (bufferString, sizeof (bufferString)) <= tamanio){

					strncpy (cadena,bufferString, tamanio);
					retorno = 0;
				}
			}
		}

		return retorno;
	}


	/**
	 * \brief Solicita una palabra al usuario, luego de verificarlo devuelve el resultado
	 * \param array Es el puntero al espacio de memoria donde se dejara el resultado de la funcion
	 * \param mensaje Es el mensaje que pide el dato
	 * \param mensajeError Es el mensaje de Error
	 * \param minimo Es el numero maximo aceptado
	 * \param maximo Es el minimo minimo aceptado
	 * \return Retorna 0 si fue EXITOSA  o -1 en caso de ERROR
	 *
	 */
	int utn_getNombre(char array[], int tamanio, char* mensaje, char* mensajeError, int reintentos )
	{
		int retorno = -1;
		char buffer [tamanio];

		if (array != NULL && tamanio >0 &&  mensaje != NULL &&  mensajeError != NULL && reintentos>= 0){

			do{
				printf ("%s", mensaje);
				if (getNombre(buffer, tamanio) == 0){

					retorno = 0;
					strcpy(array,buffer);

					break;

					}
				else{
					printf ("%s", mensajeError);
					reintentos --;
				}

				}while(reintentos >= 0);

		}

		return retorno;
	}
	/**
	 * \brief Verifica si la cadena ingresada es de caracteres
	 *\param array Array de  a ser validado
	 *\param tamanio limite del array
	 * \return Retorna 1 (EXITO) si son todos son caracteres , 0 en el caso de ERROR y -1 si no se cumple la funcion
	 */
static	int esNombre (char array [], int tamanio)
	{
		int retorno = -1;
		int i;

		if (array != NULL && tamanio > 0){

			for(i=0;i<tamanio && array[i] != '\0';i++)
			{

				array [i] = tolower (array [i]); // pasa el array a minusculas

				retorno = 1;

				if (array [i] < 'a' || array [i] > 'z'){

					retorno = 0; // ERROR
					break;
				} // FIN DEL IF
			} // FIN DEL FOR
		} // FIN VALIDACION

		return retorno;
	}

	/**
	 * \brief  Obtiene un array de caracteres validado
	 *\param array Array de  a ser validado
	 *\param tamanio limite del array
	 * \return Retorna 0 (EXITO) si logro convertirlo a caracteres y -1 (ERROR)
	 */

 static	int getNombre (char pResultado[], int tamanio)
	{
		int retorno = -1;
		char buffer[tamanio];

		if (pResultado != NULL && myGets(buffer, sizeof(buffer)) == 0
				&& esNombre(buffer,sizeof(buffer))>0) // osea si se cumple la fx y me devuelve un verdadero
				{
					strcpy(pResultado,buffer);
					retorno = 0;
				}
		return retorno;
	}

 int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
   {
   	int bufferInt;
   	int retorno = -1;

   	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0) //validacion de parametros
   	{
   		do{
   			printf("%s", mensaje); // cualquier tipo de string en el msj

   			if (getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
   			{
   				*pResultado = bufferInt;
   				retorno = 0;
   				break;
   			}
   			else
   			{
   				printf("%s", mensajeError);
   				reintentos --;
   			}
   		}while(reintentos >= 0 );

   	}

   	return retorno;
   }



 // recibe un espacio de memoriua y devuelve un numero entero Lee lo que el usuario entrega por teclado y valida que eso sea
 // un numero llama a mygets para obtener el texto y despues lo valida con es Numero REEMPLAZA AL SCANF %d

 static int getInt(int* pResultado) // numero entero
 {
 	int retorno = -1;
 	char buffer [4096];
 	fflush(stdin);

 	if (pResultado != NULL){
 		if (myGets(buffer, sizeof(buffer)) == 0 && (esNumerica(buffer,sizeof(buffer)))) // osea si se cumple la fx y me devuelve un verdadero
 		{
 			*pResultado = atoi (buffer);
 			retorno = 0;
 		}
 	}

 	return retorno;
 }


 static int esNumerica (char* cadena, int tamanio)
 {
 	int retorno = -1; // ERROR
 	int i;
 	if (cadena != NULL && tamanio > 0){

 		retorno = 1; // VERDADERO
 		for ( i = 0 ; i < tamanio && cadena [i] != '\0' ; i++) // el primer argumento esta vacio porque no sabemos que informacion viene en la cadena de arrays
 		{
 			if (i == 0 && (cadena [i] == '-' || cadena [i] == '+'))
 			{
 				continue;

 			}
 			if (cadena [i] > '9' || cadena [i] < '0')
 			{
 				retorno = 0;
 				break;
 			}
 		}
 	}

 	return retorno;
 }

 int getNumeroFlotante(float* pResultado, char mensaje[], char errorMensaje[], float minimo, float maximo, int reintentos)
 {
	 int retorno = -1;
	 	float bufferFloat;

	 	do{
	 		printf("%s",mensaje);

	 		if(getFloat(&bufferFloat)==0&&
	 		   bufferFloat >= minimo &&
	 		   bufferFloat <= maximo)
	 		{
	 			retorno = 0;
	 			*pResultado=bufferFloat;
	 			break;
	 		}
	 		printf("%s",  errorMensaje);
	 		reintentos--;
	 	}while(reintentos>=0);


	 	return retorno;
 }



 /**
  * \brief Verifica si la cadena ingresada es flotante
  * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
  * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
  *
  */
 static int getFloat(float* pResultado)
 {
     int retorno=-1;
     char bufferString[50];

    if(pResultado != NULL &&
 	myGets(bufferString,sizeof(bufferString)) == 0 &&
 	esFlotante(bufferString,sizeof(bufferString)))
    {
 	retorno=0;
 	*pResultado = atof(bufferString) ;
    }

 	return retorno;

 }

 /**
  * \brief Verifica si la cadena ingresada es flotante
  * \param cadena Cadena de caracteres a ser analizada
  * \return Retorna 1 (vardadero) si la cadena es flotante y 0 (falso) si no lo es
  *
  */

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


 int getAlfanumerico(char* inPut,char mensaje[], char errorMensaje[],int tamano, int reintentos)
 {
 	//decalro variables
 	char bufferChar[tamano];
 	int retorno;


 //valido
 	if(inPut != NULL && mensaje != NULL && errorMensaje != NULL && tamano >= 1 && reintentos >= 0 )
 	{
 												//creo bucle que se repita si reintentos>= 0 y retorno ==0
 		do{
 			 retorno = 0;
 //pido el ingreso de datos
 			 printf("\n %s",mensaje);
 			 fflush(stdin);
 		 	 gets(bufferChar);
 		 	 	 	 	 	 	 	 	 	 	 	 	 // printf("%d",strlen(bufferChar));
 //valido que lo ingresado no exceda
 			 if(strlen(bufferChar)<=tamano)
 			 {
 //recorro arrray

 				 for(int i=0;i<strlen(bufferChar);i++) //while(i<=strlen(bufferChar))
 				 {
 //niego alfanumerico

 					if(!isalnum(bufferChar[i]))
 					{
 						printf("\n %s",errorMensaje);
 						retorno = -1;
 						break;
 					}
 				 }
 				// printf("su contrsena es %s",bufferChar);
 			 }
 			 else
 			 {
 				 retorno=-1;
 			 }

 			 reintentos--;
 		 }while(reintentos>=0 && retorno==-1);

 		 if(retorno==0)
 		 {
 			 strcpy(inPut,bufferChar);
 			//inPut = bufferChar;
 		 }

 	 }
 	return	retorno;
 }


 int getCadenaTelefonica(char inPut[],char mensaje[], char errorMensaje[],int tamano, int reintentos)
 {
 	//decalro variables
 	char bufferChar[tamano];
 	int retorno;


 //valido
 	if(inPut != NULL && mensaje != NULL && errorMensaje != NULL && tamano >= 1 && reintentos >= 0 )
 	{
 												//creo bucle que se repita si reintentos>= 0 y retorno ==0
 		do{
 			 retorno = 1;
 //pido el ingreso de datos
 			 printf("\n %s",mensaje);
 			 fflush(stdin);
 		 	 gets(bufferChar);
 		 	 	 	 	 	 	 	 	 	 	 	 	 // printf("%d",strlen(bufferChar));
 //valido que lo ingresado no exceda
 			 if(strlen(bufferChar)<=tamano && sizeof(bufferChar)>=8)
 			 {
 //recorro arrray

 				 for(int i=0;i<strlen(bufferChar);i++) //while(i<=strlen(bufferChar))
 				 {
 //niego alfanumerico
 					 if(i==4)
 					 {
 						 bufferChar[i]='-';
 						 continue;
 					 }
 					if(!isalnum(bufferChar[i]))
 					{
 						printf("\n %s",errorMensaje);
 						retorno = 0;
 						break;
 					}
 				 }
 				// printf("su contrsena es %s",bufferChar);
 			 }
 			 else
 			 {
 				 retorno=0;
 			 }

 			 reintentos--;
 		 }while(reintentos>=0 && retorno==0);

 		 if(retorno==1)
 		 {

 			 strncpy(inPut,bufferChar,sizeof(bufferChar));
 			//inPut = bufferChar;
 		 }

 	 }
 	return	retorno;
 }
 int esLetraConEspacio(char inPut[],char mensaje[], char errorMensaje[],int tamano, int reintentos)
 {
 	//decalro variables
 	char bufferChar[tamano];
 	int retorno;


 //valido
 	if(inPut != NULL && mensaje != NULL && errorMensaje != NULL && tamano >= 1 && reintentos >= 0 )
 	{
 												//creo bucle que se repita si reintentos>= 0 y retorno ==0
 		do{
 			 retorno = 1;
 //pido el ingreso de datos
 			 printf("\n %s",mensaje);
 			 fflush(stdin);
 		 	 gets(bufferChar);
 		 	 	 	 	 	 	 	 	 	 	 	 	 // printf("%d",strlen(bufferChar));
 //valido que lo ingresado no exceda
 			 if(strlen(bufferChar)<=tamano )
 			 {
 //recorro arrrayC

 				 for(int i=0; i<strlen(bufferChar);i++) //while(i<=strlen(bufferChar))
 				 {
 //niego cadena y espacio

 					if(!isalpha(bufferChar[i]) && !isspace(bufferChar[i]))
 					{
 						printf("\n %s",errorMensaje);
 						retorno = 0;
 						break;
 					}
 				 }
 				// printf("su contrsena es %s",bufferChar);
 			 }
 			 else
 			 {
 				 printf("\n %s",errorMensaje);
 				 retorno=0;
 			 }

 			 reintentos--;
 		 }while(reintentos>=0 && retorno==0);

 		 if(retorno==1)
 		 {
 			 strncpy(inPut,bufferChar,strlen(bufferChar));
 			//inPut = bufferChar;
 		 }

 	 }
 	return	retorno;
 }
 int esSoloLetra(char inPut[],char mensaje[], char errorMensaje[],int tamano, int reintentos)
 {
 	//decalro variables
 	char bufferChar[tamano];
 	int retorno;


 //valido
 	if(inPut != NULL && mensaje != NULL && errorMensaje != NULL && tamano >= 1 && reintentos >= 0 )
 	{
 												//creo bucle que se repita si reintentos>= 0 y retorno ==0
 		do{
 			 retorno = 1;
 //pido el ingreso de datos
 			 printf("\n %s",mensaje);
 			 fflush(stdin);
 		 	 gets(bufferChar);
 		 	 	 	 	 	 	 	 	 	 	 	 	 // printf("%d",strlen(bufferChar));
 //valido que lo ingresado no exceda
 			 if(strlen(bufferChar)<=tamano )
 			 {
 //recorro arrrayC

 				 for(int i=0; i<strlen(bufferChar);i++) //while(i<=strlen(bufferChar))
 				 {
 //niego cadena y espacio

 					if(!isalpha(bufferChar[i]))
 					{
 						printf("\n %s",errorMensaje);
 						retorno = 0;
 						break;
 					}
 				 }
 				// printf("su contrsena es %s",bufferChar);
 			 }
 			 else
 			 {
 				 printf("\n %s",errorMensaje);
 				 retorno=0;
 			 }

 			 reintentos--;
 		 }while(reintentos>=0 && retorno==0);

 		 if(retorno==1)
 		 {
 			 strcpy(inPut,bufferChar);
 			 //strncpy(inPut,bufferChar,strlen(bufferChar));
 			//inPut = bufferChar;
 		 }

 	 }
 	return	retorno;
 }





 int getFechaInicio(char* inPut,char mensaje[], char errorMensaje[],int tamano, int reintentos)
  {
  	//decalro variables
  	char bufferChar[tamano];
  	int retorno;


  //valido
  	if(inPut != NULL && mensaje != NULL && errorMensaje != NULL && tamano >= 1 && reintentos >= 0 )
  	{
  												//creo bucle que se repita si reintentos>= 0 y retorno ==0
  		do{
  			 retorno = 0;
  //pido el ingreso de datos
  			 printf("\n %s",mensaje);
  			 fflush(stdin);
  		 	 gets(bufferChar);
  		 	 	 	 	 	 	 	 	 	 	 	 	 // printf("%d",strlen(bufferChar));
  //valido que lo ingresado no exceda
  			 if(strlen(bufferChar)<=tamano)
  			 {
  //recorro arrray

  				 for(int i=0;i<strlen(bufferChar);i++) //while(i<=strlen(bufferChar))
  				 {
  //niego alfanumerico
  					 if(bufferChar[i]=='/')
  					 {
  						 continue;
  					 }

  					if(!isdigit(bufferChar[i]))
  					{
  						printf("\n %s",errorMensaje);
  						retorno = -1;
  						break;
  					}
  				 }
  				// printf("su contrsena es %s",bufferChar);
  			 }
  			 else
  			 {
  				 retorno=-1;
  			 }

  			 reintentos--;
  		 }while(reintentos>=0 && retorno==-1);

  		 if(retorno==0)
  		 {
  			 strcpy(inPut,bufferChar);
  			//inPut = bufferChar;
  		 }

  	 }
  	return	retorno;
  }

