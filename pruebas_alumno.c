#include "pa2m.h"
#include "src/csv.h"
#include "src/pokedex.h"
#include <string.h>
#include <stdbool.h>
// void abrirUnArchivoInexistenteDebeRetornarNull()
// {
// 	struct archivo_csv *archivo =
// 		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
// 	pa2m_afirmar(archivo == NULL, "El archivo no existe y se retorna NULL");
// }

struct archivo_csv* abrirUnArchivoDebeRetornarNombreySeparador()
{
	
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/pokedex.csv", ';');

		
		
	pa2m_afirmar(archivo !=NULL, "El archivo se abrio");
	return archivo;
	
}


void NUmeroDeColumnasLeidas(struct archivo_csv* pokedex){
	size_t leido=leer_linea_csv(pokedex,5,NULL,NULL);
	pa2m_afirmar(leido==5, "se leyeron 5 col");
}

struct pokedex* crearpokedexnoesnull(){
	struct pokedex* kanto =pokedex_crear();
	pa2m_afirmar(kanto!=NULL,"existe la pokedex");
	return kanto;
}

void probarAgregarPokemon(struct pokedex* pokedex){
	struct pokemon pokemon={
		.destreza=100,
		.fuerza=5,
		.resistencia=3,
		.tipo='F',
		.nombre="luxray"
	};
	struct pokemon pokemon2={
		.destreza=10,
		.fuerza=5,
		.resistencia=3,
		.tipo='E',
		.nombre="pichu"
	};
	pa2m_afirmar(pokedex_agregar_pokemon(pokedex,pokemon2)==true,"pokemon agragado");
	pa2m_afirmar(pokedex_agregar_pokemon(pokedex,pokemon)==true,"pokemon agragado");

}

void mostrarcantidaddepokemons(struct pokedex* pokedex){
	size_t cant=pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cant==2,"cantidad adecuada de pokemons");
}
void probar_busqueda(struct pokedex* pokedex){
	const struct pokemon* poke_buscado=pokedex_buscar_pokemon(pokedex,"luxray");
	printf("nombre %s\ntipo %c\nfuerza %d\nresistencia %d\n",
		poke_buscado->nombre,poke_buscado->tipo,poke_buscado->fuerza,poke_buscado->destreza);
	pa2m_afirmar(strcmp(poke_buscado->nombre,"luxray")==0,"nombre encontrado correctamente");
}

bool print(struct pokemon* pokemon,void* ctx){
	printf("nombre: %s\n",pokemon->nombre);
	return true;
}
void probar_iterar(struct pokedex* pokedex){
	bool (*F)(struct pokemon*,void*)=print;
	size_t num=pokedex_iterar_pokemones(pokedex,*F,NULL);
	pa2m_afirmar(num==2,"pokemons iterados correctamente");
}
int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	//abrirUnArchivoInexistenteDebeRetornarNull();
	// struct archivo_csv* archivo =abrirUnArchivoDebeRetornarNombreySeparador();
	// NUmeroDeColumnasLeidas(archivo);
	// cerrar_archivo_csv(archivo);
	struct pokedex* pokedex= crearpokedexnoesnull();
	probarAgregarPokemon(pokedex);
	mostrarcantidaddepokemons(pokedex);
	//probar_busqueda(pokedex);
	probar_iterar(pokedex);

	pokedex_destruir(pokedex);
	
	//otras pruebas?

	return pa2m_mostrar_reporte();
}
