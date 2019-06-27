#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    Node* pNodeaux= NULL;
    int i;
    if(this != NULL && nodeIndex >= 0 && nodeIndex< ll_len(this) )
    {
        pNodeaux = this->pFirstNode;
        if (nodeIndex == 0)
        {
            pNode = pNodeaux;
        }else
        {
            for(i=0;i<=nodeIndex;i++)
            {
                if(i != nodeIndex)
                {
                    pNodeaux = pNodeaux->pNextNode;
                }else
                {
                   pNode = pNodeaux;
                }
            }
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNodeAux= NULL;
    Node* pNodeAux2= NULL;
    int i;
    int size =ll_len(this);
    if(this != NULL && nodeIndex >= 0 && nodeIndex<=size)
    {
        if (nodeIndex==0)
        {
            pNodeAux = malloc(sizeof(Node));
            if(pNodeAux != NULL)
            {
                pNodeAux->pNextNode = this->pFirstNode;
                pNodeAux->pElement =pElement;
                this->pFirstNode=pNodeAux;
                this->size++;
                returnAux=0;
            }
        }else if(nodeIndex==size)
        {
           pNodeAux=this->pFirstNode;
           for(i=0;i<nodeIndex;i++)
           {
                if(i<nodeIndex-1)
                    pNodeAux=pNodeAux->pNextNode;
           }
           pNodeAux2= malloc(sizeof(Node));
           if(pNodeAux2 != NULL)
           {
                pNodeAux->pNextNode=pNodeAux2;
                pNodeAux2->pNextNode= NULL;
                pNodeAux2->pElement=pElement;
                this->size++;
                returnAux=0;
           }
        }else
        {
            pNodeAux=this->pFirstNode;
            for(i=0;i<=nodeIndex;i++)
            {
                pNodeAux=pNodeAux->pNextNode;
            }
            pNodeAux2= malloc(sizeof(Node));
            if(pNodeAux2 != NULL)
            {
                pNodeAux2->pNextNode=pNodeAux->pNextNode;
                pNodeAux->pNextNode=pNodeAux2;
                pNodeAux2->pElement=pElement;
                this->size++;
                returnAux=0;
            }
        }
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    if(this != NULL)
    {
        i=addNode(this,ll_len(this),pElement);
        if (i == 0)
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{

    void* returnAux = NULL;
    Node* pNodeAux= NULL;
    int size=ll_len(this);
    if(this != NULL && index >=0 && index<=size)
    {
        pNodeAux=getNode(this,index);
        if(pNodeAux !=NULL)
        {
            returnAux=pNodeAux->pElement;
        }
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNodeAux= NULL;
    int size=ll_len(this);
    if(this != NULL && index >=0 && index<size)
    {
        pNodeAux=getNode(this,index);
        if(pNodeAux != NULL)
        {
            pNodeAux->pElement=pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNodeAux = NULL;
    Node* pNodeAux2 = NULL;
    int size=ll_len(this);
    if(this != NULL && index >=0 && index<size)
    {
        if(index == 0)
        {
            pNodeAux=this->pFirstNode;
            this->pFirstNode=pNodeAux->pNextNode;
            free(pNodeAux);
            this->size--;
        }else if(index==size)
        {
            pNodeAux=getNode(this,index);
            free(pNodeAux);
            this->size--;
        }else
        {
            pNodeAux=getNode(this,index-1);
            pNodeAux2=pNodeAux->pNextNode;
            pNodeAux->pNextNode=pNodeAux2->pNextNode;
            free(pNodeAux2);
            this->size--;
        }
        returnAux =0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int size=ll_len(this);
    int i;

    if(this != NULL)
    {

        for(i=0;i<size;i++)
        {
         ll_remove(this,i);
        }
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    int i;
    if(this != NULL)
    {
        i=ll_clear(this);
        if(i==0)
        {
            free(this);
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNodeAux = NULL;
    int i;
    int size=ll_len(this);

    if(this != NULL)
    {
        pNodeAux=this->pFirstNode;
        for(i=0;i<size;i++)
        {
            if(pNodeAux->pElement == pElement)
            {
                returnAux=i;
                break;
            }
            pNodeAux=pNodeAux->pNextNode;
        }
    }


    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(this->pFirstNode != NULL)
        {
            returnAux=0;
        }else
        {
           returnAux=1;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int size=ll_len(this);
    int i;

    if(this != NULL && index >=0 && index<=size)
    {
        i=addNode(this,index,pElement);
        if(i==0)
        {
            returnAux=0;
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    //Node* pNodeAux = NULL;
    int size=ll_len(this);

    if(this != NULL && index >=0 && index<size)
    {
        returnAux=ll_get(this,index);
        ll_remove(this,index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNodeAux = NULL;
    int i;
    int size=ll_len(this);

    if(this != NULL)
    {
        returnAux = 0;
        pNodeAux=this->pFirstNode;
        for(i=0;i<size;i++)
        {
            if(pNodeAux->pElement == pElement)
            {
                returnAux=1;
                break;
            }
            pNodeAux=pNodeAux->pNextNode;
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    Node* pNodeAux = NULL;
    int i,j;
    int size=ll_len(this2);

    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        pNodeAux=this2->pFirstNode;
        for(i=0;i<size;i++)
        {
            j=ll_contains(this,pNodeAux->pElement);
            if(j == 0 || j == -1)
            {
                returnAux = 0;
                break;
            }
            pNodeAux=pNodeAux->pNextNode;
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* newll = NULL;
    Node* pNodeAux = NULL;
    int i;
    int size=ll_len(this);

    if(this!=NULL && from >=0 && from <size && to>from &&to <=size )
    {
        newll=ll_newLinkedList();
        if (newll != NULL)
        {
            pNodeAux=this->pFirstNode;
            for(i=from;i<to;i++)
            {
                ll_add(newll,pNodeAux->pElement);
                pNodeAux=pNodeAux->pNextNode;
            }
        }

    }

    return newll;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* newll= NULL;
    Node* pNodeAux = NULL;
    int i;
    int size=ll_len(this);

    if(this !=NULL)
    {
        newll=ll_newLinkedList();
        if (newll != NULL)
        {
            pNodeAux=this->pFirstNode;
            for(i=0;i<size;i++)
            {
                ll_add(newll,pNodeAux->pElement);
                pNodeAux=pNodeAux->pNextNode;
            }
        }
    }

    return newll;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int swap;
    int i;
    int size=ll_len(this);
    Node* buffer;
    Node* buffer2;
    void* pbufferElement;
    if(this != NULL && pFunc != NULL && size>0 && (order==1 || order==0))
    {
        do
        {
            swap=0;
            for(i=0;i<size-1;i++)
            {
                buffer = getNode(this,i);
                buffer2 = getNode(this,i+1);
                if(order==0 && pFunc(buffer->pElement,buffer2->pElement)<0)
                {
                    pbufferElement = buffer->pElement;
                    buffer->pElement = buffer2->pElement;
                    buffer2->pElement = pbufferElement;
                    swap=1;
                }
                if(order==1 && pFunc(buffer->pElement,buffer2->pElement)>0)
                {
                    pbufferElement = buffer->pElement;
                    buffer->pElement = buffer2->pElement;
                    buffer2->pElement = pbufferElement;
                    swap=1;
                }
            }
        }while(swap!=0);

        returnAux = 0;
    }
    return returnAux;
}

/** \brief Prueba los elementos de la lista (this) con la funcion pasada en parametros (pFunc)
 *
 * \param  Linkedlist this puntero a una lista
 * \param int (*pFunc)(void*) puntero a la funcion criterio
 * \return  retorna return aux: (-1) this o pFunc = NULL (>0) la cantida de elementos que pasaron la funcion criterio
 *
 */

int ll_map(LinkedList* this, int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;
    int size=ll_len(this);
    void* pElement;

    if(this != NULL && pFunc != NULL)
    {
        returnAux = 0;
        for(i=0;i<size;i++)
        {
            pElement=ll_get(this,i);
            returnAux= returnAux + pFunc(pElement);
        }
    }
    return returnAux;
}

/** \brief Elimina los elementos de la lista (this) segun la funcion pasada en parametros (pFunc)
 *
 * \param  Linkedlist this puntero a una lista
 * \param int (*pFunc)(void*) puntero a la funcion criterio
 * \return  retorna return aux: (-1) this o pFunc = NULL (0) la cantida de elementos eliminados por funcion criterio
 *
 */
int ll_reduce(LinkedList* this, int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;
    int size = ll_len(this);
    Node* buffer;

    if(this != NULL && pFunc != NULL)
    {
        for(i=0;i<size;i++)
        {
            buffer=getNode(this,i);
            if(!pFunc(buffer->pElement))
            {
                ll_remove(this,i);
                returnAux++;
            }
        }
    }
    return returnAux;
}

/** \brief Filtra los elementos de la lista (this) con la funcion pasada en parametros (pFunc) y crea una nueva lista
 *
 * \param  Linkedlist this puntero a una lista
 * \param int (*pFunc)(void*) puntero a la funcion criterio
 * \return  retorna return aux: (NULL) this o pFunc = NULL (LinkedList*) puntero a la nueva lista
 *
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
    LinkedList* returnAux = NULL;
    int i;
    int size = ll_len(this);

    if(this != NULL && pFunc != NULL)
    {
        returnAux = ll_newLinkedList();
        for(i=0;i<size;i++)
        {
            if(pFunc(ll_get(this,i)))
            {
                ll_add(returnAux,ll_get(this,i));
            }
        }
    }
    return returnAux;
}
