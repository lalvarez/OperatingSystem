#include "persona.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char *argv[]){
		{
			/*Variables locales*/
			int fichero_1 = 0; /*fichero 1 entrada*/
			int fichero_2 = 0; /*fichero 2 entrada*/
			int fichero_3 = 0; /*fichero resultado*/

			Person p1;
			Person p2;

			int bytes1 = 0;
			int bytes2 = 0;

			struct stat fichero_1_stat;
			struct stat fichero_2_stat;

			int fichero_1_size = 0;
			int fichero_2_size = 0;

			int sizeP = (sizeof(p1));
			int size1 = sizeP;
			int size2 = sizeP;

				/*Apertura de ficheros*/

				fichero_1 = open(argv[1], O_RDONLY);
				fichero_2 = open(argv[2], O_RDONLY);
				fichero_3 = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0777);

				/*Primero obteneremos el tamano total de los ficheros a leer (bytes)*/

						stat(argv[1], &fichero_1_stat);
						stat(argv[2], &fichero_2_stat);

						fichero_1_size = fichero_1_stat.st_size;
						fichero_2_size = fichero_2_stat.st_size;


					//Comprobamos que ningun fichero presente error
					if (fichero_1 > -1 && fichero_2 > -1 && fichero_3 > -1){


						//Alternativa 1: fichero_1 vacio
						if (fichero_1_size == 0 ){

							//Nos posicionamos apuntando a la ultima persona del fichero_2
							lseek(fichero_2,-size2,SEEK_END);
							//Leemos la persona
							bytes2 = read(fichero_2,&p2,sizeof(p2));

							//Se continua el proceso siempre que la lectura sea correcta y no hayamos llegado al inicio del fichero
							while( (bytes2>0) && (size2 <= fichero_2_size) ){
										//Escribimos la persona leida en el fichero_3
										write(fichero_3, &p2, sizeof(p2));
										//Nos posicionamos en la persona anterior
										size2 = size2 +sizeP;
										lseek(fichero_2,-size2,SEEK_END);
										//Leemos dicha persona
										bytes2 = read(fichero_2,&p2,sizeof(p2));

						}
						}

						//Alternativa 2: fichero_2 vacio
						//El algoritmo sigue el mismo formato que el explicado anteriormente con la diferencia que se realiza sobre el archivo 1
						else if (fichero_2_size == 0 ){

							lseek(fichero_1,-size1,SEEK_END);
							bytes1 = read(fichero_1,&p1,sizeof(p1));

							while( (bytes1>0) && (size1 <= fichero_1_size) ){

										write(fichero_3, &p1, sizeof(p1));
										size1 = size1 +sizeP;
										lseek(fichero_1,-size1,SEEK_END);
										bytes1 = read(fichero_1,&p1,sizeof(p1));

							}
						}
						//Alternativa 3: fichero_1 vacio y fichero_2 vacio
						else if ( fichero_1_size == 0 && fichero_2_size == 0){


						}


					else{
						//Alternativa 4: fichero_1 y fichero _2 tienen contenido
							lseek(fichero_1,-size1,SEEK_END);
							lseek(fichero_2,-size2,SEEK_END);

							bytes1 = read(fichero_1,&p1,sizeof(p1));
							bytes2 = read(fichero_2,&p2,sizeof(p2));



						while( ( (bytes1> 0 ) || (bytes2>0) ) && ((size1 <= fichero_1_size) || (size2 <= fichero_2_size) )){

									if((bytes1)>0){


										write(fichero_3, &p1, sizeof(p1));
										size1 = size1 +sizeP;
										lseek(fichero_1,-size1,SEEK_END);

										if((bytes2)>0){

											write(fichero_3, &p2, sizeof(p2));
											size2 = size2 +sizeP;
											lseek(fichero_2,-size2,SEEK_END);

										}

										else{
										}
									}


									else{

										write(fichero_3, &p2, sizeof(p2));
										size2 = size2 +sizeP;
										lseek(fichero_2,-size2,SEEK_END);
									}

									bytes1 = read(fichero_1,&p1,sizeof(p1));
									bytes2 = read(fichero_2,&p2,sizeof(p2));
						}

					}

				}


					else{
						printf("El archivo no existe");
					}


				return 0;

			}

		}
