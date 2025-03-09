#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int palindromo(char *n){
	int len = strlen(n);
	for (int i = 0; i < len; i++){
		if(tolower(n[i]) != tolower(n[len - i - 1]))
			return 0;
	}
	return 1;
}

char upperName(char *n){
	int len = strlen(n);
	char resp [len];
	for (int i = 0; i < len; i++){
		strcat(resp, toupper(n[i]));
	}
	
	return resp;
}

int main(int argc, char *argv[]) {
	char peticion[100];
	char respuesta[100];
	
	strcpy(peticion, "Miguel/47/Juan/12/Ana/19/Maria/22/Marcos/19");
	char nombre[20];
	int edad;
	char *p = strtok(peticion, "/");
	
	/*
	int len = strlen(nombre);
	char resp [len];
	for (int i = 0; i < len; i++){
		printf("%c\n", toupper(nombre[i]));//strcat(resp, toupper(nombre[i]));
	}
	//printf("%c\n", resp);
	*/
	
	while(p!=NULL){
		strcpy(nombre, p);
		p = strtok(NULL, "/");
		
		if(p == NULL) 
			break;
		
		edad = atoi(p);
		int palindrom = palindromo(nombre);
		//printf("%s\n", upperName(nombre));
		
		if(edad > 18){
			sprintf(respuesta, "%s%s*%d*", respuesta, nombre, edad);
			if(palindrom ==0)
				strcat(respuesta, "0-");
			if(palindrom == 1)
				strcat(respuesta, "1-");	
		}
		p = strtok(NULL, "/");
	}
	respuesta[strlen(respuesta)-1] = '\0';
	printf("Resultado: %s\n", respuesta);
	
}

