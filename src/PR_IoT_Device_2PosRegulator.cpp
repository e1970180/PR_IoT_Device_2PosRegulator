#include "PR_IoT_Device_2PosRegulator.h"

    #include <arduino.h>    

	void PR_IoT_2PosRegulator::setupHW(uint8_t pin, bool onValue, float hysteresysL, float hysteresysH, uint16_t freqLimitationMS) {

		regulator = new PR_2PosRegulator();
		regulator->setup(hysteresysL, hysteresysH, freqLimitationMS);
		_pin = pin;
		_offValue = !onValue;
		pinMode(_pin, OUTPUT);
		_relay();	
	}
	
	void PR_IoT_2PosRegulator::announce() {
		postMsg("2PosRegulator", "HELLO"); 
	}
	
	void	PR_IoT_2PosRegulator::loopHW() {
		requestCurrentValue();
		regulator->loop( _setValue, _currentValue );
		_relay();
	}
	
	void PR_IoT_2PosRegulator::inMsgCallback() {
		
		if (inMsg.deviceTopic == "SET")	{			//set targetValue
			_setValue = inMsg.payload.toFloat();
					Serial.println(_setValue);
		}

	}
	
