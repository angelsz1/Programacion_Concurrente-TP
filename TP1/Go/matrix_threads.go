package main;

import (
    "fmt"
    "math/rand"
    "time"
    "sync"
)

const (
    N = 5
)

func main() {
    var matrix1 [N][N]int
    var matrix2 [N][N]int
    var result [N][N]int
    var result2 [N][N]int

    matrix1 = generateMatrix()
    matrix2 = generateMatrix()

    fmt.Println("Matrix 1:")
    printMatrix(matrix1)
    fmt.Println("Matrix 2:")
    printMatrix(matrix2)

    t0 := time.Now()
    result = secuentialSum(matrix1, matrix2)
    t1 := time.Now()
    result2 = concurrentSum(matrix1, matrix2)
    t2 := time.Now()
    fmt.Printf("Secuential sum took %v to run.\n", t1.Sub(t0))
    fmt.Printf("Concurrent sum took %v to run.\n", t2.Sub(t1))

    fmt.Println("Result:")
    printMatrix(result)

    fmt.Println("Result2:")
    printMatrix(result2)

    showThatBothResultsAreEqual(result, result2)
    
}

func showThatBothResultsAreEqual(result [N][N]int, result2 [N][N]int) {
    for i := 0; i < N; i++ {
        for j := 0; j < N; j++ {
            if result[i][j] != result2[i][j] {
                fmt.Println("Results are not equal")
                return
            }
        }
    }
    fmt.Println("Results are equal")
}

func generateMatrix() [N][N]int {
    var matrix [N][N]int
    rand.Seed(time.Now().UnixNano())
    for i := 0; i < N; i++ {
        for j := 0; j < N; j++ {
            matrix[i][j] = rand.Intn(64) - 32
        }
    }
    return matrix
}

func printMatrix(matrix [N][N]int) {
    for i := 0; i < N; i++ {
        for j := 0; j < N; j++ {
            fmt.Printf("%d ", matrix[i][j])
        }
        fmt.Println()
    }
    fmt.Println()
}

func secuentialSum(matrix1 [N][N]int, matrix2 [N][N]int) [N][N]int {
    var result [N][N]int
    for i := 0; i < N; i++ {
        for j := 0; j < N; j++ {
            result[i][j] = matrix1[i][j] + matrix2[i][j]
        }
    }
    return result
}

func concurrentSum(matrix1 [N][N]int, matrix2 [N][N]int) [N][N]int {
    var wg sync.WaitGroup
    var result [N][N]int
    wg.Add(N)
    for i := 0; i < N; i++ {
        go func(i int) {
            for j := 0; j < N; j++ {
                result[i][j] = matrix1[i][j] + matrix2[i][j]
            }
            wg.Done()
        }(i)
    }
    wg.Wait()
    return result
}
