// gcc control.c -o control
// gcc -Wall -o control control.c -lwiringPi

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

enum {EXITO, FALLO};

int main(void){
	wiringPiSetup();
	pinMode(0, OUTPUT); // GPIO 17 
	pinMode(2, OUTPUT); // GPIO 27 

	FILE *ptr_fichero;
	char nombre_fichero[] = "estados.rsp";
	int resultado = EXITO;
	char reles[1];


	while(1){
		if ( (ptr_fichero = fopen(nombre_fichero, "r") ) == NULL){
			printf("No se ha podido abrir o no se encuentra el fichero %s.\n", nombre_fichero);
			resultado = FALLO;
		}else{
			char buffer[3];
			while(!feof(ptr_fichero)){
				fgets(buffer, 3, ptr_fichero);
			}

			/*
			switch (buffer[0]){  
				case '1':
					// apaga rele 1
					reles[0] = 1;
					break;  
				case '2':  
					// prende rele 1
					reles[0] = 2;
					break;  
				case '3':  
					// apaga rele 2
					reles[1] = 3;
					break;  
				case '4':  
					// prende rele 1
					reles[1] = 4;
					break;  
				case '0':  
					// no hace nada
					reles[0] = 0;
					reles[1] = 0;
					break;  
			}		*/

			if (fclose(ptr_fichero)!=0){
				printf("No se ha podido cerrar el fichero %s.\n", nombre_fichero);
				resultado = FALLO;
			}else{
				// luego de cerrar el archivo, acciona los pines de la raspberry segun corresponda
				if (buffer[0]=='2'){
					printf("prende rele 1\n");
					digitalWrite(0, HIGH);
				}else if(buffer[0]=='1'){
					printf("apaga rele 1\n");
					digitalWrite(0, LOW);
				}else if(buffer[0]=='4'){
					printf("prende rele 2\n");
					digitalWrite(2, HIGH);
				}else if(buffer[0]=='3'){
					printf("apaga rele 2\n");
					digitalWrite(2, LOW);
				}
			}
		}	
		delay(500);
	}
	
	return resultado;
}