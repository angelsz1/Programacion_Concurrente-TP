#include "process_tree.h"
#include <iostream>
#include <sstream> // used for ostringstream
#include <unistd.h> //fork
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
  node_function(ROOT_NODE);
  return EXIT_SUCCESS;
}

void node_function(Node node)
{
  show_node_info(node);
  evaluate_to_create_nodes(node);
}

void show_node_info(Node node)
{
  const char* name = get_node_name(node);
  std::ostringstream oss;
  oss << "\nNODE " << name << " \tpid=" << getpid() << " \tppid=" << getppid() << "\n";
  std::cout<<oss.str();
}

const char* get_node_name(Node node)
{
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
    default: break;
  }
  return name;
}

void evaluate_to_create_nodes(Node node)
{
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

  if (has_left)
  {
    pid_t pid_left = fork();
    if (pid_left < 0)
    {
      std::cerr << "No se pudo crear el proceso.\n";
      exit(EXIT_FAILURE);
    }
    else if (pid_left == 0)
    {
      node_function(new_node_left); // soy proceso hijo
      exit(EXIT_SUCCESS);
    }
  }

  if (has_right)
  {
    pid_t pid_right = fork();
    if (pid_right < 0)
    {
      std::cerr << "No se pudo crear el proceso.\n";
      exit(EXIT_FAILURE);
    }
  else if (pid_right == 0)
    {
      node_function(new_node_right); // soy proceso hijo
      exit(EXIT_SUCCESS);
    }            
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