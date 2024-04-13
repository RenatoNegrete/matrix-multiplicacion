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
* 4. Crear punteros para las matrices
* 5. Apuntar a la reserva de memoria las matrices NxN
* 6. Inicializar las matrices
* 7. Impresion de las matrices
* 8. Funciones (programacion modular)
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define RESERVA (1024*128*64*8)

static double MEM_CHUNK[RESERVA];

/* Funcion para llenar las matrices con datos */
void init_matrices(int n, double *m1, double *m2, double *m3){
  for(int i = 0; i < n*n; i++){
    m1[i] = i*1.1;
    m2[i] = i*2.2;
    m3[i] = i;
  }
};

/* Funcion para imprimir una matriz */
void impre_matriz(int n, double *m){
  if(n < 10){
    for(int i = 0; i < n*n; i++){
      if(i % n == 0){
        printf("\n");
      }
      printf(" %f", m[i]);
    }
    printf("\n--------------------------\n");
  } else {
    printf("\n------------------------\n");
  }
};

/* Funcion para multiplicar dos matrices */
void multi_matrices(int n, double *m1, double *m2, double *m3){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      double sumTemp, *pA, *pB;
      sumTemp = 0.0;
      pA = m1 + i*n;
      pB = m2 + j;
      for(int k = 0; k < n; k++, pA++, pB+=n){
        sumTemp += *pA * *pB;
      }
      m3[i*n+j] = sumTemp;
    }
  }
};

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

  /* Crear punteros a las tres matrices */
  double *mA, *mB, *mC;
  /* Apuntar las matrices a la memoria reservada */
  mA = MEM_CHUNK;
  mB = mA + N*N;
  mC = mB + N*N;

  /* Llamar la funcion init_matrices para llenar las matrices */
  init_matrices(N, mA, mB, mC);
  /* Llamar la funcion impre_matriz para imprimir las matrices que se quieren multiplicar */
  impre_matriz(N, mA);
  impre_matriz(N, mB);
  /* Llamar la funcion multi_matrices para realizar la multiplicacion de dos matrices y guardar el resultado en otra matriz */
  multi_matrices(N, mA, mB, mC);
  printf("\n-------------------------\n");
  impre_matriz(N, mC);


  printf("\n\n FIN DEL PROGRAMA \n");
  return 0;
}