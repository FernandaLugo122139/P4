//
// ParallelMatrix.c
// Practica4
//
//

#include "ParallelMatrix.h"

//Definicion de funciones
void maximo_matriz(long double *ap_matriz,int r,int c)
{
	int i,mayor=0;
	int tamano=r*c;
	for(i=0;i<tamano;i++)
	{
		if(*(ap_matriz+i)>mayor)
		{
			mayor=*(ap_matriz+i);
		}
	}
	
	//printf("\nEL mayor es %d\n",mayor);
}

void maximo_matriz_paralelo(long double *ap_matriz,int r,int c)
{
	int auxr,auxc;
	int *ap_vector,tamano;
	ap_vector=(int*)calloc(r,sizeof(int));
	//printf("\nVALOR DEL VECTOR:%d\n",*(ap_vector+1));
	//Ciclo que controla los renglones
	#pragma omp parallel for private(auxc)
	for(auxr=0;auxr<r;auxr++)
	{
	//Ciclo que controla las columnas
	for(auxc=0;auxc<c;auxc++)
	{
	  	if(*(ap_matriz+(auxc+(c*auxr)))>*(ap_vector+auxr))
	  	{
	  	
	 		*(ap_vector+auxr)=*(ap_matriz+(auxc+(c*auxr)));
		}
	}
	}
	
	tamano=*(ap_vector+0);
	auxr=0;
	while(auxr<r)
	{
		if(*(ap_vector+auxr)>tamano)
		{
		 	tamano=*(ap_vector+auxr);
		}
		auxr=auxr+1;
	}
	//printf("\nEL maximo es:%d\n",tamano);
	
	free(ap_vector);
    	ap_vector=NULL;
	
}




void imprime_datos(double tiempos[4][6][4],int matrices[6][2])
{
	int hilos,matriz,operacion;
	
	for (hilos=0;hilos<4;hilos++)
	{
		printf("\n\nNUMERO DE HILOS:%d\n\n",hilos+1);
		printf("%25s", "SUMA SEC");
		printf("%25s", "SUMA PAR");
		printf("%25s", "MAXIMO SEC");
		printf("%25s", "MAXIMO PAR");
		for (matriz=0;matriz<6;matriz++)
		{
			printf("\n");
			printf("%dX%-15d",matrices[matriz][0],matrices[matriz][1]);
			for(operacion=0;operacion<4;operacion++)
			{	
				
				printf("%-25lf",tiempos[hilos][matriz][operacion]);
			}
			
		}
		
		
	}
	
	printf("\n");

}

void suma_matriz(long double *ap_matriz,long double *ap_matriz2,int r,int c)
{

	long double *ap_matriz3;
	int auxr,auxc;
	crea_matriz(&ap_matriz3,r,c);


	//Ciclo que controla los renglones
	for(auxr=0;auxr<r;auxr++)
	{
	//Ciclo que controla las columnas
	for(auxc=0;auxc<c;auxc++)
	{
	//Se realiza la inserción
  	*(ap_matriz3+(auxc+(c*auxr)))=*(ap_matriz+(auxc+(c*auxr)))+*(ap_matriz2+(auxc+(c*auxr)));
 
	}
	}
	
	//printf("\nImpresion de la matriz resultado:\n");
  	//imprime_matriz(ap_matriz3,r,c);
	libera_matriz(&ap_matriz3);
		
	
}

void suma_matriz_paralelo(long double *ap_matriz,long double *ap_matriz2,int r,int c)
{

	long double *ap_matriz3;
	int auxr,auxc;
	crea_matriz(&ap_matriz3,r,c);


	//Ciclo que controla los renglones
	#pragma omp parallel for private(auxc)
	for(auxr=0;auxr<r;auxr++)
	{
	//Ciclo que controla las columnas
	//printf("ThreadID: %d de %d\n",omp_get_thread_num(),omp_get_num_threads());
	for(auxc=0;auxc<c;auxc++)
	{
	//Se realiza la inserción
  	*(ap_matriz3+(auxc+(c*auxr)))=*(ap_matriz+(auxc+(c*auxr)))+*(ap_matriz2+(auxc+(c*auxr)));
 
	}
	}
	
	//printf("\nImpresion de la matriz resultado:\n");
  	//imprime_matriz(ap_matriz3,r,c);
	libera_matriz(&ap_matriz3);

}

void crea_matriz(long double **ap_matriz,int r,int c)
/*Crea la matriz de manera dinámica
Recibe: doble apuntador a la matriz, el número de renglones y de columnas
Envía:void*/
{
  *ap_matriz=(long double *)malloc((r*c)*sizeof(long double));//Utilización de malloc para la creación de la matriz
}



void llena_matriz(long double*ap_matriz,int r, int c)
/*Realiza el llenado de la matriz
Recibe: apuntador a la matriz, el número de renglones y de columnas y el apuntador al archivo de datos de entrada
Envía:void*/
{
	int auxr,auxc;
	
	//Ciclo que controla los renglones
	for(auxr=0;auxr<r;auxr++)
	{
	//Ciclo que controla las columnas
	for(auxc=0;auxc<c;auxc++)
	{
	//Se realiza la inserción
  	*(ap_matriz+(auxc+(c*auxr)))=rand()%256;
 
	}
	}

}


void imprime_matriz(long double *ap_matriz,int r, int c)
{
/*Realiza la impresión de la matriz
Recibe: apuntador a la matriz, el número de renglones y de columnas
Envía:void*/
int aux,i;
aux=r*c;

//Ciclo que recorre la matriz
for(i=0;i<aux;i++)
{
if(i%c==0)//Valida si ya se termino el renglón para realizar un salto
{
printf("\n");
}
printf("|%.2Lf|",*(ap_matriz+i));//Impresión de la información
}
printf("\n");
}


void libera_matriz(long double **ap_matriz)
{
/*Realiza la liberación del apuntador a la matriz
Recibe: double apuntador a la matriz
Envía:void*/
   
   //Libera al apuntador y hace a apunte a nulo
    free(*ap_matriz);
    *ap_matriz=NULL;

}
//ultima version
