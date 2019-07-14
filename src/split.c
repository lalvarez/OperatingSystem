#include "persona.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

int fichero_1=0;		//Se declaran las variables que van a ser necesarias en la implementacion de la funcion
int fichero_2=0;		
int fichero_3=0;
Person p1; 
int bytes=0;
int hay_me=0;
int hay_ma=0;
int comparador=atoi(argv[1]);
int edad=0;

//Con las siguientes tres lineas de codigo se abren los ficheros pasados por parametro. Al tener cada uno una funcion distinta, tambien tendran unos flags diferentes de tal forma que el primer fichero sea de solo lectura y los dos siguientes se crearan y en el caso de que ya existan se truncan, tambien se añaden a esto los permisos necesarios para su posterior utilizacion

fichero_1 = open(argv[2], O_RDONLY,0777);			
fichero_2 = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC,0777);
fichero_3 = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC,0777);

	if(fichero_1 != -1 && fichero_2!=-1 && fichero_3!=-1){	//Se comprueba si hay algun problema al abrir el fichero
		if((bytes=read(fichero_1,&p1,sizeof(p1)))==0){
			printf("\nEl fichero está vacío");
		}
		else{
			//Se comienza a leer el fichero
			edad=p1.age; 	//Almacena la edad de la persona leida

				if(edad<comparador){ 	//Compara si es menor que la edad introducida por parametro
			
					hay_me++; 	//Variable que comprueba si no hay ninguna persona con una edad menor a la introducida
					write(fichero_2,&p1,sizeof(p1)); 	//Si la persona tiene una edad menor la escribe en el segundo fichero introducido por parametro	
				}

				else{
					hay_ma++;
					write(fichero_3,&p1,sizeof(p1)); 	//Si la persona tiene una edad mayor la escribe en el tercer fichero introducido por parametro

				}

			while ((bytes=read(fichero_1,&p1,sizeof(p1)))>0){ 
			
				edad=p1.age; 	//Almacena la edad de la persona leida

				if(edad<comparador){ 	//Compara si es menor que la edad introducida por parametro
			
					hay_me++; 	//Variable que comprueba si no hay ninguna persona con una edad menor a la introducida
					write(fichero_2,&p1,sizeof(p1)); 	//Si la persona tiene una edad menor la escribe en el segundo fichero introducido por parametro
				}

				else{
					hay_ma++;
					write(fichero_3,&p1,sizeof(p1)); 	//Si la persona tiene una edad mayor la escribe en el tercer fichero introducido por parametro

				}
			}
		
			if (hay_me==0){

				printf("\nNo hay ninguna personas menor al número introducido");
		
			}
			if(hay_ma==0){
				printf("\nNo hay ninguna persona mayor al número introducido");
			}
		}
	}
	
	else{
		printf("\nEl archivo no se ha abierto correctamente.");
        }


	close(fichero_1);	//Se cierran los tres ficheros abiertos anteriormente
	close(fichero_2);
	close(fichero_3);

	return 0;
}

