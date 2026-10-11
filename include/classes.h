#ifndef CLASSES_H
#define CLASSES_H

#include <Arduino.h>

class Botao
{
private:
  int pino;
  int estadoAnterior;

public:
  Botao(int pinArduino);

  void begin();
  bool pressionado();

  
};

#endif