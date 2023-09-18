import random
import threading

#N: Tamaño de la matriz NxN
#min_value: Tamaño mínimo de valor que puede llegar a tener la matriz
#max_value: Tamaño máximo de valor que puede llegar a tener la matriz
def create_matrix(N, min_value, max_value):
    matriz = []
    for i in range(N):
        row = []
        for j in range(N):
            row.append(random.randint(min_value, max_value))
        matriz.append(row)
    return matriz

#matriz: Matriz a mostrar
def show_matriz(matriz):
    for row in matriz:
        print(row)

#mat1: Primera matríz para realizar la suma
#mat2: Segunda matríz para realizar la suma
def secuencial_sum_matriz(mat1, mat2):
    mat_result = []
    for i in range(len(mat1)):
        row = []
        for j in range(len(mat1)):
            acumulator = mat1[i][j] + mat2[i][j]
            row.append(acumulator)
        mat_result.append(row)
    return mat_result

def concurrent_sum_matriz(mat1, mat2):
    mat_result = []
    threads = []
    for i in range(len(mat1)):
        #inicializamos la fila en 0, para evitar errores
        mat_result.append(init_row(len(mat1)))
        
        #Creo un thread para cada fila, pasandole la función y los argumentos
        thread = threading.Thread(target=sum_row, args=(mat1, mat2, mat_result, i))
        thread.start()
        
        #Los guardo para luego esperar que TODOS los threads terminen para devolver el resultado
        threads.append(thread)
    
    #Aguardo que todos terminen para que no se corte el resultado
    for j in threads:
        j.join()
    
    return mat_result
        
#mat1: Primera matríz de la suma
#mat2: Segunda matríz de la suma
#mat_result: Matriz resultante
#index: Índice de la fila que estamos trabajando
def sum_row(mat1, mat2, mat_result, index):
    for i in range(len(mat1)):
        mat_result[index][i] = mat1[index][i] + mat2[index][i]

def mat_equals(mat1, mat2):
    return mat1 == mat2


#length: Longitud de la fila para inicializarla en 0
def init_row(length):
    row = []
    for i in range(length):
        row.append(0)
    return row

if __name__ == "__main__":
    #Valores de enunciado
    max_value = 32
    min_value = -32
    tam_matriz = 5

    matA = create_matrix(tam_matriz, min_value, max_value)
    matB = create_matrix(tam_matriz, min_value, max_value)

    #Calculamos la matriz de forma secuencial
    secuencial_mat = secuencial_sum_matriz(matA, matB)
    #Calculamos la matriz de forma concurrente
    concurrent_mat = concurrent_sum_matriz(matA, matB)
    
    #Demostración que son iguales
    if(mat_equals(secuencial_mat, concurrent_mat) == True):
        print("Las matrices son iguales\n")
    else:
        print("Las matrices no son iguales\n")
        
    #Mostramos las todas las matrices
    print("Matriz A:")
    show_matriz(matA)
    print("Matriz B:")
    show_matriz(matB)
    print("CS:")
    show_matriz(secuencial_mat)
    print("CC:")
    show_matriz(concurrent_mat)