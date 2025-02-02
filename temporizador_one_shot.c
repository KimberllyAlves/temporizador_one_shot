#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

#define LED_PIN_Y 11    // Define o pino GPIO 11 para controlar o LED Amarelo.
#define LED_PIN_G 12    // Define o pino GPIO 11 para controlar o LED Verde.
#define LED_PIN_R 13    // Define o pino GPIO 11 para controlar o LED Vermelho.

const uint BUTTON_PIN = 5;  // Define o pino GPIO 5 para ler o estado do botão.

int led_on = 0;        // Variável global para armazenar o estado do LED (não utilizada neste código).
bool led_active = false;    // Indica se o LED está atualmente aceso (para evitar múltiplas ativações).

// Função de callback para desligar o LED após o tempo programado.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {

    //Led vermelho desligado
    if (led_on == 0) {
        gpio_put(LED_PIN_R, false);
        led_on = 1;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Agenda o próximo desligamento
    }
    //Led amarelo desligado
    else if (led_on ==1 ) {
        gpio_put(LED_PIN_Y, false);
        led_on = 2;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Agenda o próximo desligamento
    }
    else {
        gpio_put(LED_PIN_G, false);
        led_on = 0;
        // Atualiza o estado de 'led_active' para falso, indicando que o LED está desligado.
        led_active = false;
    }

    return 0;
}

int main() {

    // Inicializa a comunicação serial para permitir o uso de printf.
    stdio_init_all();

    // Configura os pinos dos LEDS como saída digital.
    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R,GPIO_OUT);
    gpio_init(LED_PIN_Y);
    gpio_set_dir(LED_PIN_Y,GPIO_OUT);
    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G,GPIO_OUT);


    // Configura o pino BUTTON_PIN (5) como entrada digital.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Habilita o resistor pull-up interno para o pino do botão.
    gpio_pull_up(BUTTON_PIN);

    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true) {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                // Define 'led_active' como true para indicar que o LED está aceso.
                led_active = true;
                //Ativando todos os leds
                gpio_put(LED_PIN_R, true);
                gpio_put(LED_PIN_Y, true);
                gpio_put(LED_PIN_G, true);
                // Agenda um alarme para desligar o LED após 3 segundos (3000 ms).
                // A função 'turn_off_callback' será chamada após esse tempo.
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }

        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
        sleep_ms(10);
    }
    
    return 0;
}
