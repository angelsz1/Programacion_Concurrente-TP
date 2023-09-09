import os
import time

def showProcess(process_name):
    print(f"Proceso {process_name} - PID: {os.getpid()} - PID padre: {os.getppid()}")
    
pid_A = os.getpid()
print(f"\nProceso A - PID: {pid_A}")

pid_B = os.fork()
if pid_B == 0:
    #Proceso B
    showProcess("B")
    pid_D = os.fork()
    if(pid_D == 0):
        #Proceso D
        showProcess("D")
    else:
        #Proceo B (padre)
        pid_E = os.fork()
        if(pid_E == 0):
            #Proceso E
            showProcess("E")
            pid_G = os.fork()
            if(pid_G == 0):
                showProcess("G")
            else:
                #Proceso E (padre)
                pid_H = os.fork()
                if(pid_H == 0):
                    showProcess("H")
                else:
                    os.wait()
        else:
            os.wait()
            os.wait()
else:
    #Proceso A
    pid_C = os.fork()
    if(pid_C == 0):
        showProcess("C")
        pid_F = os.fork()
        if(pid_F == 0):
            showProcess("F")
        else:
            os.wait()
    else:
        os.wait()
        os.wait()

time.sleep(20)