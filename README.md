# adriiot
16/01/2021.<br />
Création d'un Enssemble de libraries pour l'utilisation de module IOT.<br />

<br />
<hr>

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
* librairie adriiot<br />
* librairie ![adriiot_relay](https://github.com/AdriLighting/adriiot_relay)<br />
* librairie ![adriiot_soilmoisture](https://github.com/AdriLighting/adriiot_soilmoisture)<br />
* librairie ![adriiot_dht22](https://github.com/AdriLighting/adriiot_dht22)<br />

<br />
<hr>

## 18/01/2021 01:51:36
### Idée
<pre>
    1 séléction des modules voulllu.
    2 sauvegarde de la séléction
    1 chargement de ma séméction des modules
    ----
    modules dynamique
        relay
        soilmoisture
    module statique
        dht22      
    ----
    openweather
    database with graphic interface (agenda, stock de ressource, etc...)
    ----  
</pre>
### FAIRE
<pre>
    module wemos d1 pro + oledi2c + relay
</pre>    
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
     
</pre>

<br />
<hr>

</pre>
## 29/01/2021 02:37:53
### Idée
<pre>
    no up
</pre>
### FAIRE
<pre>
    no up
</pre>    
### FAIT
<pre>
    NETWORK DASHBOARD
        platform
            domotoricz via mosquitto from W10
            webserver via http && socket from esp
        data 
            json
                modules value && modules list
            mise a jour
                démarage de l'esp
                chaque changement d'état des modules
    MODULES
        initialisation
            static
            dynamique 
                chargement via spiff

</pre>

<br />
<hr>

## 01/02/2021 11:51:07
### Idée
<pre>
    no up
</pre>
### FAIRE
<pre>
    module wemos d1 pro + oledi2c + relay
    trouver un system de requette pour domoticz+socket/http+udp
</pre>    
### FAIT
adri_tools_v2<br />
* librairie ![adri_tools_v2](https://github.com/AdriLighting/adri_tools_v2)
<pre>
    debugger-logger
    
</pre>

## 04/02/2021 09:11:54
### Idée
<pre>
    no up
</pre>
### FAIRE
<pre>
    module wemos d1 pro + oledi2c + relay
    trouver un system de requette pour domoticz+socket/http+udp
    sauvegarde des statu modules via spiff 
</pre>    
### FAIT
ADRIIOT_RGBneo<br />
* librairie ![ADRIIOT_RGBneo](https://github.com/AdriLighting/ADRIIOT_RGBneo)

ADRIIOT_lightDimmer<br />
* librairie ![ADRIIOT_lightDimmer](https://github.com/AdriLighting/ADRIIOT_lightDimmer)
<pre>
    module strip rgb
    module lightDimmer
    requette from domoticz via mqtt pour le control des modules
    
</pre>

