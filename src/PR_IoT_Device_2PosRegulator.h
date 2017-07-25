#ifndef PR_IoT_Device_2PosRegulator_h
#define PR_IoT_Device_2PosRegulator_h

    #include <arduino.h>
    #include <PR_IoT.h>
	
	#include "PR_2PosRegulator.h"

class PR_IoT_2PosRegulator : public PR_IoT_DeviceClass {
        public:
            PR_IoT_2PosRegulator(String name) : PR_IoT_DeviceClass(name) { }
			~PR_IoT_2PosRegulator()	{	delete regulator; regulator = NULL; }
            
            virtual void 	announce();			//overloaded here from base class
            void 	update();
			
            void 	inMsgCallback(); 
			virtual void	loopHW();		// do regulation in loopHW()
            
			void 	setupHW( uint8_t pin, bool onValue, float hysteresysL, float hysteresysH, uint16_t freqLimitationMS = 0);    
			void 	setupHW1( float (*pfunc)() )			{ 	_pfunc = pfunc; 		}	//we can take a value from some other device
			void 	setCurrentValue(float v) 				{	_currentValue = v;	} 	//interface to set value 
			void 	setTargetValue(float v) 				{	_setValue = v;		} 	//interface to set value 
			float 	getTargetValue() 						{	return _setValue;		} 	//interface to set value 
			bool	getOutput()								{	return regulator->getOutput(); }
			
        protected:
		
			bool	_offValue;				// false means DEenergiesed is LOW
			uint8_t	_pin;
			
			float	_setValue 		= 26;
			float	_currentValue 	= 0;		
			PR_2PosRegulator	*regulator;
			
			float	(*_pfunc)(void)	= NULL;
			void	requestCurrentValue()	{	if ( _pfunc != NULL ) _currentValue = (*_pfunc)(); 		}
			
		    void 	_setOutput();
    };
	
#endif