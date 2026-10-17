# 🎛️ Dashboard Web Serial — Controle de LEDs com Arduino

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)](https://developer.mozilla.org/pt-BR/docs/Web/JavaScript)
[![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)](https://developer.mozilla.org/pt-BR/docs/Web/HTML)
[![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white)](https://developer.mozilla.org/pt-BR/docs/Web/CSS)
[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)

Interface web interativa e responsiva desenvolvida para controle bidirecional de LEDs acoplados a um **Arduino** através da **Web Serial API**. O projeto conta com um sistema de menu navegável tanto por **botões físicos na protoboard** quanto por **botões virtuais na tela**.

---

## 🚀 Funcionalidades

- 🔌 **Conexão Direta via Web Serial API:** Comunicação Serial rápida a 9600 baud sem necessidade de servidores intermediários (Node.js).
- 🔄 **Navegação Bidirecional de Menus:**
  - **Menu 1:** Seleção do alvo (`LED 1`, `LED 2` ou `AMBAS`).
  - **Menu 2:** Seleção da ação (`LIGAR`, `DESLIGAR` ou `PISCAR`).
- 💡 **Animação Não-Bloqueante (`millis`):** Controle individual de pisca-pisca contínuo sem travamento da execução via `delay()`.
- 🕹️ **Sincronia Físico-Digital:** Botões na tela reagem com feedback visual (*efeito ativo/pressionado*) quando os botões físicos da protoboard são acionados.
- 🛡️ **Debounce Inteligente:** Lógica de tratamento de ruído de botões integrada em C++.

---

## 🛠️ Tecnologias e Ferramentas

| Tecnologia | Descrição |
| :--- | :--- |
| **Arduino (C++)** | Firmware modular estruturado com Programação Orientada a Objetos (Classes `Led` e `Botao`). |
| **Web Serial API** | Manipulação do fluxo serial com `TextDecoder`, `TextEncoder` e tratamento de buffer por quebra de linha. |
| **HTML5 & CSS3** | Dashboard estilizado no formato *Dark Theme Neon/OLED* responsivo. |
| **Git & GitHub** | Controle de versão utilizando fluxo de trabalho baseado em *feature branches*. |

---

## 🧰 Componentes de Hardware

- 1x Placa Arduino Uno / Nano
- 2x LEDs (Verde / Vermelho ou a escolha)
- 2x Resistores para os LEDs (100Ω a 220Ω)
- 3x Push Buttons (Esquerda, Confirmar, Direita)
- Protoboard e Jumpers de conexão

---

## 🔌 Esquema de Ligação (Pinos)

| Componente | Pino no Arduino | Modo |
| :--- | :---: | :---: |
| **Botão Esquerda** | `Pino 2` | `INPUT_PULLUP` |
| **Botão Confirmar** | `Pino 3` | `INPUT_PULLUP` |
| **Botão Direita** | `Pino 4` | `INPUT_PULLUP` |
| **LED 1** | `Pino 5` | `OUTPUT` |
| **LED 2** | `Pino 6` | `OUTPUT` |

---

## 💻 Como Executar o Projeto

### 1. Gravar o Firmware no Arduino
1. Abra a pasta do firmware no **VS Code** com a extensão **PlatformIO** (ou utilize a Arduino IDE).
2. Conecte o Arduino na porta USB do seu computador.
3. Compilar e fazer o upload do código (`src/main.cpp`).

### 2. Rodar a Interface Web
1. Abra o arquivo `data/index.html` em um navegador compatível (Google Chrome, Microsoft Edge ou Opera).
2. Clique no botão **"Conectar Arduino"**.
3. Selecione a porta Serial referente ao seu Arduino e clique em **Conectar**.
4. Interaja utilizando os botões da tela ou os botões físicos da sua bancada!

---

## 📂 Estrutura do Repositório

```text
├── data/
│   ├── index.html     # Estrutura do Dashboard
│   ├── style.css      # Estilização Dark/Neon e animações
│   └── script.js      # Lógica Web Serial API e controle de menu
├── include/
│   ├── classes.h      # Declaração das classes Led e Botao
│   └── functions.h    # Funções auxiliares
├── src/
│   ├── classes.cpp    # Implementação POO em C++
│   └── main.cpp       # Setup e Loop do Arduino
└── README.md          # Documentação do projeto