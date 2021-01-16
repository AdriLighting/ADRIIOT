
#include <ADRIOT.h>
#include <adri_tools.h>

adriot_main * adriotMain;

solmoistureClass * sensorSolMoisture;

int		relayPump 				= -1;
boolean relayPump_statu 		= false;
boolean sensorSolMoisture_cap 	= false;

dht22Class sensor_temperature(D2);

void setup()
{
	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }

  	#ifdef DEBUG
  		fsprintf("\n[ADRIOT BEGIN]\n");	
  	#endif
	adriotMain = new adriot_main();

	#ifdef DEBUG
		fsprintf("\n[ADRIOT SOL MOISTURE BEGIN]\n");	
	#endif
	sensorSolMoisture = new solmoistureClass(false,D1);

	#ifdef DEBUG
		fsprintf("\n[ADRIOT RELAY MOISTURE PUMP BEGIN]\n");	
	#endif
	adriotMain->_relayManagment->create(D2, relayPump);
}

void loop()
{
	relayPump_statu 		= adriotMain->_relayManagment->relay(relayPump)->getStatus();	
	sensorSolMoisture->loop(sensorSolMoisture_cap);
	if (sensorSolMoisture_cap) {
		if (!relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->open();
	} else {
		if (relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->close();
	}
}