# Temporizador One Shot com Raspberry Pi Pico W ⏱️

Este projeto implementa um **temporizador de um disparo (One Shot)** usando o microcontrolador **Raspberry Pi Pico W**, três LEDs (vermelho, amarelo e verde), um botão (pushbutton) e resistores de 330 Ω. O código foi desenvolvido em C utilizando o **Pico SDK**.

## 📋 Descrição do Projeto

O sistema aciona três LEDs de forma sequencial a partir do clique em um botão:
- Ao pressionar o **botão**, todos os LEDs acendem simultaneamente.
- Após **3 segundos**, o LED vermelho 🔴 se apaga.
- Após mais **3 segundos**, o LED amarelo 🟡 se apaga.
- Finalmente, após mais **3 segundos**, o LED verde 🟢 se apaga.

Durante o ciclo de temporização, o botão não pode iniciar uma nova sequência, garantindo um controle eficiente do sistema.

## 🚀 Requisitos

- Microcontrolador: Raspberry Pi Pico W
- Placa de Desenvolvimento: BitDogLab (opcional)
- Conta Criada no Wokwi Simulator
- Editor de Código: Visual Studio Code (VS Code)
- SDK do Raspberry Pi Pico configurado no sistema
- Ferramentas de build: CMake e Ninja

## 🔌 Conexões dos GPIOs

| Componente | Cor       | GPIO |
|------------|-----------|------|
| LED        | 🔴 Vermelho | 13   |
| LED        | 🟡 Amarelo  | 11   |
| LED        | 🟢 Verde    | 12   |
| Botão      | -         | 5    |

## ⚙️ Funcionamento do Código

1. **Inicialização:**
   - Configura os pinos dos LEDs como saída.
   - Configura o pino do botão como entrada com pull-up interno.
   - Inicia a comunicação serial com `stdio_init_all()`.

2. **Controle de Temporização:**
   - O `add_alarm_in_ms()` é usado para alternar o estado dos LEDs com um atraso de 3 segundos entre cada mudança.
   - O sistema utiliza funções de *callback* para gerenciar o desligamento dos LEDs.

3. **Debounce do Botão:**
   - Implementa um atraso de 50 ms para atenuar o efeito *bouncing*.

4. **Loop Principal:**
   - Verifica o estado do botão e inicia o ciclo de temporização apenas quando todos os LEDs estiverem desligados.

## 📦 Como Usar

### 1. Instalar o Visual Studio Code
- Acesse o site oficial e faça o download: [Visual Studio Code](https://code.visualstudio.com/).
- Instale o programa e configure conforme necessário.
- Adicione a extensão [Wokwi](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode) para simular o hardware.

### 2. Instalar as Dependências
As extensões recomendadas são:
- C/C++ (Microsoft)
- CMake Tools
- Wokwi Simulator
- Raspberry Pi Pico

### 3. Clonar o Repositório
Clone o repositório para o seu computador:
[https://github.com/KimberllyAlves/temporizador_one_shot.git](https://github.com/KimberllyAlves/temporizador_one_shot.git)

### 4. Testar no Hardware Real
- Conecte a placa ao computador no modo BOOTSEL
- Compile o projeto no VS Code utilizando a extensão do Raspberry Pi Pico W
- Execute o projeto clicando em "Run Project USB"

## 🧪 Simulação

Você pode testar o código usando o **Wokwi** integrado ao **VS Code** para simular o comportamento dos LEDs conectados aos GPIOs 11, 12 e 13.

**Desenvolvido por [Kimberlly Alves](https://github.com/KimberllyAlves) ❤️**

