# Projeto Integrador

## Descrição

Este repositório contém o desenvolvimento, organização e documentação de programas implementados no âmbito da Unidade Curricular Projeto Integrador.
  

## Programas Teste *System Calls* POSIX


As seguintes chamadas de sistema foram utilizadas para avaliar diferentes aspectos da interação com o sistema operacional:

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

- Gerenciamento de threads

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



Este programa executa um novo processo utilizando a chamada de sistema *exec*, sustituindo o processo atual pelo comando *ls -l*. Ele serve para validar o funcionamento do *exec* e sua interação com a estrutura de processos do sistema operacional.


#### Output Esperado

É esperado a listagem dos ficheiros presentes no diretório onde o programa é executado.

---
### Programa *tread.c*



Neste programa é lido e impresso no terminal o conteúdo de um ficheiro cujo nome é passado ao programa como argumento.


#### Output Esperado

É esperado que seja escrito para o terminal o conteúdo do ficheiro de leitura.

---
### Programa *twrite.c*
 


Neste programa é efetuada a escrita de uma mensagem num ficheiro cujo nome é fornecido como argumento.



#### Output Esperado

É esperado que a mensagem de teste seja escrita para o ficheiro indicado aquando a execução do programa.

---
### Programa *tgetpid.c*



Neste programa é escrito para o terminal o *id* do processo em execução. 



#### Output Esperado

É esperado que o *id* do processo atual seja impresso no terminal.

---
### Programa *tfork.c*



Neste programa são feitos 3 forks, onde para cada fork feito é impresso no terminal o id do processo que está a efetuar a escrita.



#### Output Esperado

É esperado que o processo pai escreva 3 vezes no terminal, os filhos de primeiro grau duas vezes e os filhos de segundo grau 1 vez.

---
### Programa *tpipe.c*



Neste programa é testada a comunição entre processos através da utilização de uma *pipe*, onde o processo filho imprime no terminal uma mensagem enviada pelo processo pai para ele.



#### Output Esperado

É esperado que o processo filho escreva no terminal a mensagem "Testing.." enviada pelo processo pai. 

> Testing..

---
### Programa *tthread.c*



Neste programa são criadas duas threads, cuja rotina de uma das threads consiste em imprimir o valor de uma variável global x, esperar 2 segundos e voltar a imprimir o valor de x.

A rotina da segunda thread consiste em somar 2 ao valor de x.

#### Output Esperado

É esperado o seguinte output:
> x = 0 </br>
> x = 2

---

### Programa *tmutex.c*



Neste programa são criadas duas threads com a mesma rotina. A rotina das threads consiste em escrever no terminal uma mensagem a indicar o início do seu trabalho, seguido de uma espera de 2 segundos e finalmente com uma mensagem a indicar o término do seu trabalho. 

Para garantir que não existam condições de corrida na escrita para o terminal é feito o uso de uma mutex.  


#### Output Esperado

É esperado o seguinte output no final da execução do programa:

> Thread 1: Start </br>
> Thread 1: End </br>
> Thread 2: Start </br>
> Thread 2: End

---
