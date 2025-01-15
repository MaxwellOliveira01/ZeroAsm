# Software Básico
O trabalho desenvolvido tem como objetivo o desenvolvimento de um montador e um ligador para uma linguagem Assembly genérica e para fins educacionais. Todo o código se encontra na pasta 'code' além de dois arquivos (montador.cpp e ligador.cpp) que se encontram fora que só geram o montador e o ligador. 

Todos os codigos foram criados, testados e executados no ambiente Linux (Ubuntu 22)

## Como compilar
Junto aos arquivos está um makefile, entao basta executar um comando "make" e ele irá compilar tanto o ligador quanto o montador.

## Como utilizar?
Após compilar, há dois arquivos que podem ser executados: 'montador' e 'ligador'.

O montador espera receber o caminho de um arquivo (.asm ou .pre) via argumento na linha de comando.
A saída será a geração de um arquivo .pre ou .obj, a depender do tipo de arquivo da entrada
Por exemplo: ./montador teste1.asm

O ligador, por outro lado, espera receber dois argumentos via linha de comando e sua saída sempre é a geração de um arquivo .obj
Por exemplo: ./ligador codigo_1.obj codigo_2.obj

## Testes

Para garantir a corretude do programa, foram criados uma serie de casos de testes e um script em python que roda automaticamente todos eles e verifica se a
saida está como o esperado. Isso pode ser conferido na pasta '/tests'

## Autores

Maxwell Oliveira dos Reis - 221002100
Bruno Henrique Duarte - 221022239