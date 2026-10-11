#include "functions.h"

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

void configs()
{
  switch (config)
  {
  case 1:
    espaco();
    Serial.println("> LIGAR");
    Serial.println("DESLIGAR");
    Serial.println("PISCAR");
    break;
  case 2:
    espaco();
    Serial.println("LIGAR");
    Serial.println("> DESLIGAR");
    Serial.println("PISCAR");
    break;
  case 3:
    espaco();
    Serial.println("LIGAR");
    Serial.println("DESLIGAR");
    Serial.println("> PISCAR");
    break;
  }
}