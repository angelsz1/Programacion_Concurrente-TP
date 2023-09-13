#include "process_three.h"
#include <iostream>
#include <sstream> // used for std::thread::id to const char*
#include <thread>
#include <cstring> // strcmp

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

int main(){
    node_function(ROOT_NODE,"");
    return EXIT_SUCCESS;
}

void node_function(Node node, const char * father_id){
    std::thread::id thread_id = std::this_thread::get_id();
    show_node_info(node, thread_id, father_id);

    evaluate_to_create_nodes(node);
}

const char* get_node_name(Node node){
    const char* name = "";
    switch (node)
    {
    case ROOT_NODE: name = ROOT_NODE_NAME; break;
    case LEFT_NODE: name = LEFT_NODE_NAME; break;
    case RIGHT_NODE: name = RIGHT_NODE_NAME; break;
    case LEFT_LEFT_NODE: name = LEFT_LEFT_NODE_NAME; break;
    case LEFT_RIGHT_NODE: name = LEFT_RIGHT_NODE_NAME; break;
    case RIGHT_RIGHT_NODE: name = RIGHT_RIGHT_NODE_NAME; break;
    case LEFT_RIGHT_LEFT_NODE: name = LEFT_RIGHT_LEFT_NODE_NAME; break; 
    case LEFT_RIGHT_RIGHT_NODE: name = LEFT_RIGHT_RIGHT_NODE_NAME; break;
    default:
        break;
    }
    return name;
}

void show_node_info(Node node, std::thread::id thread_id, const char * father_id){
    const char* name = get_node_name(node);
    const char* id = convert(thread_id);
    std::cout<<"NODE "<<name<<" | pid="<<thread_id<<" ppid="<<father_id<<std::endl;
}

void evaluate_to_create_nodes(Node node){

    bool has_left = false, has_right = false;
    Node new_node_left;
    Node new_node_right;

    std::thread::id thread_id = std::this_thread::get_id();
    const char* id = convert(thread_id);

    switch (node)
    {
    case ROOT_NODE:
        new_node_left = LEFT_NODE; has_left = true;
        new_node_right = RIGHT_NODE; has_right = true;
        break;

    case LEFT_NODE:
        new_node_left = LEFT_LEFT_NODE; has_left = true;
        new_node_right = LEFT_RIGHT_NODE; has_right = true;
        break;
    
    case RIGHT_NODE:
        new_node_right = RIGHT_RIGHT_NODE; has_right = true;
        break;
        
    case LEFT_RIGHT_NODE:
        new_node_left = LEFT_RIGHT_LEFT_NODE; has_left = true;
        new_node_right = LEFT_RIGHT_RIGHT_NODE; has_right = true;
        break;

    default:
        break;
    }
    
    if (has_left)
    {
        std::thread thread_node_left(node_function, new_node_left, id);
        thread_node_left.join();
    }
    if (has_right)
    {
        std::thread thread_node_right(node_function, new_node_right, id);
        thread_node_right.join();
    }
}

const char * convert(std::thread::id id){
    std::stringstream ss;
    ss << id;
    return ss.str().c_str();
}