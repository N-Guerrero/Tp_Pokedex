#include "src/csv.h"
#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	struct archivo_csv *data= abrir_archivo_csv(argv[1],';');
	cerrar_archivo_csv(data);
	return 0;
}
