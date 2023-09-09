package TP1.Java;

import java.io.IOException;
import java.util.ArrayList;

public class Process_tree {
    public static void main(String[] args) throws IOException, InterruptedException {
        ArrayList<Process> processList = new ArrayList<>();
        String node = args.length > 0 ? args[0] : "A";

        showProcessInfo(node);

        switch (node) {
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
        }
        for (Process process : processList) {
            process.waitFor();
        }
    }

    public static Process createProcess(String node) throws IOException, InterruptedException {
        ProcessBuilder pb = new ProcessBuilder("java", "Process_tree.java", node);
        pb.inheritIO();
        Process p = pb.start();

        return p;
    }

    public static void showProcessInfo(String node) {
        long pid = ProcessHandle.current().pid();
        long ppid = ProcessHandle.current().parent().get().pid();

        System.out.print("Soy el nodo " + node + " PID: " + pid + " PPID: " + ppid + "\n");
    }
}
