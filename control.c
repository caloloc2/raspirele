// gcc control.c -o control
// gcc -Wall -o control control.c -lwiringPi

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <string.h>

enum {EXITO, FALLO};

int main(void){
	wiringPiSetup();
	pinMode(0, OUTPUT); // GPIO 17 
	pinMode(2, OUTPUT); // GPIO 27 

	FILE *ptr_fichero, *tmp_fichero;
	char nombre_fichero[] = "estados.rsp";
	char fichero_tiempo[] = "hora.rsp";
	int resultado = EXITO;
	char buffer[3];
	char tiempo_dato[10];
	char output[128];
	int todos = 0;	

	while(1){

		time_t tiempo = time(0);
	    struct tm *tlocal = localtime(&tiempo);    
	    strftime(output,128,"%H:%M",tlocal);    

		if ((ptr_fichero = fopen(nombre_fichero, "r")) == NULL){
			printf("No se ha podido abrir o no se encuentra el fichero %s.\n", nombre_fichero);
			resultado = FALLO;
		}else{		
			while(!feof(ptr_fichero)){
				fgets(buffer, 3, ptr_fichero);
			}

			if (fclose(ptr_fichero)!=0){
				printf("No se ha podido cerrar el fichero %s.\n", nombre_fichero);
				resultado = FALLO;
			}else{
				
			}
		}	

	    if (todos==0){
		    if ((tmp_fichero = fopen(fichero_tiempo, "r")) == NULL){
				printf("No se ha podido abrir o no se encuentra el fichero %s.\n", fichero_tiempo);
				resultado = FALLO;
			}else{		
				while(!feof(tmp_fichero)){
					fgets(tiempo_dato, 10, tmp_fichero);
				}

				if (fclose(tmp_fichero)!=0){
					printf("No se ha podido cerrar el fichero %s.\n", fichero_tiempo);
					resultado = FALLO;
				}
				
				if (strcmp(tiempo_dato, output)==0){
					todos = 1;
				}
			}		
	    }
		

		// luego de cerrar el archivo, acciona los pines de la raspberry segun corresponda
		if (todos==0){
			if (buffer[0]=='2'){
				//printf("prende rele 1\n");
				digitalWrite(0, HIGH);
			}else if(buffer[0]=='1'){
				//printf("apaga rele 1\n");
				digitalWrite(0, LOW);
			}else if(buffer[0]=='4'){
				//printf("prende rele 2\n");
				digitalWrite(2, HIGH);
			}else if(buffer[0]=='3'){
				//printf("apaga rele 2\n");
				digitalWrite(2, LOW);
			}
		}else{
			//printf("prende rele 1-2\n");
			digitalWrite(0, HIGH);
			digitalWrite(2, HIGH);			
		}
		
		delay(300);
	}
	
	return resultado;
}