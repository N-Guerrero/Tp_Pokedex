#include "pokedex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pokedex {
	size_t cantidad_pokemons;
	struct pokemon** ptr_pokemons;
};

struct pokedex *pokedex_crear()
{

	
	

	struct pokedex *Pokedex=malloc(sizeof(struct pokedex));
	if(Pokedex==NULL){
		printf("error al asignar memoria a Pokedex");
		return NULL;
	}

	Pokedex->cantidad_pokemons=0;
	Pokedex->ptr_pokemons=(struct pokemon**)malloc(sizeof(struct pokemon*));
	if(Pokedex->ptr_pokemons==NULL){
		printf("error al asignar memoria a Pokedex->ptr_pokemons");
		return NULL;
	}
	
	return Pokedex;
}

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (pokedex->cantidad_pokemons==0){
		pokedex->ptr_pokemons[0]=&pokemon;
		pokedex->cantidad_pokemons++;
	}else{
		pokedex->cantidad_pokemons++;
		pokedex->ptr_pokemons=(struct pokemon**)realloc(pokedex->ptr_pokemons,(pokedex->cantidad_pokemons++)*(sizeof(struct pokemon*)));
		if(pokedex->ptr_pokemons==NULL){
			printf("error al reasignar memoria a Pokedex->ptr_pokemons");
			return 1;
		}
		pokedex->ptr_pokemons[pokedex->cantidad_pokemons]=&pokemon;

	}
	return false;
}

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex)
{
	return pokedex->cantidad_pokemons;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	return NULL;
}


size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	return 0;
}

void pokedex_destruir(struct pokedex *pokedex)
{
}
