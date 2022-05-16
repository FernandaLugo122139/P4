//
// ParallelMatrix.h
// Practica4
//
//

#pragma once

#ifndef ParallelMatrix_h
#define ParallelMatrix_h

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Prototipos de funciones

void crea_matriz(long double **,int,int);
void libera_matriz(long double **);
void imprime_matriz(long double *,int,int);
void llena_matriz(long double *,int, int);
void suma_matriz(long double *,long double *,int,int);
void suma_matriz_paralelo(long double *,long double *,int,int);
void maximo_matriz(long double *,int,int);
void maximo_matriz_paralelo(long double*,int,int);
void imprime_datos(double [4][6][4],int [6][2]);



#endif
