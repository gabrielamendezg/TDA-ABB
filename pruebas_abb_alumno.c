#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void prueba_crear_abb_vacio(){
	abb_t* abb = abb_crear(strcmp, NULL);
	print_test("Prueba abb crear abb vacio",abb);
	print_test("Prueba abb la cantidad de elementos es 0",abb_cantidad(abb)==0);
	print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));
    abb_destruir(abb);
}

void prueba_iterar_abb_vacio(){
	abb_t* abb = abb_crear(strcmp,NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void prueba_abb_insertar(){
	abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "A", *valor1 = "guau";
    char *clave2 = "B", *valor2 = "miau";
    char *clave3 = "C", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

void prueba_abb_reemplazar(){
	abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "A", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "B", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

void prueba_abb_reemplazar_con_destruir(){
	abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "B", *valor1a, *valor1b;
    char *clave2 = "A", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

void prueba_abb_borrar(){
	abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "F", *valor_1 = "guau";
    char *clave2 = "B", *valor_2 = "miau";
    char *clave3 = "I", *valor_3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor_1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor_2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor_3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor_3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor_1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor_2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    
    /*Casos de borrar*/
    abb = abb_crear(strcmp,NULL);
	print_test("Prueba abb crear",abb);
    char *clave4 = "A", *clave5 = "D", *clave6 = "G", *clave7 = "K";
    int valor1=1, valor2=2, valor3=3, valor4=4, valor5=5, valor6=6, valor7=7;
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, &valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, &valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, &valor5));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, &valor6));
    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, &valor7));
    /*Borrar hoja*/
    print_test("Prueba abb borrar hoja clave7, es valor7", abb_borrar(abb, clave7) == &valor7);
    /*Borrar con 1 hijo*/
    print_test("Prueba abb borrar con un hijo clave3, es valor3", abb_borrar(abb, clave3) == &valor3);
    /*Borrar con 2 hijos*/
    print_test("Prueba abb borrar con dos hijos clave2, es valor2", abb_borrar(abb, clave2) == &valor2);
	
	abb_destruir(abb);
}

