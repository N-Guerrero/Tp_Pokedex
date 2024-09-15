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
		struct pokemon* nuevo_poke=malloc(sizeof(struct pokemon));
		if(nuevo_poke==NULL){
			printf("error al asignar memoria");
			return false;
		}
		//printf("nombre len %zu\n",strlen(pokemon.nombre)+1);
		nuevo_poke->nombre=(char*)malloc(strlen(pokemon.nombre)+1);
		if(nuevo_poke->nombre==NULL){
			printf("error al asignar memoria");
			return false;
		}
		// printf("poke a agregar %p\n",(void*)&pokemon);
		// printf("poke a agregar t %c\n",pokemon.tipo);
		strcpy(nuevo_poke->nombre,pokemon.nombre);
		nuevo_poke->tipo=pokemon.tipo;
		nuevo_poke->fuerza=pokemon.fuerza;
		nuevo_poke->destreza=pokemon.destreza;
		nuevo_poke->resistencia=pokemon.resistencia;
		pokedex->ptr_pokemons[0]=nuevo_poke;
		pokedex->cantidad_pokemons++;
		//printf("nombre 1 %s\n",pokedex->ptr_pokemons[0]->nombre);
		return true;
	}else{
		
		pokedex->cantidad_pokemons++;
		struct pokemon** new_ptrarray=(struct pokemon**)realloc(pokedex->ptr_pokemons,(pokedex->cantidad_pokemons)*(sizeof(struct pokemon*)));
		
		if(new_ptrarray==NULL){
			printf("error al reasignar memoria a Pokedex->ptr_pokemons");
			return false;
		}
		pokedex->ptr_pokemons=new_ptrarray;
		struct pokemon* nuevo_poke=malloc(sizeof(struct pokemon));
		if(nuevo_poke==NULL){
			printf("error al asignar memoria");
			return false;
		}
		//printf("nombre len %zu\n",strlen(pokemon.nombre)+1);
		nuevo_poke->nombre=(char*)malloc(strlen(pokemon.nombre)+1);
		if(nuevo_poke->nombre==NULL){
			printf("error al asignar memoria");
			return false;
		}
		strcpy(nuevo_poke->nombre,pokemon.nombre);
		nuevo_poke->tipo=pokemon.tipo;
		nuevo_poke->fuerza=pokemon.fuerza;
		nuevo_poke->destreza=pokemon.destreza;
		nuevo_poke->resistencia=pokemon.resistencia;
		pokedex->ptr_pokemons[pokedex->cantidad_pokemons-1]=nuevo_poke;
		//printf("nombre 1 %s\n",pokedex->ptr_pokemons[pokedex->cantidad_pokemons-1]->nombre);
		
		
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

	int id_buscado=-1;
	for(int i=0;i<pokedex->cantidad_pokemons;i++){
		if(strcmp(nombre, pokedex->ptr_pokemons[i]->nombre)==0)
		id_buscado=i;
	}
	if(id_buscado==-1){
		printf("el pokemon buscado no existe");
		return NULL;
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
		//printf("ptr_pokemons %zu: %p\n",i,(void*)pokedex->ptr_pokemons[i]);
		free(pokedex->ptr_pokemons[i]->nombre);
		free(pokedex->ptr_pokemons[i]);
	}
	//printf("ptr del array de punteros: %p\n",(void*)pokedex->ptr_pokemons);
	free(pokedex->ptr_pokemons);
	printf("Pokemons liberados!!\n");
	free(pokedex);
	printf("Pokedex eliminada\n");
}


bool pokedex_ordenar(struct pokedex* pokedex){

	
	for(size_t i=0;i<(pokedex->cantidad_pokemons-1);i++){
		size_t j_min=i;
		for(size_t j=i+1;j<pokedex->cantidad_pokemons;j++){
			if(strcmp(pokedex->ptr_pokemons[j]->nombre,pokedex->ptr_pokemons[j_min]->nombre)<0)
				j_min=j;
			if(j_min!=i){
				struct pokemon* aux=pokedex->ptr_pokemons[i];
				pokedex->ptr_pokemons[i]=pokedex->ptr_pokemons[j_min];
				pokedex->ptr_pokemons[j_min]=aux;
			}
		}
	}
	
	return true;
}