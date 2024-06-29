#include "mbed.h"
#include "arm_book_lib.h"

// =====[Declaration and initialization of public global objects]=============
DigitalIn enterButton(BUTTON1);
DigitalIn gasDetector(D2);
DigitalIn aButton(D5);
DigitalIn bButton(D6);
DigitalIn cButton(D7);
DigitalOut alarmLed(LED2);
DigitalOut incorrectCodeLed(D4);
DigitalOut systemBlockedLed(D8);

// =====[Declaration and initialization of public global variables]=============
bool alarmState = OFF;
int numberOfIncorrectCodes = 0;

// ====[Declaration functions]
void inputsInit();
void outputsInit();

void alarmActivationUpdate();
void alarmDeactivationUpdate();


int main()
{
    inputsInit();
    outputsInit();
    while (true) {

        alarmActivationUpdate();
        alarmDeactivationUpdate();
        //enterButton (BUTTON1) diferente al libro
        /*if (!enterButton){
            alarmState = OFF;
            alarmLed = OFF;
        }*/

    }
}

void inputsInit(){
    gasDetector.mode(PullDown);
    aButton.mode(PullDown);
    bButton.mode(PullDown);
    cButton.mode(PullDown);
}

void outputsInit(){
    alarmLed = OFF;
    incorrectCodeLed = OFF; //Azul
    systemBlockedLed = OFF; //Rojo
}

void alarmActivationUpdate(){
    if ( gasDetector) {
        alarmState = ON;
    }

    alarmLed = alarmState;
}

void alarmDeactivationUpdate(){
    if ( numberOfIncorrectCodes < 3 ) {
        
        if ( aButton && bButton && cButton && enterButton) { //Desbloquer
            incorrectCodeLed = OFF;
        }

        if (!incorrectCodeLed && !enterButton && alarmState) {
            if ( aButton && bButton && !cButton) { //Codigo desbloqueo
                alarmState = OFF;
                numberOfIncorrectCodes = 0;
            } else {
                incorrectCodeLed = ON;
                numberOfIncorrectCodes = numberOfIncorrectCodes + 1;
            }
        }
    } else {
        systemBlockedLed = ON;
    }
}