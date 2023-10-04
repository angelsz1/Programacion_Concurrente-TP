# Trabajo Práctico N° 1 

## Procesos Pesados - Parte 1

### Colab 
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/17itJTrAA1oAiWgDAVAuHwZMSEjI_W0bo?hl=es)

### Enunciado
Programa que genera un árbol de procesos específico.
Todos los procesos incluido el principal (A), informarán por pantalla su letra correspondiente al gráfico, su identificador de proceso (PID) y el PID de su padre. En cuanto a la creación, todos los procesos hijos deberán crearse con el enfoque de programación concurrente, es decir NO sería una solución válida crear un proceso y esperar a que éste finalice para crear el siguiente.

## Procesos Livianos (Threads) - Parte 2

### Colab
* C++ [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/angelsz1/Programacion_Concurrente-TP/blob/master/TP1/C%2B%2B/TP1_Parte_2_Threads_C%2B%2B.ipynb)
* Go [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1p2qNkjIqmb_rGLyGpCuaGUyjUX0cGpDY#scrollTo=tBXVf2_GIMp4)
* Java [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1UADb2HlDZCnUykYoBL_XsrUDkdVhS9Da?usp=sharing)
* Python [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1Xn4TeNK25EPX1Z545fL1Hoy98Gwxehkh?authuser=0#scrollTo=fVJGE6OX5dZ4)

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

## Comunicación y Sincronismo - Parte 3

### Colab
* C++ y Rust [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)]([https://colab.research.google.com](https://colab.research.google.com/drive/1y9JFhErVRk5EP5Z_YxMpofQwEYJGZ_qE?usp=sharing))
* Python [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com)
* Java [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)]( https://colab.research.google.com/drive/16ynjmk11PcdUsnZ6CfLU2gs5rk3_-k41)

### Enunciado
1. **C++ y Rust**

   Crear un programa que reciba por parámetro una cadena de caracteres y convierta cada carácter en un número, generando una contraseña. La idea es que cada letra se corresponda con un número de la siguiente manera; A -> 1, B-> 2, etc. Se consideraran solo letras mayúsculas, en caso de recibir minúsculas, convertirlas. Por ejemplo, para la palabra; ARBOLITO el programa generará la siguiente lista de valores: [1, 18, 2, 15, 12, 9, 20, 15]

   El programa principal, generará dos hilos que realizarán la conversión de cada carácter, una vez finalizada la misma, mostrará por pantalla la contraseña generada. Como parámetro, los hilos recibirán la cantidad de caracteres que deben procesar, es decir que pueden procesar cualquier carácter de la cadena que no haya sido convertida todavía, solo están limitados en la cantidad de caracteres, en cuanto a esto último; la idea es que se reparta de la manera mas equitativa posible, para el ejemplo anterior cada hilo procesará cuatro posiciones, de quedar impar, uno de los hilos procesará un carácter mas que el otro.

   Utilizar algún mecanismo de sincronización entre los hilos para garantizar el correcto funcionamiento del programa.
   
3. **Python**

   Comunicar dos procesos emparentados (Padre – Hijo) a través de una tubería (Pipe).
   
   El programa principal (Padre) deberá proveer una suerte de prompt donde el usuario podrá ingresar palabras (close para finalizar la ejecución). Cada palabra será enviada al hijo. Al finalizar la ejecución el hijo deberá retornar cierta información estadística al padre, quien la imprimirá en pantalla, luego de estos ambos procesos finalizarán.
   
   Sobre la información estadística:
    * Cantidad de caracteres totales
    * Cantidad de letras
    * Cantidad de dígitos
    * La palabra de mayor longitud
    * La palabra de menor longitud

5. **Java**
   
   Crear un programa que genere dos hilos, un productor y un consumidor, el productor producirá valores enteros (0 a 99) y se los enviará al consumidor. El productor deberá comunicar por pantalla cada valor producido. El consumidor generará cierta información estadística que mostrará por pantalla al finalizar la recepción de N valores (el valor N debe ser pasado como parámetro al programa). Luego de esto el programa finalizará la ejecución del programa.

   Sobre la información estadística:
    * El promedio (float)
    * El mínimo
    * El máximo
    * La suma
    * El/los valor/es mas frecuente/s

   Sobre el mecanismo de comunicación:
    * Utilizar la clase ArrayBlockingQueue

Si el grupo necesitará o quisiera agregar algún método de sincronización es libre de hacerlo
