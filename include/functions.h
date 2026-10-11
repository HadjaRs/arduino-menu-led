#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

// O 'extern' avisa ao compilador que essas variáveis foram criadas no main.cpp
extern int opcao;
extern int config;

// Protótipos das funções
void espaco();
void opcoes();
void configs();

#endif