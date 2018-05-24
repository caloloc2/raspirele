// Incluye librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <string.h>

enum {EXITO, FALLO}; // vector que contiene cuando se ejecuta algun error o se ejecuto correctamente una funcion

int main(void){
	// inicializa los pines correspondientes a la raspberry donde se usaran los reles
	wiringPiSetup();
	pinMode(0, OUTPUT); // GPIO 17 
	pinMode(2, OUTPUT); // GPIO 27 

	FILE *ptr_fichero, *tmp_fichero;
	char nombre_fichero[] = "estados.rsp"; // archivo que contiene que rele debe encender o apagar
	char fichero_tiempo[] = "hora.rsp"; // contiene la hora a la que debe encender todo
	int resultado = EXITO;
	char buffer[3];
	char tiempo_dato[10];
	char output[128];
	int todos = 0;	

	while(1){ // ciclo infinito

		// obtiene la hora actual
		time_t tiempo = time(0);
	    struct tm *tlocal = localtime(&tiempo);    
	    strftime(output,128,"%H:%M",tlocal);

	    // abre el archivo que contiene que reles encender o apagar
		if ((ptr_fichero = fopen(nombre_fichero, "r")) == NULL){
			// en caso de error
			printf("No se ha podido abrir o no se encuentra el fichero %s.\n", nombre_fichero);
			resultado = FALLO;
		}else{
			// si no hay error, lee lo que contiene el archivo y lo guarda en buffer
			while(!feof(ptr_fichero)){
				fgets(buffer, 3, ptr_fichero);
			}

			if (fclose(ptr_fichero)!=0){ // cierra el archivo
				// si hay error al cerrar muestra el error
				printf("No se ha podido cerrar el fichero %s.\n", nombre_fichero);
				resultado = FALLO;
			}else{
				
			}
		}	

	    if (todos==0){ 
	    	// lee el archivo que contiene la hora
		    if ((tmp_fichero = fopen(fichero_tiempo, "r")) == NULL){
		    	// en caso de error
				printf("No se ha podido abrir o no se encuentra el fichero %s.\n", fichero_tiempo);
				resultado = FALLO;
			}else{		
				// si no hay error, lee el contenido del archivo y lo guarda en tiempo_dato
				while(!feof(tmp_fichero)){
					fgets(tiempo_dato, 10, tmp_fichero);
				}

				// cierra el archivo
				if (fclose(tmp_fichero)!=0){
					// en caso de error
					printf("No se ha podido cerrar el fichero %s.\n", fichero_tiempo);
					resultado = FALLO;
				}
				
				if (strcmp(tiempo_dato, output)==0){ // comprueba si la hora configurada es la misma que la actual
					todos = 1; // si es asi, entonces cambia la variable todos a 1
				}
			}		
	    }
		

		// luego de cerrar los archivos, acciona los pines de la raspberry segun corresponda
		if (todos==0){ // si no es la hora configurada entonces, prende o apaga el rele que corresponda
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
		}else{ // si la hora configurada es la misma que la actual entonces, prende los dos reles.
			//printf("prende rele 1-2\n"); 
			digitalWrite(0, HIGH);
			digitalWrite(2, HIGH);
			todos = 0; // cambia a cero la variable para que no se ejecute pasado el minuto y se pueda volver a apagar todo.
		}
		
		delay(300);
	}
	
	return resultado;
}