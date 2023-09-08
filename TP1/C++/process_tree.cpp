#include <iostream>
#include <sstream> // used for std::thread::id to const char*
#include <thread>

/*
Trabajo Práctico N° 1- Parte1
Procesos Pesados

Todos los procesos incluido el principal (A), informarán por pantalla su letra correspondiente al 
gráfico, su identificador de proceso (PID) y el PID de su padre. En cuanto a la creación, todos los 
procesos hijos deberán crearse con el enfoque de programación concurrente, es decir NO sería una 
solución válida crear un proceso y esperar a que éste finalice para crear el siguiente.
Nota: Pausar o retrasar la finalización del programa para que el equipo docente pueda verificar la
correcta creación del árbol
*/

// Level 0
#define ROOT_NODE_NAME "A"

// Level 1
#define LEFT_NODE_NAME "B"
#define RIGHT_NODE_NAME "C"

// Level 2
#define LEFT_LEFT_NODE_NAME "D"
#define LEFT_RIGHT_NODE_NAME "E"
#define RIGHT_RIGHT_NODE_NAME "F"

// Level 3
#define LEFT_RIGHT_LEFT_NODE_NAME "G"
#define LEFT_RIGHT_RIGHT_NODE_NAME "H"

const char * convert(std::thread::id id){
    std::ostringstream oss;
    oss << id << std::endl;
    return oss.str().c_str();
}

void show_node_info(const char* name, const char * id, const char * fatherId){
    std::cout<<"NODE "<<name<<" | pid="<<id<<" ppid="<<fatherId<<std::endl;
}

void node_function(const char* name, const char * fatherId){
    std::thread::id id = std::this_thread::get_id();
    show_node_info(name, convert(id), fatherId);
}

int main(){
    node_function(ROOT_NODE_NAME,"");
    return EXIT_SUCCESS;
}