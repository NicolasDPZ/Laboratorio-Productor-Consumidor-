
/**************************************************************************************
 * Fecha: 14/10/2025
 * Autor: Nicolas David Perdigon Zambrano
 * Materia: Sistemas Operativos
 * Tema: lab productor consumidor
 * profesor: John Corredor
 * ************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
//se utilizan librerias para que el programa funcione

#define FIFO_FILE "/tmp/fifo_twoway"

//firma de la funcion para invertir el contenido del mensaje
void reverse_string(char *);

//prorgama principal
int main() {
   int fd; 		//describe el FIFO
   char readbuf[80];	//espacio asignado para la recepcion de los datos
   char end[10];	//cadena con la palabra clave para acabar
   int to_end;		//controla la finalizacion del programa
   int read_bytes;	//Numero de bytes desde el FIFO

   /* crea el fifo si no existe */
   mkfifo(FIFO_FILE, S_IFIFO|0640);
   strcpy(end, "end");
	//abre el FIFO de lectura y escritura
   fd = open(FIFO_FILE, O_RDWR);
   while(1) {
	//el servidor lee los datos qie envio el cliente
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      //si el mensaje es end, el servidor cierra la conexion
      to_end = strcmp(readbuf, end);

      if (to_end == 0) {
         close(fd);
         break;
      }
	//el servidor revierte la cadena si el mensaje no es end
      reverse_string(readbuf);
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));
      //se envia la cadena invertida al cliente
	write(fd, readbuf, strlen(readbuf));
      //agrega una pausa para que el cliente reciba la informacion
      sleep(2);
   }
	//acaba el programa principar para el servidor
   return 0;
}
//funcion para invertir el mensaje
void reverse_string(char *str) {
   int last, limit, first;
   char temp;
   last = strlen(str) - 1;
   limit = last/2;
   first = 0;
   
   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
   return;
}
