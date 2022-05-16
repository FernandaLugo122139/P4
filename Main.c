//
// Main.c
// Practica4
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include "ParallelMatrix.h"



/**************Código principal**********/

int main(int argc, char** argv)
{
	
	//Variables a utilizar
	int r,c,tipo;
	int procesadores,max_hilos,hilos,no_matriz;
	long double *ap_matriz,*ap_matriz2,*ap_matriz3;
	int matrices[6][2]={{10,20},{50,50},{200,100},{1000,1000},{1200,1200},{1920,1080}};
	double tiempos[4][6][4];
	double tiempo;
	struct timespec s1,s2;

	
	srand(time(NULL));

	
	//Instrucciones para realizar la simulacion con 1, 2, 3 y 4 hilos disponibles para 4 nucleos.
	
	
	for (hilos=0;hilos<4;hilos++)
	{
		//Instrucciones para utilizar una cantidad de hilos.	
		omp_set_num_threads(hilos+1); //Se establece el numero de hilos en paralelo.
		#pragma omp parallel
		//no_hilos = omp_get_num_threads();
		
		//printf("\nEl numero de threads a usar es: %d\n\n",no_hilos);
		
		//Instruccion para imprimir la cantidad de nucleos disponibles en la computadora
		//y la cantidad maxima de hilos que se solicitaron.
		
		procesadores = omp_get_num_procs(); //Número de procesadores disponible
		max_hilos = omp_get_max_threads(); //Máximo de hilos que se solicitaron
		
		printf("Procesadores disponibles: %d\nMaximo de hilos en paralelo solicitados: %d\n\n", procesadores, max_hilos);
		for (no_matriz=0;no_matriz<6;no_matriz++)
		{
			/*Instrucciones para realizar la simulacion con matrices de
				10 x 20
				50 x 50
				200 x 100
				1000 x 1000
				1200 x 1200
				1920 x 1080.
				*/

			r=matrices[no_matriz][0];
			c=matrices[no_matriz][1];
			
			//Se llama a la función para crear las matrices de manera dinámica
		  	crea_matriz(&ap_matriz,r,c);
		  	crea_matriz(&ap_matriz2,r,c);
		  	crea_matriz(&ap_matriz3,r,c);
		  	
			//Funcion para inicializar las matrices
			llena_matriz(ap_matriz,r,c);
		  	llena_matriz(ap_matriz2,r,c);
		  		
		  	//Impresion de las matrices 
		  	/*printf("\nImpresion de la matriz 1:\n");
		  	imprime_matriz(ap_matriz,r,c);
		  	printf("\nImpresion de la matriz 2:\n");
		  	imprime_matriz(ap_matriz2,r,c);*/
			
			tipo=0;
			//Funcion para sumar las matrices de forma no paralela y toma de tiempo.
				
			clock_gettime(CLOCK_MONOTONIC,&s1);
			suma_matriz(ap_matriz,ap_matriz2,r,c);
			clock_gettime(CLOCK_MONOTONIC,&s2);
			
			tiempo=(double)(s2.tv_sec-s1.tv_sec)+((double)(s2.tv_nsec-s1.tv_nsec)/1000000000L);
			tiempos[hilos][no_matriz][tipo]=tiempo;
			
			//printf("\nTiempo transcurrido secuencial: %lf segundos\n",tiempo);
			
			tipo=1;
			//Funcion para sumar las matrices de forma paralela y toma de tiempo.
			
			clock_gettime(CLOCK_MONOTONIC,&s1);
			suma_matriz_paralelo(ap_matriz,ap_matriz2,r,c);
			clock_gettime(CLOCK_MONOTONIC,&s2);
			
			tiempo=(double)(s2.tv_sec-s1.tv_sec)+((double)(s2.tv_nsec-s1.tv_nsec)/1000000000L);
			tiempos[hilos][no_matriz][tipo]=tiempo;
			
			//printf("\nTiempo transcurrido en paralelo: %lf segundos\n",tiempo);

			tipo=2;
			//Funcion para obtener el valor maximo de forma no paralela y toma de tiempo.
	
			clock_gettime(CLOCK_MONOTONIC,&s1);
			maximo_matriz(ap_matriz,r,c);
			clock_gettime(CLOCK_MONOTONIC,&s2);
			
			tiempo=(double)(s2.tv_sec-s1.tv_sec)+((double)(s2.tv_nsec-s1.tv_nsec)/1000000000L);
			tiempos[hilos][no_matriz][tipo]=tiempo;
			
			tipo=3;
			//Funcion para obtener el valor maximo de forma paralela y toma de tiempo.
			
			clock_gettime(CLOCK_MONOTONIC,&s1);
			maximo_matriz_paralelo(ap_matriz,r,c);
			clock_gettime(CLOCK_MONOTONIC,&s2);
			
			tiempo=(double)(s2.tv_sec-s1.tv_sec)+((double)(s2.tv_nsec-s1.tv_nsec)/1000000000L);
			tiempos[hilos][no_matriz][tipo]=tiempo;
			
			
			//Se llama a la función para liberar los apuntadores de matrices
		  	libera_matriz(&ap_matriz);
		  	libera_matriz(&ap_matriz2);
		  	libera_matriz(&ap_matriz3);
		
		}
		
	
	}
	
	imprime_datos(tiempos,matrices);
	//Impresion de tabla de tiempos de TODA la simulacion.

	return EXIT_SUCCESS;


}
//ultima version

//ultima version

