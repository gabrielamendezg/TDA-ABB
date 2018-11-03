#include "abb.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** ESTRUCTURA NODO_ABB **/

typedef struct abb_nodo_t abb_nodo_t;

struct abb_nodo_t{
	char* clave;
	void* dato;
	abb_nodo_t* der;
	abb_nodo_t* izq;
};

abb_nodo_t* abb_nodo_crear(const char* clave, void* dato){
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if(nodo==NULL)return NULL;
	size_t lenclave = strlen(clave);
	char* str = malloc(sizeof(char)*lenclave+1);
	if(str==NULL){
		free(nodo);
		return NULL;
	}
	memcpy(str,clave,lenclave+1);
	nodo->clave = str;
	nodo->dato = dato;
	nodo->der = NULL;
	nodo->izq = NULL;
	return nodo;
}

void abb_nodo_destruir(abb_nodo_t* nodo, void destruir_dato(void*)){
	if(destruir_dato!=NULL) destruir_dato(nodo->dato);
	free(nodo->clave);
	free(nodo);
}

/** ABB **/

struct abb{
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
};

/** FUNCIONES AUXILIARES **/

//Función auxiliar para buscar el nodo que contiene una clave dada si existe en el árbol
abb_nodo_t* abb_nodo_buscar(const abb_t* arbol, abb_nodo_t* nodo, const char* clave){
	if(nodo==NULL) return NULL;
	if(arbol->cmp(nodo->clave,clave)==0){
		return nodo;
	}else if(arbol->cmp(nodo->clave,clave)<0){
		return abb_nodo_buscar(arbol,nodo->der,clave);
	}else{
		return abb_nodo_buscar(arbol,nodo->izq,clave);
	}
}

//función auxiliar para insertar una nueva hoja en el árbol.
bool abb_nodo_insertar(abb_t* arbol,abb_nodo_t* nodo, const char* clave, void* dato){
	int comparacion = arbol->cmp(nodo->clave,clave);
	if(comparacion==0){
		void* dato_anterior = nodo->dato;
		nodo->dato = dato;
		if(arbol->destruir_dato!=NULL) arbol->destruir_dato(dato_anterior);
		return true;
	}else if(comparacion<0){
		if(nodo->der==NULL){
			nodo->der = abb_nodo_crear(clave,dato);
			arbol->cantidad+=1;
			return true;
		}
		return abb_nodo_insertar(arbol,nodo->der,clave,dato);
	}else{
		if(nodo->izq==NULL){
			nodo->izq = abb_nodo_crear(clave,dato);
			arbol->cantidad+=1;
			return true;
		}
		return abb_nodo_insertar(arbol,nodo->izq,clave,dato);
	}
	return false;
}

//Función auxiliar para encontrar el padre de un nodo del árbol
//Devuelve NULL de no encontrarse el nodo en el árbol o si el nodo es la raíz.
abb_nodo_t* abb_nodo_buscar_padre(abb_t* arbol, abb_nodo_t* nodo, const char* clave){
	int comparacion = arbol->cmp(nodo->clave,clave);
	if(comparacion == 0) return NULL;
	if(comparacion < 0){
		if(nodo->der == NULL) return NULL;
		else if(arbol->cmp(nodo->der->clave,clave)==0) return nodo;
		return abb_nodo_buscar_padre(arbol,nodo->der,clave);
	}else{
		if(nodo->izq == NULL) return NULL;
		else if(arbol->cmp(nodo->izq->clave,clave)==0) return nodo;
		return abb_nodo_buscar_padre(arbol,nodo->izq,clave);
	}
}

int abb_num_hijos(abb_nodo_t* nodo){
	int i = 0;
	if(nodo->izq!=NULL)i++;
	if(nodo->der!=NULL)i++;
	return i;
}

void* abb_borrar_hoja(abb_t* arbol, abb_nodo_t* nodo, abb_nodo_t* padre){
	if(nodo==arbol->raiz) arbol->raiz=NULL;
	if(padre!=NULL){
		if(padre->izq!=NULL){
			if(arbol->cmp(nodo->clave,padre->izq->clave)==0) padre->izq = NULL;
		}
		if(padre->der!=NULL){
			if(arbol->cmp(nodo->clave,padre->der->clave)==0) padre->der = NULL;
		}
	}
	void* dato = nodo->dato;
	abb_nodo_destruir(nodo,NULL);
	return dato;
}

void* abb_borrar_un_hijo(abb_t* arbol, abb_nodo_t* nodo){
	abb_nodo_t* padre = abb_nodo_buscar_padre(arbol,arbol->raiz,nodo->clave);
	abb_nodo_t* hijo = nodo->der;
	void* dato = nodo->dato;
	if(hijo==NULL){
		hijo = nodo->izq;
	}
	if(nodo==arbol->raiz){
		abb_nodo_destruir(nodo,NULL);
		arbol->raiz=hijo;
		return dato;
	}
	if(padre->izq!=NULL){
		if(arbol->cmp(nodo->clave,padre->izq->clave)==0) padre->izq = hijo;
	}
	if(padre->der!=NULL){
		if(arbol->cmp(nodo->clave,padre->der->clave)==0) padre->der = hijo;
	}
	abb_nodo_destruir(nodo,NULL);
	return dato;
}

