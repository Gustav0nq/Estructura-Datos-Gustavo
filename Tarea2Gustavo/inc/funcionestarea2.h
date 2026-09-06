#ifndef funcionestarea2_h
#define funcionestarea2_h

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "structarea2.h"

void nombre(char *arrproducto[],Producto producto[]);
void cantidad(Producto producto[]);
void precio(int a, Producto producto[],int i);
void proveedor(Producto producto[]);
void guardar_csv(FILE *fdata, Producto producto[]);


#endif