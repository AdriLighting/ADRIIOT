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
    1 séléction des modules voulllu.
    2 sauvegarde de la séléction
    1 chargement de ma séméction des modules
    ----
    modules dynamique
        relay
        solMoisture
    module statique
        dht22      
    ----
    openweather
    database ....
    ----  
</pre>
### FAIRE
    module wemos d1 pro+oledi2c
### FAIT
<pre>
    network function
            wifi  
                STA
                    NTP real-time  
                STA || AP
                    webserver protocol
                        socket
                        http
                        
    wifi.cpp
        class wifiClass : public wifiConnect 
    adriot_main.h    
        class adriot_main
            ptr : wifiClass         * _wifi         
            ptr : ALS_espwebserver  * _webServer    (hhtp && socket)
        class adriot_module        
</pre>