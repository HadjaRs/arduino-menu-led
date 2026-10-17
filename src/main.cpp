#include <Arduino.h>
#include "classes.h"
#include "functions.h"

Botao btesquerda(2);
Botao btconfirmar(3);
Botao btdireita(4);
Led led1(5);
Led led2(6);

int menu = 1;
int opcao = 1;
int config = 1;

void setup()
{
  Serial.begin(9600);

  btesquerda.begin();
  btconfirmar.begin();
  btdireita.begin();
  led1.begin();
  led2.begin();
}

void loop()
{
  // 1. Atualiza o estado não-bloqueante dos LEDs (para o modo piscar com millis)
  led1.atualizar();
  led2.atualizar();

  // 2. LEITURA APENAS DOS COMANDOS DE AÇÃO DOS LEDS VINDOS DO JS
  if (Serial.available() > 0)
  {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    // Comandos do LED 1
    if (comando == "LED1_LIGAR")    led1.ligar();
    if (comando == "LED1_DESLIGAR") led1.desligar();
    if (comando == "LED1_PISCAR")   led1.iniciarPiscar();

    // Comandos do LED 2
    if (comando == "LED2_LIGAR")    led2.ligar();
    if (comando == "LED2_DESLIGAR") led2.desligar();
    if (comando == "LED2_PISCAR")   led2.iniciarPiscar();

    // Comandos de AMBAS
    if (comando == "AMBAS_LIGAR") {
      led1.ligar();
      led2.ligar();
    }
    if (comando == "AMBAS_DESLIGAR") {
      led1.desligar();
      led2.desligar();
    }
    if (comando == "AMBAS_PISCAR") {
      led1.iniciarPiscar();
      led2.iniciarPiscar();
    }
  }

  // 3. LEITURA DOS BOTÕES FÍSICOS (Sinaliza para a Página Web)
  if (menu == 1)
  {
    if (btesquerda.pressionado())
    {
      opcao--;
      if (opcao < 1) opcao = 3;
      Serial.println("ESQUERDA");
    }
    if (btdireita.pressionado())
    {
      opcao++;
      if (opcao > 3) opcao = 1;
      Serial.println("DIREITA");
    }
    if (btconfirmar.pressionado())
    {
      menu = 2;
      config = 1;
      Serial.println("CONFIRMAR");
    }
  }
  else if (menu == 2)
  {
    if (btdireita.pressionado())
    {
      config++;
      if (config > 3) config = 1;
      Serial.println("DIREITA");
    }
    if (btesquerda.pressionado())
    {
      config--;
      if (config < 1) config = 3;
      Serial.println("ESQUERDA");
    }
    if (btconfirmar.pressionado())
    {
      Serial.println("CONFIRMAR"); // Envia para a página Web processar a ação
      menu = 1; // Volta ao menu inicial
    }
  }
}