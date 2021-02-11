# ADRIIOT
16/01/2021.<br />
Creation of a set of libraries for the use of IOT module .<br />


## Features

* Support for **multiple ESP8266-based boards**
* Power saving options
* Wifi **AP Mode** or **STA mode**
    * Supports static IP
    * Up to 3 different networks can be defined
    * Scans for strongest network if more than one defined (also available in web UI)
    * Defaults to AP mode 
* Network visibility
    * Supports mDNS (service reporting and metadata) both server mode and client mode (.local name resolution)
    * Supports NetBIOS, LLMNR and Netbios (when built with Arduino Core >= 2.4.0)
* display 
    * support for ili9341
         * display module state
         * display rtc or ntp time
         * display mete from openWeatherApi
* Switch management
    * Support for **push buttons** and **toggle switches**
    * Support for **digital** and [**analog**](https://en.wikipedia.org/wiki/Resistor_ladder) buttons
    * Configurable **status on boot** per switch (always ON, always OFF, same as before or toggle)
    * Support for **relay synchronization** (all equal, only one ON, one and only on ON)
    * Support for **delayed ON/OFF**
    * Support for **latched relays**
* Analog management
* **MQTT** enabled
* domoticz integration via MQTT
   * Light/Switch
   * Color Switch
   * Temp + Humidity
   * Temp
   * Soil moisture
* HTTP Server for Web User Interface
    * dasboard interface for devices controll and satte 
    * Websockets-based communication between the device and the browser
* Telnet support
    * Shows debug info and allows to run terminal commands
* NTP for time synchronization
    * Supports worldwide time zones
    * Compatible with DST (EU and USA)
* OpenWeatherApi support
* Support for [different **sensors**](Sensors)
    * Environment
        * **DHT22 / DS2812b**
* Support for LED lights
   * AC dimmer pwm
   * rgb/rgbw strip based on ws2812b/SK6812 


</br>
<hr>
</br>

## Dependencies
### from my persoanl libraibries
* ![adriiot_relay](https://github.com/AdriLighting/adriiot_relay)<br />
* ![adriiot_soilmoisture](https://github.com/AdriLighting/adriiot_soilmoisture)<br />
* ![adriiot_dht22](https://github.com/AdriLighting/adriiot_dht22)<br />
* ![ADRIIOT_lightDimmer](https://github.com/AdriLighting/ADRIIOT_lightDimmer)<br />
* ![ADRIIOT_RGBneo](https://github.com/AdriLighting/ADRIIOT_RGBneo)<br />
* ![adriiot_relay](https://github.com/AdriLighting/adri_tools_v2)<br /><br />
* ![adri_ntpTime](https://github.com/AdriLighting/adri_ntpTime)<br />
* ![adri_calendar_event](https://github.com/AdriLighting/adri_calendar_event)<br />
* ![adri_wifiConnect](https://github.com/AdriLighting/adri_wifiConnect)<br />
* ![adri_timer](https://github.com/AdriLighting/adri_timer)<br />
* ![adri_espwebserver](https://github.com/AdriLighting/adri_espwebserver)<br />
* ![adri_httparseurl](https://github.com/AdriLighting/adri_httparseurl)<br />
* ![adri_logger](https://github.com/AdriLighting/adri_logger)<br />
* ![adri_tools_v2_telnet](https://github.com/AdriLighting/adri_tools_v2_telnet)<br />
* ![adri_tools_v2_serialMenu](https://github.com/AdriLighting/adri_tools_v2_serialMenu)<br />
### extern
<pre>
  https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
     LittleFS(esp8266) 0.1.0
     ESP8266WiFi 1.0
     ESP8266mDNS 1.2  
     ArduinoOTA 1.0
  https://github.com/Links2004/arduinoWebSockets
  
  http://playground.arduino.cc/Code/Time/

  https://github.com/adafruit/Adafruit_NeoPixel
  
  https://github.com/adafruit/Adafruit_Sensor
  
  https://github.com/bblanchon/ArduinoJson
  https://github.com/adafruit/Adafruit_NeoPixel
  
  https://github.com/bblanchon/ArduinoJson
  https://github.com/squix78/json-streaming-parser.git
  
  https://github.com/adafruit/Adafruit_BusIO
  https://github.com/adafruit/Adafruit-GFX-Library  
  https://github.com/adafruit/Adafruit_ILI9341 
  https://github.com/olikraus/U8g2_for_Adafruit_GFX
  https://github.com/Bodmer/JPEGDecoder
  http://github.com/spapadim/XPT2046
  https://github.com/Bodmer/JPEGDecoder
  
</pre>

