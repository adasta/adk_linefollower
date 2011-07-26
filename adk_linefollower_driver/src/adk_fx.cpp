#include "ros_lib/serial_fx.h"
#include "AndroidAccessory/AndroidAccessory.h"

AndroidAccessory acc("Willow Garage",
		     "ROSSerialADK",
		     "ROS ADK Bridge",
		     "1.0",
		     "http://www.android.com",
		     "0000000012345678");
		     
namespace adk{
	int rxBufferIndex;
	int txBufferIndex ;
	int rxBufferLen;
	uint8_t buffOut[250];
	uint8_t buffin[250];
}

using namespace adk;

void fx_open(){
	acc.powerOn();
		
	txBufferIndex =-1;
	rxBufferIndex = 0;
	rxBufferLen =0;
}

int fx_putc(char c){
	if(txBufferIndex >250) return 0;

	txBufferIndex++;
	buffOut[txBufferIndex] = c;
	
	return 1;
}
 
int fx_getc(){
	if (rxBufferIndex< rxBufferLen) {
		int c =  buffin[rxBufferIndex];
		rxBufferIndex++;
		return c;
	}
	return -1;
}

void adk_spin(){
	//handle all the reads and writes
	if (acc.isConnected()){
		int len = acc.read(buffin, 250, 1);		
		rxBufferLen = len;
		rxBufferIndex =0;
		
		if (txBufferIndex >= 0 ){
			digitalWrite(13, HIGH-digitalRead(13));
			acc.write(buffOut, txBufferIndex+1); //+1 to convert index to length
			txBufferIndex =-1;
		}
	}
}
