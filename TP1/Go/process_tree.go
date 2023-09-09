package main

import (
	"fmt"
	"os"
	"os/exec"
	"sync"
	"syscall"
	"time"
)

const (
	NodeA string = "A"
	NodeB        = "B"
	NodeC        = "C"
	NodeD        = "D"
	NodeE        = "E"
	NodeF        = "F"
	NodeG        = "G"
	NodeH        = "H"
)

func main() {
	var wg sync.WaitGroup

	if len(os.Args) > 1 {
		switch os.Args[1] {
		case NodeB:
			showNode(NodeB)
			wg.Add(1)
			go childProcess(&wg, NodeD)
			wg.Add(1)
			go childProcess(&wg, NodeE)
			break
		case NodeC:
			showNode(NodeC)
			wg.Add(1)
			go childProcess(&wg, NodeF)
			break
		case NodeD:
			showNode(NodeD)
			time.Sleep(10 * time.Second)
			break
		case NodeE:
			showNode(NodeE)
			wg.Add(1)
			go childProcess(&wg, NodeG)
			wg.Add(1)
			go childProcess(&wg, NodeH)
			break
		case NodeF:
			showNode(NodeF)
			time.Sleep(10 * time.Second)
			break
		case NodeG:
			showNode(NodeG)
			time.Sleep(10 * time.Second)
			break
		case NodeH:
			showNode(NodeH)
			time.Sleep(10 * time.Second)
			break
		}

	} else {
		showNode(NodeA)
		wg.Add(1)
		go childProcess(&wg, NodeB)
		wg.Add(1)
		go childProcess(&wg, NodeC)
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

func showNode(node string) {
	println("Node", node, "pid:", os.Getpid(), "ppid:", os.Getppid())
}
