package TP1.Java;

public class MatricesAdder {
  final static int ROWS = 5;
  final static int COLUMNS = 5;
  final static int MIN_VALUE = -32;
  final static int MAX_VALUE = 32;
  static int CC[][] = new int[ROWS][COLUMNS];

  public static class RowsAdder extends Thread {
    int rowToProcess;
    int rowAToProcess[];
    int rowBToProcess[];

    public RowsAdder(int rowToProcess, int[] rowAToProcess, int[] rowBToProcess) {
      this.rowToProcess = rowToProcess;
      this.rowAToProcess = rowAToProcess;
      this.rowBToProcess = rowBToProcess;
    }

    @Override
    public void run() {
      System.out.println("Hilo " + Thread.currentThread().getName() + " procesando fila " + rowToProcess);
      for (int i = 0; i < COLUMNS; i++) {
        CC[rowToProcess][i] = rowAToProcess[i] + rowBToProcess[i];
      }

      try {
        // Thread.sleep(10000);
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
  }

  public static void main(String[] args) {
    int[][] matrixA = generateAleatoryMatrix(ROWS, COLUMNS, MIN_VALUE, MAX_VALUE);
    int[][] matrixB = generateAleatoryMatrix(ROWS, COLUMNS, MIN_VALUE, MAX_VALUE);

    int[][] CS = new int[ROWS][COLUMNS];

    CS = addMatricesSequentially(matrixA, matrixB);
    addMatricesConcurrently(matrixA, matrixB);
    printMatrix(matrixA, "Matriz A");
    printMatrix(matrixB, "Matriz B");
    printMatrix(CS, "Matriz C (Secuencial)");
    printMatrix(CC, "Matriz C (Concurrente)");
    printResultComparation(CS, CC);
  }

  public static int[][] addMatricesSequentially(int[][] matrixA, int[][] matrixB) {
    int[][] CS = new int[matrixA.length][matrixA[0].length];
    for (int i = 0; i < matrixA.length; i++) {
      for (int j = 0; j < matrixA[0].length; j++) {
        CS[i][j] = matrixA[i][j] + matrixB[i][j];
      }
    }
    return CS;
  }

  public static void addMatricesConcurrently(int[][] matrixA, int[][] matrixB) {
    RowsAdder[] rowsAdder = new RowsAdder[matrixA.length];

    for (int i = 0; i < matrixA.length; i++) {
      rowsAdder[i] = new RowsAdder(i, matrixA[i], matrixB[i]);
      rowsAdder[i].start();
    }

    try {
      for (RowsAdder rowAdder : rowsAdder) {
        rowAdder.join();
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static int[][] generateAleatoryMatrix(int rows, int columns, int minValue, int maxValue) {
    int[][] matrix = new int[rows][columns];

    for (int[] row : matrix) {
      for (int i = 0; i < row.length; i++) {
        row[i] = (int) (Math.random() * (maxValue - minValue + 1) + minValue);
      }
    }

    return matrix;
  }

  public static void printResultComparation(int[][] matrixA, int[][] matrixB) {
    System.out.println("Resultado de la comparación de matrices: "
        + (compareMatrices(matrixA, matrixB) == 0 ? "iguales" : "diferentes"));
  }

  public static int compareMatrices(int[][] matrixA, int[][] matrixB) {
    for (int i = 0; i < matrixA.length; i++) {
      for (int j = 0; j < matrixA[0].length; j++) {
        if (matrixA[i][j] != matrixB[i][j]) {
          return -1;
        }
      }
    }

    return 0;
  }

  public static void printMatrix(int[][] matrix, String title) {
    System.out.println(title);

    for (int[] row : matrix) {
      for (int element : row) {
        System.out.printf("%3d ", element);
      }
      System.out.println();
    }
  }
}