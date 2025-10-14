all:
	gcc cliente.c -o cliente
	gcc servidor.c -o servidor

clean:
	rm -f cliente servidor
