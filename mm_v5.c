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
* 8. Funciones de multiplicacion de matrices
* 9. Estructura de datos que encapsule datos:
                - N, Th, y las matrices 
                - Se crea una variable del tipo struct creado
                - Se asignan los valores correspondientes
* 10. Crear un vector de hilos de tamaño Th
* 11. Validar que Th sea mayor que 0 y menor que 10
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

/* Se define el espacio que se va a reservar */
#define RESERVA (1024*128*64*8)

/* Se crea una estructura que almacena los valores de N, Th y los apuntadores a las matrices */
struct datos_MM{
int N;
int Th;
double *mA;
double *mB;
double *mC;
};

/* Se reserva un espacio de memoria para almacenar las matrices */
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
void *multi_matrices(void *argMM){
  struct datos_MM *val = (struct datos_MM *)argMM; // Se crea una variable tipo datos_MM para obtener los datos pasados por parametro
  int n = val->N;
  double *m1 = val->mA;
  double *m2 = val->mB; // Se obtienen los datos que se encuentran dentro de la estructura datos_MM
  double *m3 = val->mC;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      double sumTemp, *pA, *pB; // Se declara una suma temporal y dos apuntadores auxiliares
      sumTemp = 0.0;
      pA = m1 + i*n; // El apuntador pA apunta a las fila de la primera matriz
      pB = m2 + j; // El apuntador pB apunta a las columnas de la segunda matriz
      for(int k = 0; k < n; k++, pA++, pB+=n){ // En el ciclo de aumenta las filas de uno en uno y se aumenta las columnas de n en n
        sumTemp += *pA * *pB; // Se guarda en la suma temporal el resultado de la multiplicacion de la fila por la columna
      }
      m3[i*n+j] = sumTemp; // Se guarda en la posicion de la matriz tres el resultado de la suma temporal correspondiente
    }
  }
  return 0;
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

  /* Crear una variable de tipo estructuras para guardar los datos de N, mA, mB, mC */
  struct datos_MM *encValores = (struct datos_MM *)malloc(sizeof(struct datos_MM));
  encValores->N = N;
  encValores->mA = mA;
  encValores->mB = mB;
  encValores->mC = mC;
  /* Llamar la funcion multi_matrices para realizar la multiplicacion de dos matrices y guardar el resultado en otra matriz */
  multi_matrices(encValores);
  printf("\n-------------------------\n");
  /* Llamar la funcion impre_matriz para imprimir el resultado de la multiplicacion */
  impre_matriz(N, mC);


  printf("\n\n FIN DEL PROGRAMA \n");
  return 0;
}