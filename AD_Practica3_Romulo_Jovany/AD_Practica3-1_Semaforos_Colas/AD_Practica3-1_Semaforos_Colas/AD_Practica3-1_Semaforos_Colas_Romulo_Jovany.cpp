
// *****************************************************************************************************

// Práctica 3: En esta práctica el alumno debe compilar para probar el uso de semáforos, colas.

// Nota. Documentar los problemas encontrados al compilar y la forma correcta de hacerlo, así como
// la forma de ejecución en sistema linux.

// *****************************************************************************************************

// EQUIPO:
// ROMULO SANDOVAL CABRERA ().
// OMAR JOVANY HERNÁNDEZ SÁNCHEZ (344187).

//sem1.c
#include <iostream> //#include <iostream.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>

using namespace std; // para que reconozca cout cin, pertenecientes a std de iostream.

// Esta union hay que definirla o no según el valor de los defines aqui indicados.
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
// La union ya está definida en sys/sem.h
#else
// Tenemos que definir la union
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

#endif
main()
{
	key_t Clave;

	int Id_Semaforo;
	struct sembuf Operacion;
	union semun arg;
	int i=0;

	// Igual que en cualquier recurso compartido (memoria compartida, semaforos o colas) se obtiene una clave
	// a partir de un fichero existente cualquiera
	// y de un entero cualquiera. Todos los procesos que quieran compartir este // semaforo, deben usar el
	// mismo fichero y el mismo entero.

	Clave = ftok ("/bin/ls", 33);
	if (Clave == (key_t)-1)
	{
		cout << "No puedo conseguir clave de semaforo" << endl;
		exit(0);
	}

	// Se obtiene un array de semaforos (10 en este caso, aunque solo se usara uno.
	// El IPC_CREAT indica que lo cree si no lo está ya el 0600 con permisos de lectura y escritura para el usuario
	// que lance
	// los procesos. Es importante el 0 delante para que se interprete en octal.

	Id_Semaforo = semget (Clave, 10, 0600 | IPC_CREAT);
	if (Id_Semaforo == -1)
	{
		cout << "No puedo crear semaforo" << endl;
		exit (0);
	}

	// Se inicializa el semáforo con un valor conocido. Si lo ponemos a 0, es semáforo estará "rojo". Si lo
	// ponemos a 1, estará "verde".
	// El 0 de la función semctl es el índice del semáforo que queremos inicializar dentro del array de 10 que
	// hemos pedido.

	arg.val = 0;
	semctl (Id_Semaforo, 0, SETVAL, &arg);

	// Para "pasar" por el semáforo parándonos si está "rojo", debemos rellenar esta estructura.
	// sem_num es el indice del semáforo en el array por el que queremos "pasar"
	// sem_op es -1 para hacer que el proceso espere al semáforo.
	// sem_flg son flags de operación. De momento nos vale un 0.

	Operacion.sem_num = 0;
	Operacion.sem_op = -1;
	Operacion.sem_flg = 0;

	// Bucle infinito indicando cuando entramos al semáforo y cuándo salimos de él.
	// i hace de contador del número de veces que hemos salido del semáforo.

	while (1) 
	{
		cout << i << " Esperando Semaforo" << endl;

		// Se hace la espera en el semáforo. Se le pasa un array de operaciones y el número de elementos
		// en dicho array.
		// En nuestro caso solo 1.

		semop (Id_Semaforo, &Operacion, 1);
		cout << i << " Salgo de Semaforo " << endl;
		cout << endl;
		i++;
	}
}