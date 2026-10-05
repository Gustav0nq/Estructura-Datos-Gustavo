#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "product.h"

int main()
{
	Inventory inventario = inv_make_empty(NULL);
    if (inventario == NULL) 
	{
        return 1;
	}

	Product p1 = prod_create("Celular", 700000, 100, "Samsung");
    Product p2 = prod_create("PS5", 650000, 1000, "Playstation");
	Product p3 = prod_create("Audifonos", 40000, 25,"JBL");
	Product p4 = prod_create("Lapiz", 35000, 10, "HP");
	Product p5 = prod_create("Computador", 800000, 1000,"HPx360");
	
	
    inventario = inv_insert_first(p1, inventario);
    inventario = inv_insert_last(p2, inventario);
	inventario = inv_insert_last(p3,inventario);
	inventario = inv_insert_last(p4,inventario);

	InventoryElement posicion = inv_forward(inv_first(inventario));
	inventario = inv_insert(p5, inventario, posicion);

	inv_find_by_name(p1.name,inventario);
	inv_print(inventario);
	printf("\n\n");	
	InventoryElement posicion2 = inv_first(inventario);
	inv_delete(posicion2,inventario);
	inv_print(inventario);
	printf("\n\n");
	inv_destroy(inventario);
	return 0;
}
