/*
 * linkedList.c
 *
 *  Created on: 23 jun. 2022
 *      Author: lapir
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;


    this = (LinkedList*)malloc(sizeof(LinkedList));

    if (this != NULL)
    {
		this->pFirstNode = NULL;
		this->size = 0;
    }
    return this;
}
//llen: tamaño de la linkedlist.

int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if (this!= NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}

//getNode: retorna el puntero al nodo

static Node* getNode(LinkedList* this, int nodeIndex)// 1ro valida ll y que el indice este dentro del tamño del size de LL (mayor a -1 porque menor al tamaño total xq las posiciones empiezan en 0)
{
	Node* pNode = NULL;
	if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
	{
			pNode = this ->pFirstNode; // en el caso de que sea 0 pNode esta en el primer lugar

			for (int i = 0;i<nodeIndex; i++) // menor al indice del nodo para que la recorra la menor distancia posible
			{
				pNode = pNode ->pNextNode; // una vez que recorre hasta el lugar donde se encuentra la posicion nodeIndex asigna la direcciuon del siguiente nodo
			}
	}
    return pNode; // retorna el nodo
}

Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);

}
//ll add: añade un nodo al final de la linkedlist


static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int returnAux = -1;
	Node* NewNode = NULL; // declaro variabvle del tipo node
	Node* prevNode = NULL;// declaro variabvle del tipo node

	if (this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this)) // valido
	{
		NewNode = (Node*)malloc(sizeof(Node)); // busco espacio en memoria para el nuevo nodo
		if(NewNode != NULL)
		{
			NewNode->pElement = pElement; // inicializo los campos del nuevo nodo
			NewNode->pNextNode = NULL; // inicializo los campos del nuevo nodo

			if (nodeIndex == 0) // si el indice es = 0 es porque ocupa el primer lugar de mi LL
			{
				NewNode->pNextNode = this->pFirstNode; // mi nuevo nodo apunta al mismo primer nodo que mi LL
				this->pFirstNode = NewNode; // mi LL apunta a la direccion del nuevo nodo y este apunta al que fue mi primer nodo antes de incrementar el size
			}
			else
			{
				prevNode = getNode(this,nodeIndex-1); // a mi segunda variable tipo node le asigno
				NewNode->pNextNode = prevNode->pNextNode;
				prevNode->pNextNode = NewNode;
			}
			this->size++;
			returnAux = 0;
		}
	}

	return returnAux;
}


int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

//llen: tamaño de la linkedlist.

int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL)
	{
		returnAux = addNode(this, ll_len(this), pElement);
	}
    return returnAux;
}
//llget: retorna un elemento

void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode = NULL;
    //busca con getNode y retorna su pElement
    if (this != NULL && index <= ll_len(this) && index >= 0)
    {
    	pNode = getNode(this, index);
    	if (pNode != NULL)
    	{
    		returnAux  = pNode-> pElement;
    	}
    }
    return returnAux;
}

//llSet: modifica el elemento de un nodo existente


int ll_set(LinkedList* this, int index,void* pElement) // BORRAR un Nodo PISA EL NODO
{
    int returnAux = -1;
    Node* pNode = NULL;

    if (this != NULL && index < ll_len(this) && index >= 0)
    {
    	pNode = getNode(this, index);
    	if(pNode != NULL)
    	{
    		pNode->pElement = pElement;
    		returnAux = 0;
    	}
    }

    return returnAux;
}

//llRemove: elimina un nodo de la lista

int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNodePrevio = NULL;
    Node* auxNode = NULL;

    if (this != NULL && index < ll_len(this) && index >= 0)
       {

    		auxNode  = getNode(this, index);   //nodo que se desa eliminar
			if (index == 0)
			{
				this ->pFirstNode = auxNode ->pNextNode;
			}
			else
			{
				pNodePrevio = getNode(this, index-1);
				if (pNodePrevio != NULL)
					{
						pNodePrevio ->pNextNode = auxNode ->pNextNode;
					}
			}
			free(auxNode);
			this->size--;
			returnAux = 0;
       	}
    return returnAux;
}

//llclear: elimina todos los nodos de la linkedlist

int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i ;
    if (this != NULL)
    {
    	for (i = ll_len(this)-1; i >= 0 ; i--) // borra los datos de atas para adelante para no perder las referencias
    	{
    		ll_remove(this, i);
    	}
    	returnAux = 0;
    }
    return returnAux;
}


int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL && !ll_clear(this)) //
    {
    	free (this);
    	returnAux = 0;
    }
    return returnAux;
}

//llIndexOf: busca el primer nodo

int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* pElementAux;
    if (this != NULL) //
 	{
		for (int i = 0; i < ll_len(this); i++) // como el indice empieza en 0 y la ll tiene 1 elemento pero la posicion es 0 entonces siempre va a ser uno menor
		{
			pElementAux =  ll_get(this, i); // va guardando en la variable aux cada uno de los elementos de la LL que me trae la fx ll_get y lo compara con el puntero Element recibido

			if (pElement == pElementAux) // una vez que encuantra el elemento retorna el indice del misimo
			{
				returnAux = i;
				break;
			}
		}
    }
	return returnAux;
}


int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
    	if(ll_len(this))
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }
    return returnAux;
}
//llPush: incerta un nuevo nodo entre medio de dos

int ll_push(LinkedList* this, int index, void* pElement) //dezslaza el nodo  e inserta un nuevo nodo para poner el un nuevo nuevo elemento
{
    int returnAux = -1;

	if (this != NULL && index >= 0 && index <= ll_len(this))
	{
		returnAux = addNode(this,index,pElement);
	}
    return returnAux;
}

//pop: muestra el nodo y luego lo elimina

void* ll_pop(LinkedList* this,int index)
{
	void* returnAux = NULL;

 	if(this != NULL && index>= 0 && index <ll_len(this))// tiene que ser menor porque tengo que eliminar y no agregar busco uno existente
    {
 		returnAux = ll_get(this, index);// devuelve el elemento que esta guardado en el nodo del indice envidado a la fx
 		ll_remove(this, index); // remueve el nodo y enlaza el anterior y posterior para que sean consecutivos
    }
    return returnAux;
}

//llContein: avisa si existe o no un determinado elemento

int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
	{
		if( ll_indexOf(this, pElement) != -1)
		{
			 returnAux = 1;
		}
		else
		{
			 returnAux = 0;
		}
	}
    return returnAux;
}

//avisa si lo que esta contenido en una lista,se encuentra en la otra.

int ll_containsAll(LinkedList* this,LinkedList* this2)// compara si todos los elementos de la LL this2 estan en LL this
{
    int returnAux = -1; // ERROR O NULL
    void* pElementAux = NULL;

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 1;
    	for(int i = 0; i<ll_len(this2);i++) // menor si o si porque lo estoy agregando
    	{
    		pElementAux = ll_get(this2,i);// retorno el elemento contenido en this2

    		if(!(ll_contains(this,pElementAux))) // verifico si pElementaux o this2 esta contenido en this o en la LL
    		{
    			returnAux = 0;
    			break; // brekea cuando ningun elemento del 2 esta contenido en 1
    		}
    	}
    }
    return returnAux;
}


LinkedList* ll_subList(LinkedList* this,int from,int to) // copia la lista desde un rango hasta otro excluido
{
    LinkedList* cloneArray = NULL;
    void* pElementAux = NULL;

    if (this != NULL && to <= ll_len(this) && from >=  0 && to > from)
    {
    	cloneArray = ll_newLinkedList();

    	if(cloneArray != NULL)
    	{
    		for(int i=from; i <to ;i++)
    		{
    			pElementAux = ll_get(this,i);
    			ll_add(cloneArray,pElementAux);
    		}
    	}
    }
    return cloneArray;
}


//copia una lista entera , crea y retorna una nueva lista con los elementos de la lista pasada como parametro

LinkedList* ll_clone(LinkedList* this) // clona la lista
{
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
    	cloneArray = ll_subList(this,0,ll_len(this));// no lo hace desde el NEWLL porque invoca a ala fx sublist que es quein lo crea
    }
    return cloneArray;
}
// Ordena los elementos del arrray


int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)// la funcion es la que sabe que tiene que comprar
{
    int returnAux =-1;
    int i;
    int j;
    void* elemento1;
    void* elemento2;
    int len;

    if(this != NULL && pFunc != NULL && order >= 0 && order <= 1 )
    {
    	returnAux = 0;
    	len = ll_len(this);

		for(i= 0;i<len-1;i++)
		{
			for(j =i+1;j<len;j++)
			{
				elemento1 = ll_get(this,i);
				elemento2 = ll_get(this,j);

				if( (pFunc(elemento1,elemento2)>0 && order == 1) || (pFunc(elemento1,elemento2)<0 && order == 0) )
				{
					ll_set(this, i, elemento2);
					ll_set(this, j, elemento1);
				}
			}
		}
    }
    return returnAux;
}
//completa un camo el elemnto
//
void ll_map(LinkedList* this, void (*fn)(void* pElement))
{
	//LinkedList* retorno;
	if(this != NULL && fn != NULL)
	{
		for(int i = 0; i<ll_len(this);i++)//tama;o
		{
			fn(ll_get(this,i));//obtiene puntero que es llamado por calcular
		}
	}
//	return retorno;

}

LinkedList* ll_filter(LinkedList* this, int(*fn)(void*))
{
	LinkedList* listaFiltrada = NULL;
	void* elemento;
	if(this != NULL && fn != NULL)
	{
		listaFiltrada = ll_newLinkedList();//inicializa nueva linkeist

		if(listaFiltrada != NULL)
		{
			for(int i = 0; i<ll_len(this);i++)//obtengo tamano
			{
				elemento = ll_get(this,i);//obtengo puntero a elemento

				if (fn(elemento)>0)
				{
					ll_add(listaFiltrada,elemento);//anado nodo al final de la linkelist nueva
				}
			}
		}
	}
	return listaFiltrada;
}
