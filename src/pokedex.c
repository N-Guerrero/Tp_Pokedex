#include "pokedex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pokedex {
	size_t cantidad_pokemons;
	struct pokemon** ptr_pokemons;
};
bool pokedex_ordenar(struct pokedex*);


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
		return true;
	}else{
		pokedex->cantidad_pokemons++;
		pokedex->ptr_pokemons=(struct pokemon**)realloc(pokedex->ptr_pokemons,(pokedex->cantidad_pokemons++)*(sizeof(struct pokemon*)));
		if(pokedex->ptr_pokemons==NULL){
			printf("error al reasignar memoria a Pokedex->ptr_pokemons");
			return false;
		}
		pokedex->ptr_pokemons[pokedex->cantidad_pokemons]=&pokemon;
		return true;
	}
	if (pokedex==NULL)return false;
}

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex)
{
	return pokedex->cantidad_pokemons;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{

	size_t id_buscado=0;
	for(size_t i=0;i<pokedex->cantidad_pokemons;i++){
		if(strcmp(nombre, pokedex->ptr_pokemons[i]->nombre)==0)
		id_buscado=i;
	}

	return pokedex->ptr_pokemons[id_buscado];
}


size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	bool oredenado=pokedex_ordenar(pokedex);
	if(oredenado==false){
		printf("fallo al ordenar pokedex");
		return 0;
	}
	size_t iteraciones=0;
	for (size_t i=0;i<pokedex->cantidad_pokemons;i++){
		if(funcion(pokedex->ptr_pokemons[i],ctx))
			iteraciones++;
	}

	return iteraciones;
}

void pokedex_destruir(struct pokedex *pokedex)
{
	for(size_t i=0;i<pokedex->cantidad_pokemons;i++){
		free(pokedex->ptr_pokemons[i]);
	}
	free(pokedex->ptr_pokemons);
	if(pokedex->ptr_pokemons==NULL)printf("Pokemons liberados!!\n");
	free(pokedex);
	if(pokedex==NULL)printf("Pokedex eliminada\n");
}


bool pokedex_ordenar(struct pokedex* pokedex){

	struct pokemon* aux=(struct pokemon*)malloc(sizeof(struct pokemon));
	for(size_t i=0;i<(pokedex->cantidad_pokemons-1);i++){
		size_t j_min=i;
		for(size_t j=i+1;j<pokedex->cantidad_pokemons;j++){
			if(strcmp(pokedex->ptr_pokemons[j]->nombre,pokedex->ptr_pokemons[j_min]->nombre)<0)
				j_min=j;
			if(j_min!=i){
				aux=pokedex->ptr_pokemons[i];
				pokedex->ptr_pokemons[i]=pokedex->ptr_pokemons[j_min];
				pokedex->ptr_pokemons[j_min]=aux;
			}
		}
	}
	

}