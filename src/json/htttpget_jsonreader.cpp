/*
    Author: adrilighting
    Name: covid-19 tracker
    Description : json parse from http://coronavirus-19-api.herokuapp.com/countries/France
    
*/
#include "htttpget_jsonreader.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <adri_tools_v2.h>
// #include "ui_progress.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

API_MOD apiMod;

String currentParent;
int weatherItemCounter=0;

PROGMEM httpGetJsonReaderList covid19List_key [] = { 
	// {"country",					"Pays"},
	// {"cases",					"Cas de Covid-19"},
	// // {"todayCases",				"Cas de Covid-19, aujourd'hui"},
	// {"deaths",					"Mort"},
	// {"recovered", 				"Retabli"},
	// // {"active", 					"Actif."},
	// // {"critical",				"Critique."},
	// // {"casesPerOneMillion",		"casesPerOneMillion."},
	// // {"deathsPerOneMillion",		"deathsPerOneMillion."},
	// {"totalTests",				"Despistage total"},
	// // {"testsPerOneMillion",		"testsPerOneMillion."}

};
uint8_t covid19List_keyCount = ARRAY_SIZE(covid19List_key);

PROGMEM httpGetJsonReaderList weatherbitList_key [] = { 
	// {"lat",                             "Latitude (Degrees)."                                               },
	// {"lon",                             "Longitude (Degrees)."                                              },
	// {"sunrise",                         "Sunrise time (HH:MM)."                                             },
	// {"sunset",                          "Sunset time (HH:MM)."                                              },
	// {"timezone",                        "Local IANA Timezone."                                              },
	// {"station",                         "Source station ID."                                                },
	// {"ob_time",                         "Last observation time (YYYY-MM-DD HH:MM)."                         },
	// {"datetime",                        "Current cycle hour (YYYY-MM-DD:HH)."                               },
	// {"ts",                              "Last observation time (Unix timestamp)."                           },
	// {"city_name",                       "City name."                                                        },
	// {"country_code",                    "Country abbreviation."                                             },
	// {"state_code",                      "State abbreviation/code."                                          },
	// {"pres",                            "Pressure (mb)."                                                    },
	// {"slp",                             "Sea level pressure (mb)."                                          },
	// {"wind_spd",                        "Wind speed (Default m/s)."                                         },
	// {"wind_dir",                        "Wind direction (degrees)."                                         },
	// {"wind_cdir",                       "Abbreviated wind direction."                                       },
	// {"wind_cdir_full",                  "Verbal wind direction."                                            },
	{"temp",                            "Temperature (default Celcius)."                                    },
	{"app_temp",                        "Apparent/Feels Like temperature (default Celcius)."              	},
	// {"rh",                              "Relative humidity (%)."                                            },
	// {"dewpt",                           "Dew point (default Celcius)."                                      },
	// {"clouds",                          "Cloud coverage (%)."                                               },
	// {"pod",                             "Part of the day (d = day / n = night)."                            },
	// {"icon",                            "Weather icon code."                                                },
	// {"code",                            "Weather code."                                                     },
	// {"description",                     "Text weather description."                                         },
	// {"vis",                             "Visibility (default KM)."                                          },
	// {"precip",                          "Liquid equivalent precipitation rate (default mm/hr)."             },
	// {"snow",                            "Snowfall (default mm/hr)."                                         },
	// {"uv",                              "UV Index (0-11+)."                                                 },
	// {"aqi",                             "Air Quality Index [US - EPA standard 0 - +500]"                    },
	// {"dhi",                             "Diffuse horizontal solar irradiance (W/m^2) [Clear Sky]"           },
	// {"dni",                             "Direct normal solar irradiance (W/m^2) [Clear Sky]"                },
	// {"ghi",                             "Global horizontal solar irradiance (W/m^2) [Clear Sky]"            },
	// {"solar_rad",                       "Estimated Solar Radiation (W/m^2)."                                },
	// {"elev_angle", 						"Solar elevation angle (degrees)."                                  },
	// {"h_angle",                         "Solar hour angle (degrees)."                                       }
};
uint8_t weatherbitList_keyCount = ARRAY_SIZE(weatherbitList_key);
String weatherbitList_data[2];


PROGMEM httpGetJsonReaderList weatherstack_key [] = { 

};
PROGMEM httpGetJsonReaderList openWeatherMapList_key [] = { 
	// {"id",				"id"},
	// {"main",            "main"},
	{"description",     "description"},
	{"icon",            "icon"},
	{"temp",            "temp"},
	{"pressure",        "pressure"},
	// {"humidity",        "humidity"},
	{"temp_min",        "temp_min"},
	{"temp_max",        "temp_max"},
	// {"visibility",      "visibility"},
	// {"speed",           "speed"},
	// {"deg",             "deg"},
	// {"all",             "all"},
	// {"dt",              "dt"},
	// {"country",         "country"},
	// {"sunrise",         "sunrise"},
	// {"sunset",          "sunset"},
	// {"name",            "name"}
};
uint8_t openWeatherMapList_keyCount = ARRAY_SIZE(openWeatherMapList_key);
String openWeatherMapList_data[6];


