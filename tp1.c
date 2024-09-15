#include "src/csv.h"
#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>


bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}
bool crear_string_nuevo(const char *str, void *ctx)
{
	
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool mostrar_pokemons(struct pokemon *pokemon, void *ctx){
	if(pokemon!=NULL){
	printf("Nombre: %s,Tipo: %c,Fuerza: %d,Destreza: %d,Resistencia: %d\n",pokemon->nombre,pokemon->tipo,pokemon->fuerza,pokemon->destreza,pokemon->resistencia);
	return true;
	}else return false;
}

int main(int argc, char const *argv[])
{
	struct archivo_csv *data= abrir_archivo_csv("ejemplos/pokedex.csv",';');
	struct pokedex* kanto=pokedex_crear();
	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter,
						       leer_int,
							   leer_int,
							   leer_int };

	int fuerza;
	int resistencia;
	int destreza;
	char tipo;
	char *nombre = NULL;
	void *punteros[5] = { &nombre, &tipo, &fuerza,&destreza,&resistencia };

	while (leer_linea_csv(data, 5, funciones, punteros) == 5) {
		struct pokemon nuevo_pokemon={
			.nombre=nombre,
			.tipo=tipo,
			.fuerza=fuerza,
			.destreza=destreza,
			.resistencia=resistencia
		};

		if(pokedex_agregar_pokemon(kanto,nuevo_pokemon)==false)printf("El pokemon %s se escapo!!\n",nuevo_pokemon.nombre);
		else printf("Capturaste a %s!!!\n",nuevo_pokemon.nombre);

		free(nombre);
	}

	printf("mostrando Pokedex...\n\n");
	size_t pokemons_mostrados=pokedex_iterar_pokemones(kanto,(&mostrar_pokemons),NULL);
	printf("Pokemons capturados: %zu\n",pokemons_mostrados);

	pokedex_destruir(kanto);
	cerrar_archivo_csv(data);
	return 0;
}
