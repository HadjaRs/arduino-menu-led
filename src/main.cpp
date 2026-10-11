#include <Arduino.h>
#include "classes.h"
#include "functions.h"

Botao btesquerda(2);
Botao btconfirmar(3);
Botao btdireita(4);

int menu = 1;
int opcao = 1;
int config = 1;

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

  if (menu == 1)
  {

    if (btesquerda.pressionado())
    {
      opcao--;
      if (opcao < 1)
      {
        opcao = 3;
      }
      Serial.println("ESQUERDA");
      opcoes();
    }

    if (btdireita.pressionado())
    {
      opcao++;
      if (opcao > 3)
      {
        opcao = 1;
      }
      Serial.println("DIREITA");
      opcoes();
    }

    if (btconfirmar.pressionado())
    {
      menu = 2;
      configs();
    }
  }

  if (menu == 2)
  {

    if (btdireita.pressionado())
    {
      config++;
      if (config > 3)
      {
        config = 1;
      }
      configs();
    }

    if (btesquerda.pressionado())
    {
      config--;
      if (config < 1)
      {
        config = 3;
      }
      configs();
    }
  }
}