httpGetJsonReaderCurrent::httpGetJsonReaderCurrent() {

}

String httpGetJsonReaderCurrent::buildUrl(String url) {
	return url;
}
void httpGetJsonReaderCurrent::updateCurrentById(String url) {
	doUpdate(buildUrl(url));
}
void httpGetJsonReaderCurrent::doUpdate(String url) {
	Serial.printf("\n[httpGetJsonReaderCurrent::doUpdate] Start\n");
	unsigned long lostTest = 10000UL;
	unsigned long lost_do = millis();
	JsonStreamingParser parser;
	parser.setListener(this);

	Serial.printf("[URL]: %s\n", url.c_str());
	HTTPClient http;

	http.begin(url);
	bool isBody = false;
	char c;
	Serial.print("[HTTP] GET...\n");
	int httpCode = http.GET();
	Serial.printf("[HTTP] GET... code: %d\n", httpCode);
	uint8_t count = 0;
	if(httpCode > 0) {

		WiFiClient * client = http.getStreamPtr();
		while (client->connected() || client->available()) {
			while (client->available()) {
				if ((millis() - lost_do) > lostTest) {
					Serial.println("timeout");
					client->stop();
					ESP.restart();
				}
				c = client->read();
				if (c == '{' || c == '[') {
					isBody = true;
				}
				if (isBody) {
					parser.parse(c);
				}
				yield();
				delay(1);

				// screen_wifiConnect_loop(count);
				count++;
			}
			client->stop();
		}
	}
	Serial.printf("[httpGetJsonReaderCurrent::doUpdate] End\n");

}
void httpGetJsonReader_print(httpGetJsonReaderList * list, int count, String header, int space, String apiName) {
	String s;
	String v;
	const char * d;
	String dS;
	Serial.printf("\n[httpGetJsonReader_print - %s] Start\n", header.c_str());
    for( int i = 0; i < count; i++) { 

    	if (apiName == "openweather"){
			v = openWeatherMapList_data[i];
    	}
    	if (apiName == "weatherbit") {
			v = weatherbitList_data[i];
    	}

		d = list[i].desc;
		dS = adri_toolsv2Ptr_get()->ch_toString(d);
		while (dS.length()<space) dS+=" ";

    	Serial.printf("%s : %s\n", dS.c_str(), v.c_str());
    } 	
	Serial.printf("[httpGetJsonReader_print] End\n");

}
String httpGetJsonReader_getKey(httpGetJsonReaderList * list, const char * value, int count, String apiName) {
	String ret = "";
    for( int i = 0; i < count; i++) { 
    	if (apiName == "openweather"){
	        if(list[i].key == value) {
	        	ret = openWeatherMapList_data[i];
	        	break;
	        }
    	}
    	if (apiName == "weatherbit") {
	        if(list[i].key == value) {
	        	ret = weatherbitList_data[i];
	        	break;
	        }
    	}

    } 	
    return ret;
}

void httpGetJsonReaderCurrent::whitespace(char c) {
}

void httpGetJsonReaderCurrent::startDocument() {
}

void httpGetJsonReaderCurrent::key(String key) {
	currentKey = String(key);
}

void httpGetJsonReaderCurrent::value(String value) {
	if (apiMod == API_MOD_COVID19) {
	    for( int i = 0; i < covid19List_keyCount; i++) { 
	        if(adri_toolsv2Ptr_get()->ch_toString(covid19List_key[i].key) == currentKey) {
	        	// covid19List_key[i].data = ch_toString(value);
	        }
	    }
    }
	if (apiMod == API_MOD_WEATHERBIT) {
	    for( int i = 0; i < weatherbitList_keyCount; i++) { 
	        if(adri_toolsv2Ptr_get()->ch_toString(weatherbitList_key[i].key) == currentKey) {
	        	// weatherbitList_key[i].data = value;
	        	weatherbitList_data[i] = value;
	        }
	    }
    }  
	if (apiMod == API_MOD_OPENWATHERMAP) {
	    for( int i = 0; i < openWeatherMapList_keyCount; i++) { 
	        if(adri_toolsv2Ptr_get()->ch_toString(openWeatherMapList_key[i].key) == currentKey) {
	        	// openWeatherMapList_key[i].data = value;
	        	openWeatherMapList_data[i] = value;
	        }
	    }
    }       
}

void httpGetJsonReaderCurrent::endArray() {
}

void httpGetJsonReaderCurrent::endObject() {
	if (apiMod == API_MOD_OPENWATHERMAP) {
		if (currentParent == "weather") {
			weatherItemCounter++;
		}
		currentParent = "";
    } 	
}

void httpGetJsonReaderCurrent::endDocument() {
}

void httpGetJsonReaderCurrent::startArray() {
}

void httpGetJsonReaderCurrent::startObject() {
	if (apiMod == API_MOD_OPENWATHERMAP) {
  		currentParent = currentKey;
    } 		
}
