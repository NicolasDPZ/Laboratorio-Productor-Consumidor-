/**************************************************************************************
 * Fecha: 14/10/2025
 * Autor: Nicolas David Perdigon Zambrano
 * Materia: Sistemas Operativos
 * Tema: lab Productor-Consumidor
 * profesor: John Corredor
 * ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//se utilizan librerias para que el programa funcione adecuadamente

#define FIFO_FILE "/tmp/fifo_twoway"//define la ruta del fifo para comunicacion

int main() {//inicia el programa principal o main
   int fd;		//Describe el archivo del FIFO
   int end_process;	//Variable de fin del programa
   int stringlen;	//Almacena la longitud de la cadena 
   int read_bytes;	//indica el numero de bytes del FIFO
   char readbuf[80];	//espacio para almacenar los datos 
   char end_str[5];	//palabra para  terminar

   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

 //Se abre el archivo FIFO  para organizar la lectura y la escrutura
  fd = open(FIFO_FILE, O_CREAT|O_RDWR);
   strcpy(end_str, "end");

   while (1) {
      printf("Enter string: ");
      fgets(readbuf, sizeof(readbuf), stdin);//Se obtiene el mensaje ingresado
      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0';//se elimina el salto de linea
      end_process = strcmp(readbuf, end_str);//se compara la entrada con el fin

      //printf("end_process is %d\n", end_process);
      if (end_process != 0) {
         // Si la entrada no es "end", se envía la cadena al servidor a través del FIFO
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         read_bytes = read(fd, readbuf, sizeof(readbuf));
	 // El cliente espera una respuesta del servidor
         readbuf[read_bytes] = '\0';
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      } else {
            // Si el usuario escribe "end", el cliente lo envía al servidor y finaliza
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd);
         break;
      }
   }
//acaba el programa del cliente
   return 0;
}
