#include "car.h"

Car car(7,4,3,8,9,10);
void setup()
{
    
}

void loop(){
    car.forward();
    delay(1000);
    car.stop();
    delay(1000);

    car.backward();
    delay(1000);
    car.stop();
    delay(1000);

    car.turnRight();
    delay(1000);
    car.stop();
    delay(1000);

    car.turnLeft();
    delay(1000);
    car.stop();
    delay(1000);

}