void* abb_borrar_dos_hijos(abb_t* arbol, abb_nodo_t* nodo){
	void* dato = nodo->dato;
	void* dato_aux = NULL;
	abb_nodo_t* min = nodo->der;
	while(min->izq!=NULL) min = min->izq;
	
	size_t len_clave = strlen(min->clave);
	char* clave_aux= malloc(sizeof(char)*len_clave+1);
	memcpy(clave_aux,min->clave,len_clave+1);
	dato_aux = abb_borrar(arbol,clave_aux);
	free(nodo->clave);
	nodo->clave = clave_aux;
	nodo->dato = dato_aux;
	return dato;
}

void abb_destruir_nodos(abb_t* arbol, abb_nodo_t* nodo){
	if(nodo==NULL) return;
	abb_destruir_nodos(arbol,nodo->der);
	abb_destruir_nodos(arbol,nodo->izq);
	abb_nodo_destruir(nodo,arbol->destruir_dato);
	return;
}

/** PRIMITIVAS **/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	if(cmp==NULL) return NULL;
	abb_t* abb = malloc(sizeof(abb_t));
	if(abb==NULL) return NULL;
	abb->raiz = NULL;
	if(destruir_dato!=NULL) abb->destruir_dato = destruir_dato;
	else abb->destruir_dato = NULL;
	abb->cmp = cmp;
	abb->cantidad = 0;
	return abb;
}

bool abb_guardar(abb_t* arbol,const char* clave, void* dato){
	if(arbol->raiz==NULL){
		arbol->raiz = abb_nodo_crear(clave,dato);
		if(arbol->raiz==NULL) return false;
		arbol->cantidad+=1;
		return true;
	}
	return abb_nodo_insertar(arbol,arbol->raiz,clave,dato);
}

void* abb_borrar(abb_t* arbol, const char* clave){
	abb_nodo_t* nodo = abb_nodo_buscar(arbol,arbol->raiz,clave);
	if(nodo==NULL) return NULL;
	abb_nodo_t* padre = abb_nodo_buscar_padre(arbol,arbol->raiz,clave);
	int num_hijos = abb_num_hijos(nodo);
	if(num_hijos==1){
		arbol->cantidad-=1;
		return abb_borrar_un_hijo(arbol,nodo);
	}else if(num_hijos==2){
		return abb_borrar_dos_hijos(arbol,nodo);
	}
	arbol->cantidad-=1;
	return abb_borrar_hoja(arbol,nodo,padre);
}

void* abb_obtener(const abb_t* arbol, const char* clave){
	abb_nodo_t* nodo = abb_nodo_buscar(arbol,arbol->raiz,clave);
	if(nodo == NULL) return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t* arbol, const char* clave){
	if(abb_nodo_buscar(arbol,arbol->raiz,clave)==NULL) return false;
	return true;
}

size_t abb_cantidad(abb_t* arbol){
	return arbol->cantidad;
}

void abb_destruir(abb_t* arbol){
	if(arbol==NULL) return;
	abb_destruir_nodos(arbol,arbol->raiz);
	free(arbol);
}

/** ITERADOR INTERNO **/

bool abb_iterar(abb_nodo_t* nodo, bool visitar(const char* clave, void* valor, void* extra), void* extra){
	if(nodo==NULL) return true;
	if(!abb_iterar(nodo->izq,visitar,extra)) return false;
	if(!visitar(nodo->clave,nodo->dato,extra)) return false;
	if(!abb_iterar(nodo->der,visitar,extra)) return false;
	return true;
}

void abb_in_order(abb_t* arbol, bool visitar(const char* clave, void* valor, void* extra),void* extra){
	abb_iterar(arbol->raiz,visitar,extra);
}

/** ITERADOR EXTERNO **/

struct abb_iter{
	lista_t* pila;
	const abb_t* arbol;
};

abb_iter_t* abb_iter_in_crear(const abb_t* arbol){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(iter==NULL) return NULL;
	iter->arbol=arbol;
	lista_t* pila = lista_crear();
	if(pila==NULL){
		free(iter);
		return NULL;
	}
	iter->pila = pila;
	if(arbol->raiz==NULL) return iter;
	lista_insertar_primero(pila,arbol->raiz);
	abb_nodo_t* nodo = arbol->raiz;
	while(nodo->izq!=NULL){
		nodo = nodo->izq;
		lista_insertar_primero(pila,nodo);
	}
	return iter;
}

bool abb_iter_in_avanzar(abb_iter_t* iter){
	abb_nodo_t* desapilado = lista_borrar_primero(iter->pila);
	if(desapilado==NULL)return false;
	abb_nodo_t* nodo = desapilado->der;
	if(nodo==NULL)return true;
	lista_insertar_primero(iter->pila,nodo);
	while(nodo->izq!=NULL){
		nodo = nodo->izq;
		lista_insertar_primero(iter->pila,nodo);
	}
	return true;
}

const char* abb_iter_in_ver_actual(const abb_iter_t* iter){
	abb_nodo_t* nodo = lista_ver_primero(iter->pila);
	if(nodo==NULL) return NULL;
	return nodo->clave;
}

bool abb_iter_in_al_final(const abb_iter_t* iter){
	return lista_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
	lista_destruir(iter->pila,NULL);
	free(iter);
}
