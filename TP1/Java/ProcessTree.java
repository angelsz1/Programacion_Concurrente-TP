package TP1.Java;

import java.io.IOException;
import java.util.ArrayList;

public class ProcessTree
{
  public static void main(String[] args) throws IOException, InterruptedException
  {
    try
    {
      ArrayList<Process> processList = new ArrayList<>();
      String node = args.length > 0 ? args[0] : "A";

      showProcessInfo(node);

      switch (node)
      {
        case "A":
          processList.add(createProcess("B"));
          processList.add(createProcess("C"));
          break;
        case "B":
          processList.add(createProcess("D"));
          processList.add(createProcess("E"));
          break;
        case "C":
          processList.add(createProcess("F"));
          break;
        case "E":
          processList.add(createProcess("G"));
          processList.add(createProcess("H"));
          break;
        case "D":
        case "F":
        case "G":
        case "H":
          break;
        default:
          System.out.println("Nodo desconocido");
      }

      waitChilds(processList);
      Thread.sleep(10000);
    } catch (IOException | InterruptedException e)
    {
      e.printStackTrace();
    }
  }

  public static Process createProcess(String node) throws IOException, InterruptedException
  {
    ProcessBuilder pb = new ProcessBuilder("java", "ProcessTree.java", node);
    pb.inheritIO();
    Process p = pb.start();

    return p;
  }

  public static void showProcessInfo(String node)
  {
    long pid = ProcessHandle.current().pid();
    long ppid = ProcessHandle.current().parent().get().pid();

    System.out.print("Soy el nodo " + node + " PID: " + pid + " PPID: " + ppid + "\n");
  }

  public static void waitChilds(ArrayList<Process> processList) throws InterruptedException
  {
    for (Process process : processList)
    {
      process.waitFor();
    }
  }
}
