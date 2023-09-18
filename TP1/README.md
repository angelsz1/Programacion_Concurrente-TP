# Trabajo Práctico N° 1 

## Procesos Pesados - Parte 1

### Colab 
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/17itJTrAA1oAiWgDAVAuHwZMSEjI_W0bo?hl=es)

### Enunciado
Programa que genera un árbol de procesos específico.
Todos los procesos incluido el principal (A), informarán por pantalla su letra correspondiente al gráfico, su identificador de proceso (PID) y el PID de su padre. En cuanto a la creación, todos los procesos hijos deberán crearse con el enfoque de programación concurrente, es decir NO sería una solución válida crear un proceso y esperar a que éste finalice para crear el siguiente.

## Procesos Livianos (Threads) - Parte 2

### Colab
* C++ [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/googlecolab/colabtools/blob/master/notebooks/colab-github-demo.ipynb)
* Go [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/googlecolab/colabtools/blob/master/notebooks/colab-github-demo.ipynb)
* Java [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/googlecolab/colabtools/blob/master/notebooks/colab-github-demo.ipynb)
* Python [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/googlecolab/colabtools/blob/master/notebooks/colab-github-demo.ipynb)

### Enunciado
Programa que genera y suma dos matrices de 5x5 de dos formas distintas:

a. Suma secuencial (algoritmo sin hilos)

b. Suma concurrente (algoritmo con hilos)

En cuanto al programa principal:
* Creará las matrices a sumar A y B con números enteros aleatorios (-32 a 32) así como 
la matriz resultado CS (Generada secuencialmente) y CC (Generada 
concurrentemente).
* Al finalizar el programa deberá comparar que la matriz resultante CS sea igual a CC y 
mostrará por pantalla el resultado de la comparación.

a. Suma secuencial
* Se deberá realizar la suma de la matriz A y B almacenando el resultado en la matriz CS.
* La suma será realizada en forma secuencial (Sin concurrencia)
  
b. Suma concurrente
* Creará una cantidad de hilos igual a 5.
* Cada hilo deberá tomar una fila de la matriz A y realizar la suma con la fila 
correspondiente de la matriz B, generando la fila resultado en la matriz CC.
* Al finalizar todos los hilos, el main deberá informar por pantalla las matrices A y B 
generadas, así como la matriz resultado CC