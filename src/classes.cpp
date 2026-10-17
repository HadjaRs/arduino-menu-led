#include "classes.h"
#include <Arduino.h>


 Botao::Botao(int pinArduino)
  {
    pino = pinArduino;
    estadoAnterior = HIGH;
  }

  void Botao::begin()
  {
    pinMode(pino, INPUT_PULLUP);
  }

  bool Botao::pressionado()
  {
    int estadoBtAtual = digitalRead(pino);
    bool clicou = false;

    if (estadoAnterior == HIGH && estadoBtAtual == LOW)
    {
      delay(50); // Filtra o ruído inicial de descida

      // Se após 50ms ele AINDA continuar pressionado, confirmamos o clique!
      if (digitalRead(pino) == LOW)
      {
        clicou = true;
        delay(150); // Filtra o ruído ao soltar o botão
      }
    }

    estadoAnterior = estadoBtAtual;
    return clicou;
  };


Led::Led(int pinoArduino)
  {
    pino = pinoArduino;
    estado = false;
    piscando = false;
    tempoAnterior = 0;
  }

  void Led:: begin()
  {
    pinMode(pino, OUTPUT);
    desligar();
  }
  void Led::desligar()
  {
    digitalWrite(pino, LOW);
    estado = false;
    piscando = false;
  }
  void Led::ligar()
  {
    digitalWrite(pino, HIGH);
    estado = true;
    piscando = false;
  }

  void Led::iniciarPiscar()
  {
    piscando = true;
  }

  void Led::atualizar()
  {
    if (piscando)
    {
      unsigned long tempoAtual = millis();
      if (tempoAtual - tempoAnterior >= 500)
      {
        tempoAnterior = tempoAtual;
        estado = !estado;
        digitalWrite(pino, estado);
      }
    }
  }
