#include "persona.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char *argv[]){

//Variables locales
int fichero=0;
Person buffer;  
int bytes=0;

//Apertura del fichero recibido por parámetro
fichero = open(argv[1], O_RDONLY, 0777);

	//Análisis del proceso de apertura del fichero
	if(fichero != -1){
	//Si el fichero se ha abierto correctamente comenzamos la lectura 
		if(bytes=read(fichero, &buffer, sizeof(buffer))==0){ 
			//En caso de que el fichero este vacío se informa por pantalla
			printf("\nEl fichero está vacío.");
		}else{
			//En caso contrario se imprime la primera persona leída por pantalla
			printf("%s\t %i\t %d\t %c\t %.0f\n", buffer.name, buffer.age, buffer.id, buffer.id_ctrl, buffer.salary);	
			
			//Mientras la lectura de la persona se realice correctamente, es decir no se acabe el fichero, se imprime dicha persona por pantalla
			while((bytes=read(fichero, &buffer, sizeof(buffer)))>0){ 
				printf("%s\t %i\t %d\t %c\t %.0f\n", buffer.name, buffer.age, buffer.id, buffer.id_ctrl, buffer.salary);	
			}
		}	
	}
	
	else{
		//Si se ha producido error al abrir el fichero se informa 
		printf("\nEl fichero no se ha abierto correctamente.\n");
        }

	//Cerramos el fichero

	close(fichero);

	return 0;
}
