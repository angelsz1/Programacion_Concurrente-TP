#ifndef FILENAME_H
#define FILENAME_H

enum Node {
// Level 0
ROOT_NODE,
// Level 1
LEFT_NODE,
RIGHT_NODE,
// Level 2
LEFT_LEFT_NODE,
LEFT_RIGHT_NODE,
RIGHT_RIGHT_NODE,
// Level 3
LEFT_RIGHT_LEFT_NODE,
LEFT_RIGHT_RIGHT_NODE,
};

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


// Functions
void node_function(Node node, pid_t * father_id);
void show_node_info(Node node,pid_t thread_id,  pid_t * father_id);
void evaluate_to_create_nodes(Node node);
const char* get_node_name(Node node);

#endif