void prueba_abb_clave_vacia(){
	abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

void prueba_abb_valor_null(){
	abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

void prueba_abb_iterar(){
	printf("Pruebas iterador externo\n");
	abb_t* auxbb = abb_crear(strcmp, NULL);
	abb_iter_t* auxbb_iter = abb_iter_in_crear(auxbb);
	print_test("Prueba iterador ver actual abb vacío", abb_iter_in_ver_actual(auxbb_iter) == NULL);
	print_test("Prueba avanzar abb vacío", !abb_iter_in_avanzar(auxbb_iter));
	print_test("Prueba iterador abb vacío está al final", abb_iter_in_al_final(auxbb_iter));
	abb_iter_in_destruir(auxbb_iter);
	print_test("Prueba destruir iterador", auxbb_iter);

	char* clave0 = "B";
	int dato0 = 0;
	
	int* dato_aux = 0;
	print_test("Prueba guardar dato0 con clave0", abb_guardar(auxbb, clave0, &dato0));
	print_test("Prueba pertenece clave0", abb_pertenece(auxbb, clave0));
	dato_aux = abb_obtener(auxbb, clave0);
	print_test("Puede obtener clave0", *dato_aux == 0);
	print_test("Prueba cantidad en abb = 1", abb_cantidad(auxbb)==1);
	
	auxbb_iter = abb_iter_in_crear(auxbb);
	print_test("Prueba crear iterador", auxbb_iter != NULL);
	print_test("Prueba ver actual igual clave0", abb_iter_in_ver_actual(auxbb_iter) != NULL);
	print_test("Prueba avanzar iterador", abb_iter_in_avanzar(auxbb_iter));
	print_test("Prueba iterador está al final", abb_iter_in_al_final(auxbb_iter));
	abb_iter_in_destruir(auxbb_iter);
	print_test("Prueba destruir iterador", auxbb_iter);
	
	dato_aux = abb_borrar(auxbb, clave0);
	print_test("Prueba borrar clave0", *dato_aux == 0);
	print_test("Prueba clave0 no pertenece", !abb_pertenece(auxbb, clave0));
	print_test("Prueba cantidad en abb es 0", abb_cantidad(auxbb)==0);

	char* clave1 = "A";
	char* clave2 = "C";
	int dato1 = 1;
	int dato2 = 2;
	
	print_test("Prueba Guardar dato0 con clave0", abb_guardar(auxbb, clave0, &dato0));
	print_test("Prueba pertenece clave0", abb_pertenece(auxbb, clave0));
	dato_aux = abb_obtener(auxbb, clave0);
	print_test("Prueba obtener clave0", *dato_aux == 0);
	print_test("Prueba cantidad en abb = 1", abb_cantidad(auxbb)==1);
	
	print_test("Prueba Guardar dato1 con clave1", abb_guardar(auxbb, clave1, &dato1));
	print_test("Prueba pertenece clave1", abb_pertenece(auxbb, clave1));
	dato_aux = abb_obtener(auxbb, clave1);
	print_test("Prueba obtener clave1", *dato_aux == 1);
	print_test("Prueba cantidad en abb = 2", abb_cantidad(auxbb)==2);
	
	print_test("Prueba Guardar dato1 con clave2", abb_guardar(auxbb, clave2, &dato2));
	print_test("Prueba pertenece clave2", abb_pertenece(auxbb, clave2));
	dato_aux = abb_obtener(auxbb, clave2);
	print_test("Prueba obtener clave2", *dato_aux == 2);
	print_test("Prueba cantidad en abb = 3", abb_cantidad(auxbb)==3);
	
	auxbb_iter = abb_iter_in_crear(auxbb);
	print_test("Prueba crear iterador", auxbb_iter != NULL);
	const char* clave_aux = abb_iter_in_ver_actual(auxbb_iter);
	print_test("Prueba ver actual es clave1", strcmp(clave_aux,clave1)==0);
	print_test("Prueba avanzar iterador", abb_iter_in_avanzar(auxbb_iter));
	clave_aux = abb_iter_in_ver_actual(auxbb_iter);
	print_test("Prueba ver actual es clave0", strcmp(clave_aux,clave0)==0);
	print_test("Prueba avanzar iterador", abb_iter_in_avanzar(auxbb_iter));
	clave_aux = abb_iter_in_ver_actual(auxbb_iter);
	print_test("Prueba ver actual es clave2", strcmp(clave_aux,clave2)==0);
	print_test("Prueba avanzar iterador", abb_iter_in_avanzar(auxbb_iter));
	
	print_test("Prueba iterador esta al final...", abb_iter_in_al_final(auxbb_iter));
	abb_iter_in_destruir(auxbb_iter);
	print_test("Se destruyo...", auxbb_iter);	
	
	abb_destruir(auxbb);
}

bool duplicar_primeros_3(const char* clave, void* dato, void* extra){
	int* contador = extra;
	if(*contador>=3){
		return false;
	}
	int* valor = dato;
	*valor = *valor * 2;
	*contador += 1;
	return true;
}

void prueba_abb_iterar_interno(){
	printf("Pruebas iterador interno\n");
	abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "F", *clave2 = "B", *clave3 = "I";
    char *clave4 = "A", *clave5 = "D", *clave6 = "G";
    int valor1=1, valor2=2, valor3=3, valor4=4, valor5=5, valor6=6;
    
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, &valor3));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave4, &valor4));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave5, &valor5));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave6, &valor6));
  
	printf("Preba duplicar primeros 3 iterador interno:\n");
	size_t contador = 0;
	abb_in_order(abb,duplicar_primeros_3,&contador);
	int* dato_aux = abb_obtener(abb,clave4);
	print_test("Prueba obtener clave4 duplicada",*dato_aux==8);
	dato_aux = abb_obtener(abb,clave2);
	print_test("Prueba obtener clave2 duplicada",*dato_aux==4);
	dato_aux = abb_obtener(abb,clave5);
	print_test("Prueba obtener clave5 duplicada",*dato_aux==10);
	dato_aux = abb_obtener(abb,clave1);
	print_test("Prueba obtener clave1 no duplicada",*dato_aux==1);
	dato_aux = abb_obtener(abb,clave6);
	print_test("Prueba obtener clave6 no duplicada",*dato_aux==6);
	
	abb_destruir(abb);
}

void pruebas_abb_alumno(){
	prueba_crear_abb_vacio();
	prueba_iterar_abb_vacio();
	prueba_abb_insertar();
	prueba_abb_reemplazar();
	prueba_abb_reemplazar_con_destruir();
	prueba_abb_borrar();
	prueba_abb_clave_vacia();
	prueba_abb_valor_null();
	prueba_abb_iterar();
	prueba_abb_iterar_interno();
}
