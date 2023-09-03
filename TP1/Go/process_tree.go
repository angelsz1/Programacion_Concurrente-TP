package main 

import (
	"fmt"
	"os"
	"os/exec"
	"syscall"
	"sync"
    "time"
)

func main() {
	var wg sync.WaitGroup

    if len(os.Args) > 1 {
        switch os.Args[1] {
        case "B":
            println("Nodo B, pid:", os.Getpid(), "ppid:", os.Getppid())
            wg.Add(1)
            go childProcess(&wg, "D")
            wg.Add(1)
            go childProcess(&wg, "E")
            break
        case "C":
            println("Nodo C, pid:", os.Getpid(), "ppid:", os.Getppid())
            wg.Add(1)
            go childProcess(&wg, "F")
            break
        case "D":
            println("Nodo D, pid:", os.Getpid(), "ppid:", os.Getppid())
            time.Sleep(10 * time.Second)
            break
        case "E":
            println("Nodo E, pid:", os.Getpid(), "ppid:", os.Getppid())
            wg.Add(1)
            go childProcess(&wg, "G")
            wg.Add(1)
            go childProcess(&wg, "H")
            break
        case "F":
            println("Nodo F, pid:", os.Getpid(), "ppid:", os.Getppid())
            time.Sleep(10 * time.Second)
            break
        case "G":
            println("Nodo G, pid:", os.Getpid(), "ppid:", os.Getppid())
            time.Sleep(10 * time.Second)
            break
        case "H":
            println("Nodo H, pid:", os.Getpid(), "ppid:", os.Getppid())
            time.Sleep(10 * time.Second)
            break
        }

    } else {
        println("Nodo A, pid:", os.Getpid(), "ppid:", os.Getppid())
        wg.Add(1)
        go childProcess(&wg, "B")
        wg.Add(1)
        go childProcess(&wg, "C")
    }

	wg.Wait()
}

func childProcess(wg *sync.WaitGroup, name string) {
    defer wg.Done()
    cmd := exec.Command(os.Args[0], fmt.Sprintf("%s", name))
    cmd.SysProcAttr = &syscall.SysProcAttr{Cloneflags: syscall.CLONE_VM | syscall.CLONE_FS | syscall.CLONE_FILES | syscall.CLONE_SIGHAND | syscall.CLONE_SYSVSEM}
    cmd.Stdout = os.Stdout
    cmd.Stderr = os.Stderr

    if err := cmd.Start(); err != nil {
        fmt.Printf("Error starting child %s: %v\n", name, err)
        return
    }

    if err := cmd.Wait(); err != nil {
        fmt.Printf("Error waiting for child %s: %v\n", name, err)
        return
    }
}

