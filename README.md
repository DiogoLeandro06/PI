# Projecto Integrador

## Descrição

Este repositório contém o desenvolvimento, organização e documentação de programas implementados no âmbito da Unidade Curricular Projeto Integrador.

## Documentação

O repositório inclui os seguintes documentos de apoio:

- **Guião Milk-V.pdf**: Guião de utilização e configuração da plataforma Milk-V
- **PE39.pdf**: Relatório do projeto PE39 (submetido no Moodle)
- **PE39_poster_fixed.pdf**: Poster do projeto PE39 (exposto na π Projects Fair)

## Estrutura do Repositório

O repositório está organizado da seguinte forma:

- `programas_teste/`: Directório com programas de teste das diferentes *system calls*
- `makefile_template/`: Modelo de Makefile para compilação dos programas
- Documentos PDF com guiões e apresentações do projeto

## Programas Teste *System Calls* POSIX


As seguintes chamadas de sistema foram utilizadas para avaliar diferentes aspectos da interação com o sistema operativo:

- Entrada e saída padrão (I/O):

* [printf](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/printf.html)
* [exec](https://pubs.opengroup.org/onlinepubs/007904875/functions/exec.html)
* [open](https://pubs.opengroup.org/onlinepubs/007904875/functions/open.html)
* [close](https://pubs.opengroup.org/onlinepubs/009604499/functions/close.html)
* [write](https://pubs.opengroup.org/onlinepubs/009695099/functions/write.html)
* [read](https://pubs.opengroup.org/onlinepubs/009604599/functions/read.html)

- Criação e comunicação de processos:
 
* [fork](https://pubs.opengroup.org/onlinepubs/009696799/functions/fork.html) 
* [pipe](https://pubs.opengroup.org/onlinepubs/009604599/functions/pipe.html)

- Gestão de threads

* [pthread_create](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_create.html)
* [pthread_join](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_join.html)
* [pthread_mutex_init](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_init.html)
* [pthread_mutex_lock](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_lock.html)
* [pthread_mutex_unlock](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_unlock.html)
* [pthread_mutex_destroy](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_destroy.html)

</br>
</br>

De seguida, apresentamos os programas desenvolvidos, as chamadas de sistema testadas e os resultados esperados.

---
### Programa *texec.c*

Este programa executa o comando `ls -l` através da chamada da função `execl`.


#### Output Esperado

Espera-se a listagem dos ficheiros presentes no directório onde o programa é executado.

---
### Programa *tread.c*

Este programa lê e exibe no terminal o conteúdo de um ficheiro, cujo nome é fornecido como argumento.


#### Resultado Esperado

Espera-se que seja escrito para o terminal o conteúdo do ficheiro indicado para leitura.

---
### Programa *twrite.c*
 
Este programa escreve uma mensagem num ficheiro, cujo nome é fornecido como argumento.

#### Resultado Esperado

Espera-se que a mensagem de teste seja escrita no ficheiro indicado na execução do programa.

---
### Programa *tgetpid.c*

Neste programa é escrito para o terminal o *id* do processo em execução. 

#### Resultado Esperado

Espera-se que o *id* do processo actual seja impresso no terminal.

---
### Programa *tfork.c*

Neste programa, são realizados dois forks, sendo que, para cada fork, é impresso no terminal o ID de cada processo da família em execução.

#### Resultado Esperado

Espera-se que o processo pai escreva 3 vezes no terminal, os filhos de primeiro grau duas vezes e os filhos de segundo grau 1 vez.

---
### Programa *tpipe.c*

Neste programa, é testada a comunicação entre processos através da utilização de uma *pipe*, onde o processo filho imprime no terminal uma mensagem recebida do processo pai.

#### Resultado Esperado

Espera-se que o processo filho escreva no terminal a mensagem "Testing..." recebida do processo pai. 

> Testing..

---
### Programa *tthread.c*

Neste programa, são criadas duas threads. A rotina de uma das threads consiste em imprimir o valor de uma variável global, x, esperar 2 segundos e, em seguida, imprimir novamente o valor de x.

A rotina da segunda thread consiste em adicionar 2 ao valor de x.

#### Resultado Esperado

Espera-se o seguinte resultado:
> x = 0 </br>
> x = 2

---

### Programa *tmutex.c*

Neste programa, são criadas duas threads com a mesma rotina. A rotina de cada thread consiste em escrever no terminal uma mensagem a indicar o início do seu trabalho, seguida de uma espera de 2 segundos e, por fim, uma mensagem a indicar o término do seu trabalho.

Para garantir que não ocorram condições de corrida na escrita para o terminal, é utilizada uma mutex.

#### Resultado Esperado

Espera-se o seguinte resultado no final da execução do programa:

> Thread 1: Start </br>
> Thread 1: End </br>
> Thread 2: Start </br>
> Thread 2: End
