# ADRIIOT
16/01/2021.<br />
Creation of a set of libraries for the use of IOT module .<br />


## Features

* Support for **multiple ESP8266-based boards**
* Wifi **AP Mode** or **STA mode**
    * Supports static IP
    * Up to 3 different networks can be defined
    * Scans for strongest network if more than one defined (also available in web UI)
    * Defaults to AP mode 
* Network visibility
    * Supports mDNS (service reporting and metadata) both server mode and client mode (.local name resolution)
    * Supports NetBIOS 
* display 
    * support for ili9341
         * display module state
         * display rtc or ntp time
         * display mete from openWeatherApi
* module managment
    * via web user interfance 
      * add or remove module
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

<pre>
Librairies
<details>
ALS_espwebserver                = https://github.com/AdriLighting/ALS_espwebserver

ADRIIOT                         = https://github.com/AdriLighting/ADRIIOT
ADRIIOT_dht22                   = https://github.com/AdriLighting/ADRIIOT_dht22
ADRIIOT_DS18B20                 = https://github.com/AdriLighting/ADRIIOT_DS18B20
ADRIIOT_lightDimmer             = https://github.com/AdriLighting/ADRIIOT_lightDimmer
ADRIIOT_relay                   = https://github.com/AdriLighting/ADRIIOT_relay
ADRIIOT_RGBneo                  = https://github.com/AdriLighting/ADRIIOT_RGBneo
ADRIIOT_solMoisture             = https://github.com/AdriLighting/ADRIIOT_solMoisture

adri_tools_v2                   = https://github.com/AdriLighting/adri_tools_v2
adri_ntpTime                    = https://github.com/AdriLighting/adri_ntpTime
adri_calendar_event             = https://github.com/AdriLighting/adri_calendar_event
adri_wifiConnect                = https://github.com/AdriLighting/adri_wifiConnect
adri_timer                      = https://github.com/AdriLighting/adri_timer
adri_espwebserver               = https://github.com/AdriLighting/adri_espwebserver
adri_httparseurl                = https://github.com/AdriLighting/adri_httparseurl
adri_tft_ILI9341                = https://github.com/AdriLighting/adri_tft_ILI9341
adri_tft_ILI9341_ESP            = https://github.com/AdriLighting/adri_tft_ILI9341_ESP
adri_logger                     = https://github.com/AdriLighting/adri_logger
adri_softLogger                 = https://github.com/AdriLighting/adri_softLogger
adri_tools_v2_serialMenu        = https://github.com/AdriLighting/adri_tools_v2_serialMenu
adri_tools_v2_telnet            = https://github.com/AdriLighting/adri_tools_v2_telnet

esp8266/arduino                 = https://github.com/esp8266/Arduino/tree/master/libraries

