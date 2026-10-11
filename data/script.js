const conectar = document.getElementById("conectar");
const led1 = document.getElementById("led1");
const led2 = document.getElementById("led2");
const both = document.getElementById("both");

let porta;
let opcao = 1;
let menu = 1;

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

conectar.onclick = async function () {
  //espera abrir a janela de seleçao antes de ir pra prox linha
  porta = await navigator.serial.requestPort();
  //espera abrir a comunicação pela velocidade tal
  await porta.open({ baudRate: 9600 });
  conectar.innerText = "Conectado!";
  //puxa os dados da serial
  const leitor = porta.readable.getReader();
  //traduz os bytes que chegam em texto
  const decodificar = new TextDecoder();
  //para ir acumalando os pedaços que chegam na serial
  let buffer = "";

  while (true) {
    //espera receber pacote contendo o valor e o done caso tenha perdido a conexão
    const { value, done } = await leitor.read();
    if (done) break;
    //fica pegando o que chega e coloca em buffer
    buffer += decodificar.decode(value);
    //para de ler ate encontrar quebra de linha
    const linhas = buffer.split("\n");
    buffer = linhas.pop();

    for (let texto of linhas) {
      texto = texto.trim();

      if (texto.includes("DIREITA")) {
        if (menu == 1) {
          opcao++;
          if (opcao > 3) {
            opcao = 1;
          }
        }
        if (menu == 2) {
          config++;
          if (config > 3) {
            config = 1;
          }
        }
        atualizarMenu();
      }
    }
  }
};
