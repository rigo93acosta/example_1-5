#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    DigitalIn enterButton(BUTTON1);
    DigitalIn gasDetector(D2);
    //DigitalIn overTempDetector(D3);
    DigitalIn aButton(D5);
    DigitalIn bButton(D6);
    DigitalIn cButton(D7);
    //DigitalIn dButton(D7);

    DigitalOut alarmLed(LED2);

    DigitalOut incorrectCodeLed(D4);
    DigitalOut systemBlockedLed(D8);

    gasDetector.mode(PullDown);
    //overTempDetector.mode(PullDown);
    aButton.mode(PullDown);
    bButton.mode(PullDown);
    cButton.mode(PullDown);
    //dButton.mode(PullDown);

    alarmLed = OFF;
    incorrectCodeLed = OFF; //Azul
    systemBlockedLed = OFF; //Rojo

    bool alarmState = OFF;
    int numberOfIncorrectCodes = 0;

    while (true) {

        if ( gasDetector) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        //enterButton (BUTTON1) diferente al libro
        /*if (!enterButton){
            alarmState = OFF;
            alarmLed = OFF;
        }*/
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
}