Adafruit BusIO                  = https://github.com/adafruit/Adafruit_BusIO
Adafruit Unified Sensor         = https://github.com/adafruit/Adafruit_Sensor
JsonStreamingParser             = https://github.com/squix78/json-streaming-parser.git
TimeLib                         = https://github.com/PaulStoffregen/Time
ArduinoJson                     = https://github.com/bblanchon/ArduinoJson
WebSockets                      = https://github.com/Links2004/arduinoWebSockets
ESPAsyncTCP                     = https://github.com/me-no-dev/ESPAsyncTCP
Adafruit GFX Library            = https://github.com/adafruit/Adafruit-GFX-Library
XPT2046                         = http://github.com/spapadim/XPT2046
U8g2_for_Adafruit_GFX           = https://github.com/olikraus/U8g2_for_Adafruit_GFX
JPEGDecoder                     = https://github.com/Bodmer/JPEGDecoder
DHT sensor library              = https://github.com/adafruit/DHT-sensor-library
DallasTemperature               = https://github.com/milesburton/Arduino-Temperature-Control-Library
OneWire                         = https://github.com/PaulStoffregen/OneWire
Adafruit NeoPixel               = https://github.com/adafruit/Adafruit_NeoPixel
PubSubClient                    = https://github.com/knolleary/pubsubclient
</details>
Dependency Graph
<details>
|-- [ESP8266WiFi] 1.0
|-- [Adafruit BusIO] 1.4.1
|   |-- [Wire] 1.0
|   |-- [SPI] 1.0
|-- [Wire] 1.0
|-- [Adafruit Unified Sensor] 1.1.4
|-- [ADRIIOT] 1.0.0
|   |-- [JsonStreamingParser] 1.0.5
|   |-- [adri_tools_v2] 1.0.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [ESP8266HTTPClient] 1.2
|   |   |-- [ESP8266WiFi] 1.0
|   |-- [ESP8266WiFi] 1.0
|   |-- [adri_ntpTime] 1.0.0
|   |   |-- [TimeLib] 1.6
|   |   |-- [ESP8266WiFi] 1.0
|   |-- [adri_calendar_event] 1.0.0
|   |   |-- [TimeLib] 1.6
|   |-- [TimeLib] 1.6
|   |-- [adri_wifiConnect] 1.0.0
|   |   |-- [ESP8266WebServer] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266mDNS] 1.2
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [adri_timer] 1.0.0
|   |-- [adri_timer] 1.0.0
|   |-- [adri_espwebserver] 1.0.0
|   |   |-- [ArduinoOTA] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266mDNS] 1.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266mDNS] 1.2
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [Hash] 1.0
|   |   |-- [ArduinoJson] 6.17.1
|   |   |-- [ESP8266HTTPClient] 1.2
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266WebServer] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [WebSockets] 2.2.1
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESPAsyncTCP] 1.2.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [Ethernet(esp8266)] 1.0.4
|   |   |   |   |-- [SPI] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |   |-- [Hash] 1.0
|   |   |-- [adri_httparseurl] 1.0.0
|   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tft_ILI9341] 1.0.0
|   |   |-- [SPI] 1.0
|   |   |-- [adri_tft_ILI9341_ESP] 1.0.1
|   |   |   |-- [Adafruit GFX Library] 1.10.2
|   |   |   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |   |   |-- [Wire] 1.0
|   |   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [Wire] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |-- [Adafruit GFX Library] 1.10.2
|   |   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |   |-- [Wire] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |   |-- [Wire] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |-- [XPT2046] 0.1
|   |   |   |-- [SPI] 1.0
|   |   |-- [U8g2_for_Adafruit_GFX] 1.7.0
|   |   |   |-- [Adafruit GFX Library] 1.10.2
|   |   |   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |   |   |-- [Wire] 1.0
|   |   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [Wire] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |-- [JPEGDecoder] 1.8.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [Adafruit GFX Library] 1.10.2
|   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |-- [Wire] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |-- [Wire] 1.0
|   |   |-- [SPI] 1.0
|   |-- [ADRIIOT_dht22] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |   |-- [DHT sensor library] 1.4.1
|   |   |   |-- [Adafruit Unified Sensor] 1.1.4
|   |-- [ADRIIOT_DS18B20] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |   |-- [DallasTemperature] 3.9.0
|   |   |   |-- [OneWire] 2.3.5
|   |   |-- [OneWire] 2.3.5
|   |-- [ADRIIOT_lightDimmer] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [ADRIIOT_relay] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [ADRIIOT_RGBneo] 1.0.0
|   |   |-- [Adafruit NeoPixel] 1.7.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [ADRIIOT_solMoisture] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [adri_logger] 1.0.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_softLogger] 1.0.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tools_v2_serialMenu] 1.0.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tools_v2_telnet] 1.0.0
|   |   |-- [adri_tools_v2_serialMenu] 1.0.0
|   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |-- [ALS_espwebserver] 1.0.0
|   |   |-- [adri_espwebserver] 1.0.0
|   |   |   |-- [ArduinoOTA] 1.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [ESP8266mDNS] 1.2
|   |   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266mDNS] 1.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [Hash] 1.0
|   |   |   |-- [ArduinoJson] 6.17.1
|   |   |   |-- [ESP8266HTTPClient] 1.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266WebServer] 1.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [WebSockets] 2.2.1
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [ESPAsyncTCP] 1.2.2
|   |   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [Ethernet(esp8266)] 1.0.4
|   |   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [Hash] 1.0
|   |   |   |-- [adri_httparseurl] 1.0.0
|   |   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [ArduinoJson] 6.17.1
|   |-- [PubSubClient] 2.8</details>
</pre>

<hr>

#### examples

