#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "structarea2.h"
#include "funcionestarea2.h"

void nombre(char *arrproducto[], Producto producto[])
{
    for(int i=0;i<10;i++)
    {
        strcpy(producto[i].nombre, arrproducto[i]); 
    }
}
void cantidad(Producto producto[])
{
    srand(time(0));
    for(int i=0;i<10;i++)
    {
        producto[i].cantidad = rand() % 30;

    }
    
}

void precio(int a, Producto producto[],int i)
{
        producto[i].precio= a;
}

void proveedor(Producto producto[])
{
    int MAX_LETRAS = 5;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<MAX_LETRAS;j++)
        {
            producto[i].proveedor[j]=rand()%26 + 65;
        }
        
        producto[i].proveedor[5] = '\0';

    }

}

void guardar_csv(FILE *fdata,Producto producto[])
{
    fprintf(fdata,"nombre,cantidad,proveedor,precio\n");

    for(int i=0; i< 10;i++)
    {
        fprintf(fdata, "%s,%d,%s,%d\n", producto[i].nombre, producto[i].cantidad,producto[i].proveedor, producto[i].precio);
    }
}