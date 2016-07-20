#ifndef TMP36_H
#define TMP36_H

#include <Arduino.h>

class TMP36
{
	int _pin;
public:
	TMP36(int pin) {
		_pin = pin;
	};

	float readTemperatureC(float ref_voltage) {
        int tempReading = analogRead(_pin);  
        float voltage = tempReading * ref_voltage;
        voltage /= 1024.0;

        float temperatureC = (voltage - 0.5) * 100;
        return temperatureC;
	}

	float readTemperatureF(float ref_voltage) {
		float temperatureC = readTemperatureC(ref_voltage);
		float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
		return temperatureF;
	}
	
};

#endif