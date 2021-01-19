

#include <ADRIOT.h>
#include <adri_tools.h>


#define DEBUG


adri_webserver		clientServer(80);
adri_socket			socketServer(81);

adriot_main 		* adriotMain;

adri_timer 			* timeDisplay 			= nullptr;

solmoistureClass 	* sensorSolMoisture 	= nullptr;
boolean 			sensorSolMoisture_cap 	= false;

int					relayPump 				= -1;
boolean 			relayPump_statu 		= false;

int					sensorTemperature		= -1;

void setup()
{


	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }


	LittleFS.begin();


  	#ifdef DEBUG
  		fsprintf("\n[ADRIOT BEGIN]\n");	
  	#endif
	adriotMain = new adriot_main((char *)"ADRIOT");




/*
	#ifdef DEBUG
		fsprintf("\n[ADRIOT SOL MOISTURE SENSOR BEGIN]\n");	
	#endif
	sensorSolMoisture = new solmoistureClass(false, A0);

	
	#ifdef DEBUG
		fsprintf("\n[ADRIOT MOISTURE PUMP RELAY BEGIN]\n");	
	#endif
	adriotMain->_relayManagment->create(D2, relayPump);

	
	#ifdef DEBUG
		fsprintf("\n[ADRIOT TEMPERATURE SENSOR BEGIN]\n");	
	#endif
	adriotMain->_dht22Managment->create(D2, sensorTemperature);
*/
/*	
	timeDisplay = new adri_timer(1000,"",true);
void loop()
*/


}


void loop()
{


	adriotMain->loop();
	

	if ((relayPump!=-1) && (sensorSolMoisture!=nullptr)) {
		relayPump_statu 		= adriotMain->_relayManagment->relay(relayPump)->getStatus();	
		sensorSolMoisture->loop(sensorSolMoisture_cap);
		if (sensorSolMoisture_cap) {
			if (!relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->open();
		} else {
			if (relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->close();
		}		
	}


}
