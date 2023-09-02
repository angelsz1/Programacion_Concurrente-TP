package main 

import (
	"fmt"
	"os"
	"os/exec"
	"syscall"
	"sync"
    "time"
)

const MaxChild = 2

func main() {
    fmt.Printf("Parent process %d\n", os.Getpid())
	var wg sync.WaitGroup

	for i := 0; i < MaxChild; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()

			cmd := exec.Command(os.Args[0], "child", fmt.Sprintf("%d", i+1))
			cmd.SysProcAttr = &syscall.SysProcAttr{Cloneflags: syscall.CLONE_VM | syscall.CLONE_FS | syscall.CLONE_FILES | syscall.CLONE_SIGHAND | syscall.CLONE_SYSVSEM}
			cmd.Stdout = os.Stdout
			cmd.Stderr = os.Stderr

			if err := cmd.Start(); err != nil {
				fmt.Printf("Error starting child %d: %v\n", i+1, err)
				return
			}

			if err := cmd.Wait(); err != nil {
				fmt.Printf("Error waiting for child %d: %v\n", i+1, err)
				return
			}
		}(i)
	}

	wg.Wait()
}

func init() {
	if len(os.Args) > 1 && os.Args[1] == "child" {
		childProcess()
		os.Exit(0)
	}
}

func childProcess() {
    fmt.Printf("Child process %d\n", os.Getpid())
    time.Sleep(10 * time.Second)
	fmt.Printf("Child process %s\n", os.Args[2])
}

