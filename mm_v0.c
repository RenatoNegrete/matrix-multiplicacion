/**************************************************************
* Fecha: 02/04/2024
* Autor: Renato Negrete
* Materia: Sistemas Operativos
* Profesor: John Corredor
* Tema: Algoritmo clasico Multiplicacion de Matrices
* Objetivo: Crear una aplicacion que use el algoritmo de multiplicacion de matrices clasica (filas * columnas). La aplicacion presentara diversos pasos como metodologia para la implementacion de un algoritmo. La implementacion se hara para martices cuadradas, es decir el numero de filas = columnas

* A continuacion se presentan las diferentes etapas:
* 1. Reserva de memoria
* 2. Se crea el main para ingreso de argumentos de entrada
* 2.1. Arg1 dimension matriz (NxN)
* 2.2. Arg2 cantidad de hilos
* 3. Validar los documentos de entrada
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define RESERVA (1024*128*64*8)

static double MEM_CHUNK[RESERVA];

int main(int argc, char *argv[]){

  /* Se verifica si la cantidad de argumentos es correcta */
  if(argc < 3){
    printf("FALTAN ARGUMENTOS!!!!!!!!! \n");
    printf("\n\t $ ./ejecutable.exe #Dim #Hilos \n");
    return -1;
  }

  /* Se obtiene la dimension de la matriz y la cantidad de hilos */
  int N = (int) atof(argv[1]);
  int Th = (int) atof(argv[2]);

  /* Se verifica si la dimension de la matriz es correcta (no puede ser cero o un valor negativo) */
  if(N <= 0){
    printf("Dimension de matriz incorrecta \n");
    printf("\n\t Debe ser mayor que cero \n");
    return -1;
  }

  /* Se verifica si la cantidad de hilos es correcta (tiene que haber como minimo un hilo) */
  if(Th < 1){
    printf("Cantidad de hilos incorrecta \n");
    printf("\n\tDebe haber por lo menos un hilo \n");
    return -1;
  }

  printf("hola que tal\n");
  printf("dimension matriz NxN = %d \n", N);
  printf("Nunero de hilos = %d \n", Th);

  return 0;
}