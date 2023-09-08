import os
import time

pid_A = os.getpid()
print(f"\nProceso A - PID: {pid_A}")

pid_B = os.fork()
if pid_B == 0:
    #Proceso B
    print(f"Proceso B - PID: {os.getpid()} - PID padre: {os.getppid()}")
    pid_D = os.fork()
    if(pid_D == 0):
        #Proceso D
        print(f"Proceso D - PID: {os.getpid()} - PID padre: {os.getppid()}")
    else:
        #Proceo B (padre)
        pid_E = os.fork()
        if(pid_E == 0):
            #Proceso E
            print(f"Proceso E - PID: {os.getpid()} - PID padre: {os.getppid()}")
            pid_G = os.fork()
            if(pid_G == 0):
                print(f"Proceso G - PID: {os.getpid()} - PID padre: {os.getppid()}")
            else:
                #Proceso E (padre)
                pid_H = os.fork()
                if(pid_H == 0):
                    print(f"Proceso H - PID: {os.getpid()} - PID padre: {os.getppid()}")
                else:
                    os.wait()
        else:
            os.wait()
            os.wait()
else:
    #Proceso A
    pid_C = os.fork()
    if(pid_C == 0):
        print(f"Proceso C - PID: {os.getpid()} - PID padre: {os.getppid()}")
        pid_F = os.fork()
        if(pid_F == 0):
            print(f"Proceso F - PID: {os.getpid()} - PID padre: {os.getppid()}")
        else:
            os.wait()
    else:
        os.wait()
        os.wait()

time.sleep(20)