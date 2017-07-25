#include "PR_IoT_Device_2PosRegulator.h"

    #include <arduino.h>    

	void PR_IoT_2PosRegulator::setupHW(uint8_t pin, bool onValue, float hysteresysL, float hysteresysH, uint16_t freqLimitationMS) {

		regulator = new PR_2PosRegulator();
		regulator->setup(hysteresysL, hysteresysH, freqLimitationMS);
		_pin = pin;
		_offValue = !onValue;
		pinMode(_pin, OUTPUT);
		_setOutput();	
	}
	
	void	PR_IoT_2PosRegulator::announce()	{
		PR_IoT_DeviceClass::announce();
		postMsg("announce", "COMMAND=SET payload=temp; COMMAND=GET");
	}		
	

	void	PR_IoT_2PosRegulator::loopHW() {
		requestCurrentValue();
		regulator->loop( _setValue, _currentValue );
		_setOutput();
	}

	void	PR_IoT_2PosRegulator::update() {
		String	s;
		if ( regulator->getOutput() )	s = "ON"; else s = "OFF";
		postMsg ("output", s );
	}	
	
	void 	PR_IoT_2PosRegulator::_setOutput()	{	
		digitalWrite(_pin, regulator->getOutput() ^ _offValue);	 
	} 
	
	void PR_IoT_2PosRegulator::inMsgCallback() {
		
		if (inMsg.deviceTopic == "SET")	{			//set targetValue
			_setValue = inMsg.payload.toFloat();
		}
		
		if (inMsg.deviceTopic == "GET")	{			//set targetValue

			postMsg ("targetValue", String(_setValue, 2) );
			postMsg ("currentValue", String(_currentValue, 2) );
			update();
		}

	}
	
