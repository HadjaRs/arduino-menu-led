#include <Arduino.h>

class Botao
{
private:
  int pino;

public:
  Botao(int pinArduino)
  {
    pino = pinArduino;
  }

  void begin()
  {
    pinMode(pino, INPUT_PULLUP);
  }

  bool pressionado()
  {
    if (digitalRead(pino) == LOW)
    {
      while (digitalRead(pino) == LOW)
      {
      }
      delay(100);
      return true;
    }
    return false;
  }
};

Botao btesquerda(2);
Botao btconfirmar(3);
Botao btdireita(4);

int opcao = 1;

void espaco()
{
  for (int i = 0; i < 20; i++)
  {
    Serial.println("");
  }
}

void opcoes()
{
  switch (opcao)
  {
  case 1:
    espaco();
    Serial.println("> LED 1");
    Serial.println("LED 2");
    Serial.println("AMBAS");
    break;
  case 2:
    espaco();
    Serial.println("LED 1");
    Serial.println("> LED 2");
    Serial.println("AMBAS");
    break;
  case 3:
    espaco();
    Serial.println("LED 1");
    Serial.println("LED 2");
    Serial.println("> AMBAS");
    break;
  }
}

void setup()
{
  Serial.begin(9600);

  btesquerda.begin();
  btconfirmar.begin();
  btdireita.begin();

  Serial.println("> LED 1");
  Serial.println("LED 2");
  Serial.println("AMBAS");
}

void loop()
{
  if (btesquerda.pressionado())
  {
    opcao--;
    if (opcao < 1)
    {
      opcao = 3;
    }
    opcoes();
  }

  if (btdireita.pressionado())
  {
    opcao++;
    if (opcao > 3)
    {
      opcao = 1;
    }
    opcoes();
  }
}