## adri_rgb_patterns

patterns management for rgb mod lampe.
used for ALS_server.

<pre>
Librairies
<details>
adri_rgb_patterns               = https://github.com/AdriLighting/adri_rgb_patterns
adri_timer                      = https://github.com/AdriLighting/adri_timer

ArduinoJson                     = https://github.com/bblanchon/ArduinoJson

framework                       = https://github.com/esp8266/Arduino/tree/master/libraries
LittleFS(esp8266)               = 

</details>
Dependency Graph
<details>
|-- [adri_rgb_patterns] 1.0.0
|   |-- [adri_timer] 1.0.0
|   |-- [ArduinoJson] 6.17.1
|   |-- [LittleFS(esp8266)] 0.1.0</details>
</pre>

<hr>

#### examples

adri_rgb_patterns_1
<details>
<pre>
platformio.ini
<details>
[env:nodemcuv2]
platform=espressif8266
board=nodemcuv2
framework=arduino
lib_extra_dirs= ${env.lib_extra_dirs}
[platformio]
src_dir= ${env.src_dir}

</details>
</pre>
<pre>
Librairies
<details>
ALS_leds_effects                = https://github.com/AdriLighting/ALS_leds_effects

adri_rgb_patterns               = https://github.com/AdriLighting/adri_rgb_patterns
adri_timer                      = https://github.com/AdriLighting/adri_timer
adri_tools_v2                   = https://github.com/AdriLighting/adri_tools_v2
adri_leds_color                 = https://github.com/AdriLighting/adri_leds_color
adri_spiff                      = https://github.com/AdriLighting/adri_spiff

ArduinoJson                     = https://github.com/bblanchon/ArduinoJson
FastLED                         = https://github.com/FastLED/FastLED

framework                       = https://github.com/esp8266/Arduino/tree/master/libraries
LittleFS(esp8266)               = 
ESP8266WiFi                     = 
SPI                             = 

unregisterd lib:
EspSoftwareSerial = 
</details>
Dependency Graph
<details>
|-- [adri_rgb_patterns] 1.0.0
|   |-- [adri_timer] 1.0.0
|   |-- [ArduinoJson] 6.17.1
|   |-- [LittleFS(esp8266)] 0.1.0
|-- [adri_tools_v2] 1.0.0
|   |-- [ESP8266WiFi] 1.0
|   |-- [LittleFS(esp8266)] 0.1.0
|-- [ALS_leds_effects] 1.0.0
|   |-- [FastLED] 3.3.3
|   |   |-- [SPI] 1.0
|   |   |-- [EspSoftwareSerial] 6.8.5
|   |-- [adri_leds_color] 1.0.0
|   |   |-- [FastLED] 3.3.3
|   |   |   |-- [SPI] 1.0
|   |   |   |-- [EspSoftwareSerial] 6.8.5
|   |-- [adri_spiff] 1.0.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [adri_tools_v2] 1.0.0
|   |   |-- [ESP8266WiFi] 1.0
|   |   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [LittleFS(esp8266)] 0.1.0
|   |-- [ArduinoJson] 6.17.1
|   |-- [adri_timer] 1.0.0</details>
</pre>

</details>
<hr>