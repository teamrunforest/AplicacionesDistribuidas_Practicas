
// Programa para demostración de memoria compartida 1

#include <sys/shm.h>
#include <iostream> // (cambio) #include <iostream.h>
#include <unistd.h>
#include <stdio.h>

int main() // (cambio) void main()
{
	key_t Clave;
	int Id_Memoria;
	int *Memoria = NULL;
	int i,j;

	// Conseguimos una clave para la memoria compartida.
	// Todos los
	// procesos que quieran compartir la memoria, debenobtener la misma
	// clave. Esta se puede conseguir por medio de la funcion ftok.
	// A esta funcion se le pasa un fichero cualquiera que
	// exista y este
	// accesible (todos los procesos deben pasar el mismo
	// fichero) y un
	// entero cualquiera (todos los procesos el mismo
	// entero).

	Clave = ftok ("/bin/ls", 33);
	if (Clave == -1)
	{
		printf("No consigo clave para memoria compartida");
		return -1; // (cambio) exit(0);
	}

	// Creamos la memoria con la clave recien conseguida.
	// Para ello llamamos
	// a la funcion shmget pasandole la clave, el tamano de
	// memoria que
	// queremos reservar (100 enteros en nuestro caso) y
	// unos flags.
	// Los flags son los permisos de
	// lectura/escritura/ejecucion
	// para propietario, grupo y otros (es el 777 en octal) y el
	// flag IPC_CREAT para indicar que cree la memoria.
	// La funcion nos devuelve un identificador para la
	// memoria recien
	// creada.

	Id_Memoria = shmget (Clave, sizeof(int)*100, 0777 |
	IPC_CREAT);
	if (Id_Memoria == -1)
	{
		printf("No consigo Id para memoria compartida");
		return -1; // (cambio) exit (0);
	}

	// Una vez creada la memoria, hacemos que uno de
	// nuestros punteros
	// apunte a la zona de memoria recien creada. Para ello
	// llamamos a
	// shmat, pasandole el identificador obtenido
	//anteriormente y un
	// par de parametros extranos, que con ceros vale.

	Memoria = (int *)shmat (Id_Memoria, (char *)0, 0);
	if (Memoria == NULL)
	{
		printf("No consigo memoria compartida");
		return -1; // (cambio) exit (0);
	}

	// Ya podemos utilizar la memoria.
	// Escribimos cosas en la memoria. Los numeros de 1 a 10
	//esperando
	// un segundo entre ellos. Estos datos seran los que lea el
	//otro
	// proceso.

	for (i=0; i<10; i++)
	{
		for (j=0; j<100; j++)
		{
			Memoria[j] = i;
		}

		printf("Escrito %d",i);
		sleep (1);
	}

	// Terminada de usar la memoria compartida, la liberamos.

	shmdt ((char *)Memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);

	return 0; // linea adicional.
}