adriot
<details>
platformio.ini
<details>
<pre>
[env:nodemcuv2]
platform=espressif8266
board=nodemcuv2
framework=arduino
lib_deps=adri_tools_v2_serialMenu, Json Streaming Parser, Adafruit BusIO, Wire, Adafruit Unified Sensor
lib_ignore=WiFi101
board_build.filesystem=littlefs
board_build.ldscript=eagle.flash.4m3m.ld
lib_extra_dirs= ${env.lib_extra_dirs}
upload_speed=921600
[platformio]
src_dir= ${env.src_dir}

</pre>
</details>
<pre>
Librairies
<details>
ALS_espwebserver                = https://github.com/AdriLighting/ALS_espwebserver

ADRIIOT                         = https://github.com/AdriLighting/ADRIIOT
ADRIIOT_dht22                   = https://github.com/AdriLighting/ADRIIOT_dht22
ADRIIOT_DS18B20                 = https://github.com/AdriLighting/ADRIIOT_DS18B20
ADRIIOT_lightDimmer             = https://github.com/AdriLighting/ADRIIOT_lightDimmer
ADRIIOT_relay                   = https://github.com/AdriLighting/ADRIIOT_relay
ADRIIOT_RGBneo                  = https://github.com/AdriLighting/ADRIIOT_RGBneo
ADRIIOT_solMoisture             = https://github.com/AdriLighting/ADRIIOT_solMoisture

adri_tools_v2_serialMenu        = https://github.com/AdriLighting/adri_tools_v2_serialMenu
adri_tools_v2                   = https://github.com/AdriLighting/adri_tools_v2
adri_ntpTime                    = https://github.com/AdriLighting/adri_ntpTime
adri_calendar_event             = https://github.com/AdriLighting/adri_calendar_event
adri_wifiConnect                = https://github.com/AdriLighting/adri_wifiConnect
adri_timer                      = https://github.com/AdriLighting/adri_timer
adri_espwebserver               = https://github.com/AdriLighting/adri_espwebserver
adri_httparseurl                = https://github.com/AdriLighting/adri_httparseurl
adri_tft_ILI9341                = https://github.com/AdriLighting/adri_tft_ILI9341
adri_tft_ILI9341_ESP            = https://github.com/AdriLighting/adri_tft_ILI9341_ESP
adri_logger                     = https://github.com/AdriLighting/adri_logger
adri_softLogger                 = https://github.com/AdriLighting/adri_softLogger
adri_tools_v2_telnet            = https://github.com/AdriLighting/adri_tools_v2_telnet

esp8266/arduino                 = https://github.com/esp8266/Arduino/tree/master/libraries

