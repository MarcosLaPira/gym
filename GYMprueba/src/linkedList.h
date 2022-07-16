/*
 * linkedList.h
 *
 *  Created on: 23 jun. 2022
 *      Author: lapir
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct Node
{
    void* pElement;                 //puntero al elemento (persona, empleado, etc.)
    struct Node* pNextNode;         //puntero al prox nodo
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;
    int size;                       //cada vez que agrego o elimino un elemento size++/--
}typedef LinkedList;
#endif



//Publicas

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void); // es el constructor que pide un lugar en memoria y despues lo inicializa
int ll_len(LinkedList* this);//devuelve el valor del campo int size de la LL
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex,void* pElement);
int ll_add(LinkedList* this, void* pElement); // agranda el tamaño de la linkedList agregando un nuevo nodo y asignandole al mismo un nuevo elemento
void* ll_get(LinkedList* this, int index); // Retorna el Elemento buscando el nodo correspondiente (get node) y devuelvo el elemento asignado al nodo ->pElement
int ll_set(LinkedList* this, int index,void* pElement);// PISA el elemento, busca el nodo con la fx get node en el indice que le paso y me devuelve el nodo que quiero pisar con el elemento que le envio a la fx
int ll_remove(LinkedList* this,int index);// remueve un nodo, para eso declara un nodo auxiliar donde guarda con getnode el nodo que quiere remover, si el indezx es = 0 va a guardar en el firstnode LL la direccion de memoria del siguiente nodo al que quiero borrar osea va a guardar la direccion del nodo 2 que pasaria a ser el 1, en el caso de que sea cualquier otro nodo != 0 guardo en un aux el nodo previo para acceder al campo nextnodo y guardo en este la direccion de memeoria  nextnode del que quiero borrar , de esta forma desato el nodo que quiero remover de la LL y engancho al nodo previo la dir del nodo siguiente
int ll_clear(LinkedList* this);// remueve todos los nodos de la LL , Recorre la LL con un for de atras para adelante (osea decrementando el indice) (para no perder la referencia en caso de borrar) una vez que encuentra el indice del que quiere borrar y llama a la fx remove indicandole cada indice a remover
int ll_deleteLinkedList(LinkedList* this);// Elimina toda la LL, primero valida los datos y una vez que clear devuelve 0 (osea que limpio la ll) aplicamos la fx free para desadjudicar los espacios en memoria y liberarlos
int ll_indexOf(LinkedList* this, void* pElement); // utiliza la funcion getnode para traer cada uno de los elementos de la LL guardandolos en una variable aux y esta la compara con el pElemnt recibuido y una vez que encuentra el elemento que es igual al que nos llega por parametro brekea el for y retorna el indice de este.
int ll_isEmpty(LinkedList* this);// Indica si la lista esta vacia (retorna 1) o no esta vacia (retorna 0), con el ll_len verifica si el size es mayor a 0 (tiene nodos/elementos) o si esta vacia
int ll_push(LinkedList* this, int index, void* pElement); // desplaza el nodo que se encuentra en la posicion que queremos insertar, dezplazando este hacia adelante y agrega un nuevo nodo en su lugar utilizando la funcion addNode e inserta el elemento en la posicion LL designada en el indice de la funcion
void* ll_pop(LinkedList* this,int index); //elimina un elemento de la posicion indicada, (llama al ll get que devuelve el elemento que esta guardado en el nodo del indice envidado a esa fx), DESPUES (llama al llremove para remover el nodo) y devuelve un puntero a ese elemento
int ll_contains(LinkedList* this, void* pElement);//Determina si la lista contiene o no el elemento pasado como parametro utilizando la fx indexof para que busqie el indice de dicho elemento, en el caso de encontrarlo retorna el indice si lo encuentra y un 0 (FALSO) si no lo encuentra
int ll_containsAll(LinkedList* this,LinkedList* this2);//compara si todos los elementos de la LL this2 estan en LL this, utiliza ll GET para que retorne el elemento contenido en this2, despues verifica con llContains // verifico si pElementaux o this2 esta contenido en this o en la LL. retorna Verdadero si lo contiene, falso o 0 si no y -1 en el caso de NULL o ERROR
LinkedList* ll_subList(LinkedList* this,int from,int to);
LinkedList* ll_clone(LinkedList* this);
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
//LinkedList* ll_map(LinkedList* this, void (*fn)(void* pElement));
void ll_map(LinkedList* this, void (*fn)(void* pElement));
LinkedList* ll_filter(LinkedList* this, int(*fn)(void*));




