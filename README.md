# Software Básico
O trabalho desenvolvido tem como objetivo o desenvolvimento de um montador e um ligador para uma linguagem Assembly genérica e para fins educacionais. Todo o código se encontra na pasta 'code' além de dois arquivos (montador.cpp e ligador.cpp) que se encontram fora que só geram o montador e o ligador. 

## Como utilizar?
Há dois arquivos que podem ser executados: 'montador.exe' e 'ligador.exe' ambos são gerados utilizando o comando make.

O montador.exe é executado da seguinte maneira:
```bash
    ./montador.exe codigo.asm
```
Onde 'codigo.asm' é um código na linguagem assembly. A saída do montador é um código objeto referente ao código inputado.

O ligador.exe é executado da seguinte maneira:
```bash
    ./ligador.exe codigo_1.obj codigo_2.obj
```
Onde 'codigo_1.obj' e 'codigo_2.obj' são objetos já montados, importante mencionar que os arquivos devem estar em ordem. A saída do ligador é um arquivo de nome 'prog1.e', composto por somente o código montado já ligado.