Adafruit BusIO                  = https://github.com/adafruit/Adafruit_BusIO
Adafruit Unified Sensor         = https://github.com/adafruit/Adafruit_Sensor
JsonStreamingParser             = https://github.com/squix78/json-streaming-parser.git
TimeLib                         = https://github.com/PaulStoffregen/Time
ArduinoJson                     = https://github.com/bblanchon/ArduinoJson
WebSockets                      = https://github.com/Links2004/arduinoWebSockets
ESPAsyncTCP                     = https://github.com/me-no-dev/ESPAsyncTCP
Adafruit GFX Library            = https://github.com/adafruit/Adafruit-GFX-Library
XPT2046                         = http://github.com/spapadim/XPT2046
U8g2_for_Adafruit_GFX           = https://github.com/olikraus/U8g2_for_Adafruit_GFX
JPEGDecoder                     = https://github.com/Bodmer/JPEGDecoder
DHT sensor library              = https://github.com/adafruit/DHT-sensor-library
DallasTemperature               = https://github.com/milesburton/Arduino-Temperature-Control-Library
OneWire                         = https://github.com/PaulStoffregen/OneWire
Adafruit NeoPixel               = https://github.com/adafruit/Adafruit_NeoPixel
PubSubClient                    = https://github.com/knolleary/pubsubclient
</details>
Dependency Graph
<details>
|-- [adri_tools_v2_serialMenu] 1.0.0
|   |-- [adri_tools_v2] 1.0.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|-- [Adafruit BusIO] 1.4.1
|   |-- [Wire] 1.0
|   |-- [SPI] 1.0
|-- [Wire] 1.0
|-- [Adafruit Unified Sensor] 1.1.4
|-- [ADRIIOT] 1.0.0
|   |-- [JsonStreamingParser] 1.0.5
|   |-- [adri_tools_v2] 1.0.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [ESP8266HTTPClient] 1.2
|   |   |-- [ESP8266WiFi] 1.0
|   |-- [ESP8266WiFi] 1.0
|   |-- [adri_ntpTime] 1.0.0
|   |   |-- [TimeLib] 1.6
|   |   |-- [ESP8266WiFi] 1.0
|   |-- [adri_calendar_event] 1.0.0
|   |   |-- [TimeLib] 1.6
|   |-- [TimeLib] 1.6
|   |-- [adri_wifiConnect] 1.0.0
|   |   |-- [ESP8266WebServer] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266mDNS] 1.2
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [adri_timer] 1.0.0
|   |-- [adri_timer] 1.0.0
|   |-- [adri_espwebserver] 1.0.0
|   |   |-- [ArduinoOTA] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266mDNS] 1.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266mDNS] 1.2
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [Hash] 1.0
|   |   |-- [ArduinoJson] 6.17.1
|   |   |-- [ESP8266HTTPClient] 1.2
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [ESP8266WebServer] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [WebSockets] 2.2.1
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESPAsyncTCP] 1.2.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [Ethernet(esp8266)] 1.0.4
|   |   |   |   |-- [SPI] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |   |-- [Hash] 1.0
|   |   |-- [adri_httparseurl] 1.0.0
|   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tft_ILI9341] 1.0.0
|   |   |-- [SPI] 1.0
|   |   |-- [adri_tft_ILI9341_ESP] 1.0.1
|   |   |   |-- [Adafruit GFX Library] 1.10.2
|   |   |   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |   |   |-- [Wire] 1.0
|   |   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [Wire] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |-- [Adafruit GFX Library] 1.10.2
|   |   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |   |-- [Wire] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |   |-- [Wire] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |-- [XPT2046] 0.1
|   |   |   |-- [SPI] 1.0
|   |   |-- [U8g2_for_Adafruit_GFX] 1.7.0
|   |   |   |-- [Adafruit GFX Library] 1.10.2
|   |   |   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |   |   |-- [Wire] 1.0
|   |   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [Wire] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |-- [JPEGDecoder] 1.8.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [Adafruit GFX Library] 1.10.2
|   |   |-- [Adafruit BusIO] 1.4.1
|   |   |   |-- [Wire] 1.0
|   |   |   |-- [SPI] 1.0
|   |   |-- [Wire] 1.0
|   |   |-- [SPI] 1.0
|   |-- [ADRIIOT_dht22] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |   |-- [DHT sensor library] 1.4.1
|   |   |   |-- [Adafruit Unified Sensor] 1.1.4
|   |-- [ADRIIOT_DS18B20] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |   |-- [DallasTemperature] 3.9.0
|   |   |   |-- [OneWire] 2.3.5
|   |   |-- [OneWire] 2.3.5
|   |-- [ADRIIOT_lightDimmer] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [ADRIIOT_relay] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [ADRIIOT_RGBneo] 1.0.0
|   |   |-- [Adafruit NeoPixel] 1.7.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [ADRIIOT_solMoisture] 1.0.0
|   |   |-- [ArduinoJson] 6.17.1
|   |-- [adri_logger] 1.0.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_softLogger] 1.0.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tools_v2_serialMenu] 1.0.0
|   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tools_v2_telnet] 1.0.0
|   |   |-- [adri_tools_v2_serialMenu] 1.0.0
|   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |-- [ESP8266WiFi] 1.0
|   |-- [ALS_espwebserver] 1.0.0
|   |   |-- [adri_espwebserver] 1.0.0
|   |   |   |-- [ArduinoOTA] 1.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [ESP8266mDNS] 1.2
|   |   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266mDNS] 1.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [Hash] 1.0
|   |   |   |-- [ArduinoJson] 6.17.1
|   |   |   |-- [ESP8266HTTPClient] 1.2
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [ESP8266WebServer] 1.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |-- [WebSockets] 2.2.1
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [ESPAsyncTCP] 1.2.2
|   |   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [Ethernet(esp8266)] 1.0.4
|   |   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [SPI] 1.0
|   |   |   |   |-- [Hash] 1.0
|   |   |   |-- [adri_httparseurl] 1.0.0
|   |   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |   |   |-- [adri_tools_v2] 1.0.0
|   |   |   |   |-- [ESP8266WiFi] 1.0
|   |   |   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [ArduinoJson] 6.17.1
|   |-- [PubSubClient] 2.8</details>
</pre>

</details>
<hr>