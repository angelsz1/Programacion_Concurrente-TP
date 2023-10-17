%%writefile ProducerConsumer.java
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class ProducerConsumer
{
    public static boolean isNumeric(String string) 
    {
        int intValue;
        if(string == null || string.equals("")) 
        {
            return false;
        }
        try 
        {
            intValue = Integer.parseInt(string);
            return true;
        } 
        catch (NumberFormatException e) 
        {
            return false;
        }
    }

    public static void main(String[] args) 
    {
        //Valido argunmentos
        int argv = args.length;
        if(argv != 1)
        {
            System.out.println("El programa debe recibir 1 argunemto (la cantidad de numeros) para ejecutarse");
            return;
        }
        String number_str = args[0];
        if(!isNumeric(number_str))
        {
            System.out.println("El argunmento debe ser un número");
            return;
        }

        int quantity = Integer.parseInt(number_str);
        // Crear una cola bloqueante con capacidad para 10 elementos
        BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(10);

        // Crear el productor y el consumidor
        Thread producerThread = new Thread(new Producer(queue,quantity));
        Thread consumerThread = new Thread(new Consumer(queue));

        // Iniciar los hilos
        producerThread.start();
        consumerThread.start();

        try 
        {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

}

class Producer implements Runnable 
{
    private final BlockingQueue<Integer> queue;
    private Integer quantity;

    public Producer(BlockingQueue<Integer> queue, Integer quantity) 
    {
        this.queue = queue;
        this.quantity = quantity;
    }

    public Integer getRandomNumber(int min, int max)
    {
        return (int)Math.floor(Math.random() * (max - min + 1) + min);
    }

    @Override
    public void run() 
    {
        try 
        {
            for (int i = 0; i < this.quantity; i++) 
            {
                // Produce un número y lo coloca en la cola
                int random_number = this.getRandomNumber(0,99);
                queue.put(random_number);
                Thread.sleep(100); // Simula un proceso de producción
            }
            queue.put(-1);
        } 
        catch (InterruptedException e) 
        {
            Thread.currentThread().interrupt();
        }
    }
}

class Consumer implements Runnable 
{
    private int min_value;
    private int max_value;
    private int sum;
    private int cont;
    private final BlockingQueue<Integer> queue;

    Map<Integer, Integer> occurrences;
    public Consumer(BlockingQueue<Integer> queue) 
    {
        this.queue = queue;
        //Inicializo con el valor máximo para que cualquier número que llegue sea menor
        this.min_value  = Integer.MAX_VALUE;
        //Inicializo con el valir mínimo para que cualquier número que llegue sea mayor
        this.max_value = Integer.MIN_VALUE;

        this.sum = 0;
        this.cont = 0;
        this.occurrences = new HashMap<>();
    }

    public Integer getMaxOcurrence()
    {
        int maxOcurrence = 0;
        for (int numero : this.occurrences.keySet()) 
        {
            int ocurrencia = this.occurrences.get(numero);
            if (ocurrencia > maxOcurrence) 
            {
                maxOcurrence = ocurrencia;
            }
        }
        return maxOcurrence;
    }

    public void showMaxOcurrenceValues(int maxOcurrrence)
    {
        System.out.println("Valores con la máxima ocurrencia:");
        for (int numero : this.occurrences.keySet()) 
        {
            int ocurrencia = this.occurrences.get(numero);
            if (ocurrencia == maxOcurrrence) 
            {
                System.out.println("Número: " + numero + ", Ocurrencia: " + ocurrencia);
            }
        }
    }

    public void showStatistics()
    {
        System.out.println("VALOR MINIMO: " + this.min_value);
        System.out.println("VALOR MAXIMO: " + this.max_value);
        System.out.println("SUMA DE LOS VALORES: " + this.sum);
        System.out.printf("PROMEDIO: %.2f \n", ((float) this.sum / (float)this.cont));
        Integer maxOcurrence = this.getMaxOcurrence();
        this.showMaxOcurrenceValues(maxOcurrence);
    }

    @Override
    public void run() 
    {
        try 
        {
            while (true) 
            {
                // Toma un número de la cola y lo consume
                int number = queue.take();
                //Condicion de corte
                if(number == -1)
                {
                    break;
                }
                if(number < this.min_value)
                {
                    this.min_value = number;
                }
                if(number > this.max_value) 
                {
                    this.max_value = number;
                }
                this.occurrences.put(number, this.occurrences.getOrDefault(number, 0) + 1);
                this.cont++;
                this.sum += number;
                Thread.sleep(200); // Simula un proceso de consumo
            }
            //Estadisticas
            this.showStatistics();
        } 
        catch (InterruptedException e) 
        {
            Thread.currentThread().interrupt();
        }
    }
}
