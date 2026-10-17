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

class Led
{
private:
  int pino;
  bool estado;
  bool piscando;
  unsigned long tempoAnterior;

public:
  Led(int pinoArduino);

  void begin();
  void desligar();
  void ligar();
  void iniciarPiscar();

  void atualizar();
};

#endif