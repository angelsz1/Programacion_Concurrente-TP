#include "process_three.h"
#include <iostream>
#include <sstream> // used for ostringstream
#include <unistd.h> //fork
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

Node currentNode = ROOT_NODE;

int main(){
    node_function(ROOT_NODE,nullptr);
    return EXIT_SUCCESS;
}

void node_function(Node node, pid_t * father_id){
    pid_t process_id = getpid();
    show_node_info(node, process_id, father_id);

    evaluate_to_create_nodes(node);
}

void show_node_info(Node node, pid_t thread_id, pid_t * father_id){
    const char* name = get_node_name(node);

    std::ostringstream oss;
    oss << "\nNODE " << name << " \tpid=" << thread_id << " \tppid=";
    
    if (father_id != nullptr) {
        oss << *father_id;
    } else {
        oss << "-";
    }

    std::cout<<oss.str();
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

void evaluate_to_create_nodes(){
    bool has_left = false, has_right = false;

    Node new_node_left;
    Node new_node_right;

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

    pid_t id = getpid();
    
    if (has_left)
    {
        pid_t pid_left = fork();
        if (pid <= 0)
        {
            std::cerr << "No se pudo crear el proceso.\n";
            exit(EXIT_FAILURE);
        }
        node_function(new_node_left, &id);
    };
    if (has_right)
    {
        pid_t pid_right = fork();
        if (pid <= 0)
        {
            std::cerr << "No se pudo crear el proceso.\n";
            exit(EXIT_FAILURE);
        }
        node_function(new_node_right, &id);
    }
    
    if (has_left)
    {
        wait(NULL);
    }
    if (has_right)
    {
        wait(NULL);
    }
}