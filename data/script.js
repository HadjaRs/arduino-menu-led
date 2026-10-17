const conectar = document.getElementById("conectar");
const led1 = document.getElementById("led1");
const led2 = document.getElementById("led2");
const both = document.getElementById("both");

const esquerda = document.getElementById("esquerda");
const direita = document.getElementById("direita");
const confirmar = document.getElementById("confirmar");

let porta;
let escritor;
let leitor;

let opcao = 1;
let menu = 1;
let config = 1;

function piscarBotao(elemento) {
  if (elemento) {
    elemento.classList.add("ativo");
    setTimeout(function () {
      elemento.classList.remove("ativo");
    }, 200);
  }
}

function atualizarMenu() {
  if (menu == 1) {
    if (opcao == 1) {
      led1.innerText = "> LED 1";
      led2.innerText = "LED 2";
      both.innerText = "AMBAS";
    }
    if (opcao == 2) {
      led1.innerText = "LED 1";
      led2.innerText = "> LED 2";
      both.innerText = "AMBAS";
    }
    if (opcao == 3) {
      led1.innerText = "LED 1";
      led2.innerText = "LED 2";
      both.innerText = "> AMBAS";
    }
  }
  if (menu == 2) {
    if (config == 1) {
      led1.innerText = "> LIGAR";
      led2.innerText = "DESLIGAR";
      both.innerText = "PISCAR";
    } else if (config == 2) {
      led1.innerText = "LIGAR";
      led2.innerText = "> DESLIGAR";
      both.innerText = "PISCAR";
    } else if (config == 3) {
      led1.innerText = "LIGAR";
      led2.innerText = "DESLIGAR";
      both.innerText = "> PISCAR";
    }
  }
}

// Monta o comando final do LED e envia via Serial
async function enviarComando() {
  let comando = "";

  if (opcao == 1) comando = "LED1_";
  if (opcao == 2) comando = "LED2_";
  if (opcao == 3) comando = "AMBAS_";

  if (config == 1) comando += "LIGAR\n";
  if (config == 2) comando += "DESLIGAR\n";
  if (config == 3) comando += "PISCAR\n";

  if (escritor) { //verifica se a conexão serial está pronta antes de enviar o comando
    const codificar = new TextEncoder(); //transforma o comando texto em bytes para enviar via Serial
    await escritor.write(codificar.encode(comando)); // espera a escrita do comando na porta serial
    console.log("--> Comando enviado para o Arduino:", comando);
  } else {
    console.log("Erro: Conexão Serial com Arduino não está pronta.");
  }
}

conectar.onclick = async function () {
  try { // tudo que estiver dentro do try será executado, caso ocorra algum erro, o catch será acionado
    porta = await navigator.serial.requestPort(); // abre a janela de seleção de porta serial do navegador
    await porta.open({ baudRate: 9600 }); // abre a porta serial com a taxa de transmissão de 9600 bps
    conectar.innerText = "Conectado!";

    escritor = porta.writable.getWriter(); // para enviar dados para o Arduino, é necessário criar um escritor (writer) da porta serial
    leitor = porta.readable.getReader(); // para receber dados do Arduino, é necessário criar um leitor (reader) da porta serial

    const decodificar = new TextDecoder(); // converte os bytes recebidos do Arduino em texto legível
    let buffer = "";

    while (true) {
      try {
        const { value, done } = await leitor.read(); // value é o dado recebido do Arduino, done indica se a leitura foi concluída
        if (done) break; // se a leitura foi concluída, sai do loop

        buffer += decodificar.decode(value); // faz a decodificação do valor recebido e adiciona ao buffer
        const linhas = buffer.split("\n"); //
        buffer = linhas.pop(); //

        for (let texto of linhas) { // percorre cada linha recebida do Arduino
          texto = texto.trim();

          // Botão Físico DIREITA
          if (texto.includes("DIREITA")) { // se o texto recebido do Arduino contém a palavra "DIREITA", significa que o botão físico DIREITA foi pressionado
            piscarBotao(direita);
            if (menu == 1) {
              opcao++;
              if (opcao > 3) opcao = 1;
            } else if (menu == 2) {
              config++;
              if (config > 3) config = 1;
            }
            atualizarMenu();
          }

          // Botão Físico ESQUERDA
          if (texto.includes("ESQUERDA")) {
            piscarBotao(esquerda);
            if (menu == 1) {
              opcao--;
              if (opcao < 1) opcao = 3;
            } else if (menu == 2) {
              config--;
              if (config < 1) config = 3;
            }
            atualizarMenu();
          }

          // Botão Físico CONFIRMAR
          if (texto.includes("CONFIRMAR")) {
            piscarBotao(confirmar);

            if (menu == 1) {
              menu = 2;
              config = 1;
            } else if (menu == 2) {
              await enviarComando(); // Manda o comando para acionar o LED
              menu = 1;
            }
            atualizarMenu();
          }
        }
      } catch (erroLeitura) { // caso ocorra algum erro na leitura dos dados do Arduino, o catch será acionado
        console.log("Erro na leitura de dados:", erroLeitura);
        break;
      }
    }
  } catch (erroConexao) { // caso ocorra algum erro na conexão com o Arduino, o catch será acionado
    console.log("Erro ao conectar ou porta desconectada:", erroConexao);
  } finally { // serve para garantir que o código dentro dele será executado mesmo que ocorra um erro no try ou catch
    // Desbloqueia as portas ao desconectar para permitir reconexão sem travar
    if (leitor) leitor.releaseLock(); // libera o bloqueio do leitor da porta serial, permitindo que outros leitores possam ser criados
    if (escritor) escritor.releaseLock(); // libera o bloqueio do escritor da porta serial, permitindo que outros escritores possam ser criados
    if (porta) await porta.close(); // fecha a porta serial, liberando-a para outras aplicações
    conectar.innerText = "Conectar Arduino";
  }
};

// Cliques do Mouse na Tela (Navegação na interface web)
confirmar.onclick = async function () {
  piscarBotao(confirmar);
  if (menu == 1) {
    menu = 2;
    config = 1;
  } else if (menu == 2) {
    await enviarComando();
    menu = 1;
  }
  atualizarMenu();
};

direita.onclick = function () {
  piscarBotao(direita);
  if (menu == 1) {
    opcao++;
    if (opcao > 3) opcao = 1;
  } else if (menu == 2) {
    config++;
    if (config > 3) config = 1;
  }
  atualizarMenu();
};

esquerda.onclick = function () {
  piscarBotao(esquerda);
  if (menu == 1) {
    opcao--;
    if (opcao < 1) opcao = 3;
  } else if (menu == 2) {
    config--;
    if (config < 1) config = 3;
  }
  atualizarMenu();
};