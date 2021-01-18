# ADRIOT
16/01/2021.<br />
Création d'un Enssemble de libraries pour l'utilisation de module IOT.<br />

## 16/01/2021 13:58:06
### Idée
<pre>
    configuration des modules
        interface
            - android || html
            - tft 
        configuration
            - activation/désactivation
</pre>
### FAIRE
### FAIT
* librairie ADRIOT<br />
* librairie ![ADRIOT_relay](https://github.com/AdriLighting/ADRIOT_relay)<br />
* librairie ![ADRIOT_solMoisture](https://github.com/AdriLighting/ADRIOT_solMoisture)<br />
* librairie ![ADRIOT_dht22](https://github.com/AdriLighting/ADRIOT_dht22)<br />

## 18/01/2021 01:51:36
### Idée
<pre>
    modules dynamique
        relay
        solMoisture
    module statique
        dht22        
</pre>
### FAIRE
### FAIT
<pre>
    network function
            wifi connect 
                STA
                    real-time NTP 
                STA || AP
                    webserver
                        socket
                        http
    wifi.cpp
        class wifiClass : public wifiConnect
    adriot_main.h    
        class adriot_main
            ptr : wifiClass         * _wifi  
            ptr : ALS_espwebserver  * _webServer
        class adriot_module        

</pre>