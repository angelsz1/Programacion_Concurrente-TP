#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <unistd.h>

#define AMOUNT_PARAMETERS 2

void characterConverter(int);
void push_to_vec(int);
int handleMinus(char);
int convert();
int fromCharToInt(char);

#endif PASSWORD_GENERATOR_H // PASSWORD_GENERATOR_H
