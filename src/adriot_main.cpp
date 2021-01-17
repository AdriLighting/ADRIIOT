#include "adriot_main.h"

relayManagement adriot_relayManagement;

adriot_main::adriot_main(const char * hName){
	_relayManagment = &adriot_relayManagement;
	_wifi = new wifiClass(hName);
}