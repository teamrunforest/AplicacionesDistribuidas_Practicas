
// *****************************************************************************************************

// Práctica 2: Aprender el uso del compilador de C en el servidor “GCC”.
// Una vez comprobado que se cuenta con las librerías necesarias deberán realizar un programa en el
// lenguaje C, el cual deberá manipular el contenido de archivos.

// Nota. Documentar los problemas encontrados al compilar y la forma correcta de hacerlo, así como
// la forma de ejecución en sistema linux.

// *****************************************************************************************************

// EQUIPO:
// ROMULO SANDOVAL CABRERA ().
// OMAR JOVANY HERNÁNDEZ SÁNCHEZ (344187).

// Ejemplo:

#include<stdio.h>
//#include<conio.h> // omitido conio.h sólo funciona en windows.
//#include<string.h>
#include <stdlib.h> // libreria adicional.
#include <iostream>

using namespace std; // toma de iostream unicamente la librería std.

void contenido(void)
{
	FILE *archivo;
	char temp[255]; //char *temp;
	int nchar=0;
	int nren=0;
	//system("cls"); //clrscr();

	archivo = fopen("archivo.txt","r+");

	if(archivo) // se agregó llaves a condición.
	{
		printf("archivo abierto\n");
		printf("\ncontenido:\n\n");
		while(fgets(temp,2,archivo))
		{
			printf("%s",temp);
			nchar++;
			if(temp[0]==10)
				nren++;
		}

		printf("\n\nnumero de caracteres: %d\n",nchar);
		printf("numero de renglones : %d",nren+1);
		fclose(archivo);
		getchar(); //getch();
	}
}

void acaracter(void)
{
	//printf("\n\ncaptura caracter:\n");
	//getch();
	
	char car;
	int pos;
	
	printf("Indique el caracter y su posición separados por un espacio:\n");
	scanf("%s %d",&car, &pos);

	FILE *archivo;
	archivo=fopen("archivo.txt","r+");
	if(archivo) // condición agregada.
	{
		fseek(archivo,pos,SEEK_CUR);
		fprintf(archivo,"%c",car);
		fclose(archivo);
		printf("caracter capturado");
	}
}

void arenglon(void)
{
	char cadena[255]; // char *cadena;
	FILE *archivo;
	archivo = fopen("archivo.txt","r+");

	if(archivo) // se agregó condición.
	{
		fseek(archivo,0,SEEK_END);
		printf("\n\ncaptura cadena\n");
		scanf("%s",cadena); //gets(cadena); función no disponible en C.
		fprintf(archivo,"\n%s",cadena);
		fclose(archivo); //close(archivo);
		printf("cadena capturada");
	}
}

int main()
{
	char op;
	contenido();
	printf("\n\n1: agregar caracter\n2: agregar renglon");
	scanf("%c",&op); //op = getch();

	switch(op)
	{
		case '1': acaracter();
		break;
		case '2': arenglon();
		break;
	}

	getchar(); // getch();
	return 0;
}
