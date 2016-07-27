#include "GadgetManager.h"

GadgetManager * GadgetManager::singleton = new GadgetManager();

void GadgetManager::registerServo( ServoMotor * servo ) {
    ServoMotor * oldHead = singleton->servoList;
    singleton->servoList = servo;
    servo->next = oldHead;
}

void GadgetManager::freePins(int pins[], int number ) {
    modifyPins( pins, number, true );
}

void GadgetManager::reenablePins(int pins[], int number ) {
    modifyPins( pins, number, false);
}

void GadgetManager::modifyPins(int pins[], int number, bool shouldFree ) {
    for( int i = 0; i < number; i++ ) {
        switch( pins[i] ) {
            // ServoPins
            case 9:
              modifyServo( shouldFree) ;
              break;
            case 10:
              modifyServo( shouldFree) ;
              break;
        }
    }
}

void GadgetManager::modifyServo(bool shouldBlock) {
    ServoMotor * servo = singleton->servoList;
    // If the servo exists and
    // If we are trying to block our servos and
    // If our servos are already blocked
    // Then exit the function
    if( servo != 0 && shouldBlock && (servo->state & BLOCKED)) return; 
    while( servo != 0 ) {
        shouldBlock ?
        servo->block()  :
        servo->enable() ;
        servo = servo->next;
    }
}
