#include "classes.h"


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
  }
