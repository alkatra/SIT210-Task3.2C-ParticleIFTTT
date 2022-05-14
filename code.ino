#include "BH1750.h"
BH1750 sensor(0x23, Wire);
bool currentValue = false;
int luxc;
int timer;

void setup()
{
      sensor.begin();
    
      sensor.set_sensor_mode(BH1750::forced_mode_high_res2);
    
      Serial.begin();
}

void loop()
{
    sensor.make_forced_measurement();

    luxc = sensor.get_light_level();
    timer++;
    if(luxc > 200 && currentValue == false) {
        currentValue = true;
        Particle.publish("Sunlight_Detected_After", String(timer));
        timer = 0;
    } else if(luxc <= 200 && currentValue == true) {
        currentValue = false;
        Particle.publish("Sunlight_Not_Detected_After", String(timer));
        timer = 0;
    }
    Particle.publish("Lux:",String(luxc));
    delay(1000);
}