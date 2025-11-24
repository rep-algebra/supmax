## Supmax

* Description:

Program for obtaining all supermaximal repeats from a set of dependent sequences.
The documentation explaining how the program works can be found in the thesis
of Cristian S. Rocha, presented at the Department of Computer Science, Faculty
of Exact and Natural Sciences, University of Buenos Aires.

* Tools:

  * **supmax**:
    Supermaximal repeat finder for a set of dependent sequences.

  * **fasta2tex.pl**:
    Perl script that converts FASTA input into LaTeX text. (Deprecated)

  * **generate_fragments**:
    Simulates a random sequencing process from a given sequence. Only RAW
    format files are supported. (Deprecated)

  * **generate_genome**:
    Generates a genome with a specified number of repetitions from a set of
    sequences. (Deprecated)

  * **in2tex.pl**:
    Perl script that converts RAW input into LaTeX text. (Deprecated)

  * **randomread.pl**:
    Reads a file and simulates a random sequencing process.

  * **supmax2fasta.pl**:
    Converts the supermaximal repeats produced by `supmax` into FASTA format.

  * **supmax2tex.pl**:
    Converts the supermaximal repeats produced by `supmax` into LaTeX format.

  * **check.pl**:
    Compares a supersequence with the supermaximal repeats obtained from the
    set of dependent sequences.

* Dependencies:

Mandatory:

* glib6
* Perl 5

Optional:

* CLO++ — [http://pmade.org/~pjones/software/clo++/](http://pmade.org/~pjones/software/clo++/)
* GCC v3 — (required by CLO++)

**Note:**
CLO++ significantly simplifies the use of the program. Without it, using the
program becomes quite tedious. It is listed as optional to allow compilation on
IRIX, since GCC version 3 did not exist at the time this code was written.

* Compilation:

Summary:

```
$ bash
$ export CXX=g++3
$ export CC=gcc3
$ ./autogen.sh

If CLO++ is installed:
$ echo #define CLO >> config.h

$ make
```

* Acknowledgments:

  Thanks to Peter Jones for his help using CLO++.

---

© 2002–2025 Cristian S. Rocha. All rights reserved.

This repository contains code and documentation originally developed as part of the 
undergraduate thesis presented at the Department of Computer Science, Faculty of 
Exact and Natural Sciences, University of Buenos Aires. The material is provided for 
academic and historical preservation purposes. Commercial use or redistribution of 
modified versions is not permitted without the author's consent.
