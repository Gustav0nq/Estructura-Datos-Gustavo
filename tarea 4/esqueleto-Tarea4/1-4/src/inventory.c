/**
 * @file inventory.c
 * @brief Funciones relacionadas con inventarios de productos
*/
#include "inventory.h"


//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS PRODUCTOS DEL INVENTARIO
//==============================================================================
Inventory inv_insert(Product P, Inventory I, InventoryElement Position)
{
    if(I==NULL)
    {
        return NULL;
    }
    if(Position==NULL)
    {
        printf("Error\n");
        return I;
    }

    if(P.name==NULL)
    {
        printf("Error\n");
        return I;
    }

    if(P.provider==NULL)
    {   
        printf("Error\n");
        return I;
    }
    PtrToNode comparar;
    int pertenece=(Position==I);
    for(comparar=I->next;!pertenece && comparar!=I;comparar=comparar->next)
    {
        if (comparar == Position)
        {
            pertenece = 1;
        }
    }

    if (!pertenece)
    {
        printf("Error\n");
        return I;
    }

    PtrToNode nuevo_nodo = malloc(sizeof *nuevo_nodo);
    if(nuevo_nodo ==NULL)
    {
        printf("Error\n");
        return I;
    }
    nuevo_nodo->producto=P;
    nuevo_nodo->next=Position->next;
    nuevo_nodo->prev=Position;
    Position->next->prev=nuevo_nodo;
    Position->next=nuevo_nodo;

    I->cantidad++;

    return I;
    
}

Inventory inv_insert_first(Product P, Inventory I)
{
    return inv_insert(P,I,I);
}

Inventory inv_insert_last(Product P, Inventory I)
{
    if(I==NULL)
    {
        return NULL;
    }
    return inv_insert(P, I, I->prev);
}

Inventory inv_delete(InventoryElement Position, Inventory I)
{
    if(I==NULL)
    {
        return NULL;
    }
    if(Position==NULL)
    {   
        printf("Error\n");
        return I;
    }
    PtrToNode comparar;
    int pertenece=(Position==I);
    for(comparar=I->next;!pertenece && comparar!=I;comparar=comparar->next)
    {
        if (comparar == Position)
        {
            pertenece = 1;
        }
    }

    if (!pertenece)
    {
        printf("Error\n");
        return I;
    }
    if(Position==I)
    {
        printf("Error\n");
        return I;
    }
    Position->prev->next = Position->next;
    Position->next->prev = Position->prev;
    I->cantidad--;
    prod_delete(Position->producto);
    free(Position);
    return I;
}

Product* inv_retrieve(InventoryElement Position, Inventory I)
{
    if(I==NULL)
    {
        return NULL;
    }
    if(Position==NULL)
    {   
        printf("Error\n");
        return NULL;
    }
    PtrToNode comparar;
    int pertenece=(Position==I);
    for(comparar=I->next;!pertenece && comparar!=I;comparar=comparar->next)
    {
        if (comparar == Position)
        {
            pertenece = 1;
        }
    }

    if (!pertenece)
    {
        printf("Error\n");
        return NULL;
    }
    if(Position==I)
    {
        printf("Error\n");
        return NULL;
    }
    return &Position->producto;
}

//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS ÍNDICES DEL INVENTARIO
//==============================================================================
InventoryElement inv_header(Inventory I)
{   
    return I;
}

InventoryElement inv_first(Inventory I)
{
    if(I == NULL)
    {
        return I;
    }

    return I->next;
}
InventoryElement inv_last(Inventory I)
{
    if(I == NULL)
    {
        return I;
    }

    return I->prev;
}

InventoryElement inv_forward(InventoryElement Position)
{
    if(Position == NULL)
    {
        return NULL;
    }
    return Position->next;

}
InventoryElement inv_backward(InventoryElement Position) 
{
    if(Position == NULL)
    {
        return NULL;
    }
    return Position->prev;

}



//==============================================================================
//        FUNCIONES RELACIONADAS CON LA TOTALIDAD DEL INVENTARIO
//==============================================================================
void inv_destroy(Inventory I)
{
    if(I==NULL)
    {
        return;
    }
    PtrToNode actual=I->next;
    while(actual!=I)
    {
        PtrToNode siguiente=actual->next;
        prod_delete(actual->producto);
        free(actual);
        actual = siguiente;
    } 
    free(I);
}

Inventory inv_make_empty(Inventory I)
{
    if(I != NULL)
    {
        inv_destroy(I);
    }

    Inventory nuevonodo= malloc(sizeof *nuevonodo); //Reserva de memoria para nuevo nodo
    if(nuevonodo ==  NULL)
    {
        printf("Error\n");
        return NULL;
    }
    nuevonodo->next = nuevonodo;
    nuevonodo->prev = nuevonodo;
    nuevonodo->cantidad = 0;
    return nuevonodo;
}

void inv_print(Inventory I)
{
    if(I==NULL)
    {
        return;
    }
    PtrToNode actual=I->next;
    if(actual == I)
    {
        printf("Está vacío\n");
        return;
    }

    printf("La cantidad de productos es de: [%d]\n", I->cantidad);
    while(actual != I)
    {
        prod_print(actual->producto);
        actual =actual->next;
    }
}
//==============================================================================
//        FUNCIONES DE COMPROBACIÓN DE ESTADO
//==============================================================================
int inv_is_empty(Inventory I)
{
    if(I==NULL)
    {
        return 1;
    }
    PtrToNode actual=I->next;
    if(actual==I)
    {
        return 1;
    }
    else
        return 0;

}

int inv_is_last(InventoryElement Position, Inventory I)
{
    if(I==NULL)
    {
        return 0;
    }

    if(Position == I)
    {
        return 0;
    }
    
    if(Position == NULL)
    {
        return 0;
    }

    if(Position==I->prev)
    {
        return 1;
    }
    return 0;
}

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================

Product* inv_find_by_name(char* name, Inventory I)
{   
    if(I== NULL)
    {
        return NULL;
    }
    if(name == NULL)
    {
        return NULL;
    }
    int cantidad=0;
    PtrToNode actual_adelante = I->next;
    PtrToNode actual_atras = I->prev;

    while (actual_adelante != I && actual_atras != I &&
       actual_adelante != actual_atras &&
       actual_adelante->prev != actual_atras)
    {   
        cantidad++;

        if(strcmp(actual_adelante->producto.name , name)== 0)
        {
            printf("Encontrado en [%d] iteraciones. Por Nodo adelante\n", cantidad);
            return &actual_adelante->producto;
        }   
        if(strcmp(actual_atras->producto.name , name)== 0)
        {
            printf("Encontrado en [%d] iteraciones. Por Nodo atras\n", cantidad);
            return &actual_atras->producto;
        }           
        actual_adelante = actual_adelante->next ;
        actual_atras = actual_atras->prev;
   
    }
    if (actual_adelante == actual_atras && actual_adelante != I)
    {
        cantidad++;

        if (strcmp(actual_adelante->producto.name, name) == 0)
        {
            printf("Encontrado en %d iteraciones. Por ambos nodos\n", cantidad);
            return &actual_adelante->producto;
        }
    }
    printf("No se encontró el producto: %s\n", name);
    return NULL;
}