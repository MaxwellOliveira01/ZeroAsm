# Software Básico
O trabalho desenvolvido tem como objetivo o desenvolvimento de um montador e um ligador para uma linguagem Assembly genérica e para fins educacionais. Todo o código se encontra na pasta 'code' além de dois arquivos (montador.cpp e ligador.cpp) que se encontram fora que só geram o montador e o ligador. 

Todos os codigos foram criados, testados e executados no ambiente Linux (Ubuntu 22)

## Como compilar
Junto aos arquivos está um makefile, entao basta executar um comando "make" e ele irá compilar tanto o ligador quanto o montador.

## Como utilizar?
Após compilar, há dois arquivos que podem ser executados: 'montador' e 'ligador'.

O montador é executado da seguinte maneira:
```bash
    ./montador <input>
```
Onde <input> seria um arquivo '.asm' ou '.pre'. A saída do montador pode ser do tipo '.pre' ou '.obj', a depender do conteudo do arquivo.

O ligador é executado da seguinte maneira:
```bash
    ./ligador codigo_1.obj codigo_2.obj
```
Onde 'codigo_1.obj' e 'codigo_2.obj' são objetos já montados e com toda a informação necessaria para sua ligação, importante mencionar que os arquivos devem estar em ordem. A saída do ligador é um arquivo de nome 'prog1.e', composto por somente o código montado já ligado.

## Autores

Maxwell Oliveira dos Reis - 221002100
Bruno Henrique Duarte - 221022239