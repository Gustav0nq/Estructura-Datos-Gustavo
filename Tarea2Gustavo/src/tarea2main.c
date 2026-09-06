#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "structarea2.h"
#include "funcionestarea2.h"

//dudas: porque arrproducto debe ser un puntero
int main ()
{
    int a;
    int inicio = 0;
    char *arrproducto[10] = {"Pera","Manzana","Uva","Sandia","Platano","Kiwi","Frutilla","Frambuesa","Arandanos","Naranja"};
    Producto producto[10];

    nombre(arrproducto,producto);
    cantidad(producto);
    proveedor(producto);
    for(int i=0;i<10;i++)
    {
        printf("Dame el valor de [%s]\n",producto[i].nombre);
        scanf("%d",&a);
        if (a<=0)
        {
            printf("El valor que ingresaste debe ser mayor que 0");
            return -1;
        }
        
        precio(a,producto,i);


    }

    for(int i=0;i<10;i++)
    {
        printf("NOMBRE: [%s]\nCANTIDAD: [%d]\nPRECIO: [%d]\nPROVEEDOR [%s]\n",&producto[i].nombre[inicio],producto[i].cantidad,producto[i].precio,&producto[i].proveedor[inicio]);
    }
    
    FILE *fdata = fopen("inventario.csv", "w");

    if(fdata == NULL)
    {
        return -1;
    }

    guardar_csv(fdata, producto);
    fclose(fdata);
    return 0;
}