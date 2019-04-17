/*
 *  UNISAL 2019 - Sistemas Operacionais Embarcados - Linux Embarcado
 *  Atividade - Controle de GPIO via Sysfs
 *  Lucas Tamborrino
 */

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include "gpioFileSys.h"


#define LED_PIN	23
#define BTN_PIN	25
#define DEBOUNCE    0.05 //s
#define LED_PERIOD  1 //s

volatile bool terminateSignal = false;

// Prototypes
void initPins();
void sigintHandler();
void ledHandler();
void btnHandler();
void UnexportAllPins();


int main(int argc, char *argv[])
{

    initPins();
    signal(SIGINT, sigintHandler); 

    while(!terminateSignal)
    {
        ledHandler();
        btnHandler();
    }

    UnexportAllPins();
    return 0;
}

void initPins()
{
    GPIOUnexport(LED_PIN);
    GPIOUnexport(BTN_PIN);

    GPIOExport(LED_PIN);
    GPIOExport(BTN_PIN);

    GPIODirection(LED_PIN, OUT);
    GPIODirection(BTN_PIN, IN);

}

void UnexportAllPins()
{
    GPIOUnexport(LED_PIN);
    GPIOUnexport(BTN_PIN);
}

void sigintHandler()
{
    terminateSignal = true;
    printf("\nTerminate\n");
}

void ledHandler()
{
    static clock_t old_led_time = 0;
    static bool led_state = false;

    if((float)((clock() - old_led_time)/CLOCKS_PER_SEC) >= LED_PERIOD)
    {
        led_state = !led_state;
        GPIOWrite(LED_PIN, led_state);
        old_led_time = clock();

        if(led_state)
        {
            printf("LED ACES0\n");
        }else{
            printf("LED APAGADO\n");
        }


    }
}

void btnHandler()
{
    static bool old_estado_botao;
    bool estado_botao;
    
    estado_botao = (GPIORead(BTN_PIN) == 0 ? true : false);

    // checa mudança de estado
    if(estado_botao != old_estado_botao)
    {   
        // Debouce do botão (~50ms)
        usleep(DEBOUNCE * 1000*1000);
        // borda de subida
        if(estado_botao)
        {
            printf("Botão Pressionado!\n");
        }else{ //borda de descida

        }

        old_estado_botao = estado_botao;
    }

}
