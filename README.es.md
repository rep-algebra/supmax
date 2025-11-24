(Only in spanish)

Supmax
------

+ Descripción:

Programa para obtener todos las repeticiones supermaximales de un
conjunto de secuencias dependientes. La documentación de como
funciona el mismo esta en la tesis de Cristian S. Rocha presentado
ante el Departamento Computación, Facultad de Ciencias Exactas y
Naturales, Universidad de Buenos Aires.

+ Herramientas:

	+ supmax:	Buscador de repeticiones supermaximales en
			un conjunto de secuencias dependientes.
	+ fasta2tex.pl:	Script el Perl que convierte una entrada
			FASTA en texto Latex. (En desuso).
	+ generate_fragments: Simula a partir de una secuencias
			un secuenciamiento aleatorio. Solo soporta
			archivos en formato RAW. (En desuso).
	+ generate_genome: A partir de un conjunto de secuencias
			genera un genoma con una cantidad
			determinada de repeticiones. (En desuso).
	+ in2tex.pl: Script el Perl que convierte una entrada
                        RAW en texto Latex. (En desuso).
	+ randomread.pl: Lee un archivo y simula un secuenciamiento
			aleatorio.
	+ supmax2fasta.pl: Convierte una salida de supermaximales
			de 'supmax' a fasta.
	+ supmax2tex.pl: Convierte una salida de supermaximales
			de 'supmax' a tex.
	+ check.pl:	Compara una supersecuencia con los supermaximales
			objetidos del conjunto de secuencias dependientes.

+ Dependencias:

Obligatorias:
* glib6
* Perl 5

Optativas:
* CLO++	http://pmade.org/~pjones/software/clo++/
* GCC v3	(CLO++ lo necesita)

Nota: El CLO++ simplifica el uso del programa. Su falta hace muy tedioso
      el uso del programa. Se lo dejo como optativo para poder compilar
      el codigo en IRIX, ya que no existia la version 3 del GCC cuando
      se realizó este codigo.

+ Compilación:

Resumen:
	$ bash
	$ export CXX=g++3
	$ export CC=gcc3
	$ ./autogen.sh

	Si tiene el CLO++ instalado
	$ echo #define CLO >> config.h

	$ make

Agradecimientos:

	Gracias a Peter Jones por su ayuda para usar el CLO++.
	Thanks to Peter Jones for the help to use the CLO++.

