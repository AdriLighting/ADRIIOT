# ADRIOT
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
* librairie ADRIOT<br />
* librairie ![ADRIOT_relay](https://github.com/AdriLighting/ADRIOT_relay)<br />
* librairie ![ADRIOT_solMoisture](https://github.com/AdriLighting/ADRIOT_solMoisture)<br />
* librairie ![ADRIOT_dht22](https://github.com/AdriLighting/ADRIOT_dht22)<br />

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
        solMoisture
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
                        
    wifi.cpp
        class wifiClass : public wifiConnect 
    adriot_main.h    
        class adriot_main
            ptr : wifiClass         * _wifi         
            ptr : ALS_espwebserver  * _webServer    (hhtp && socket)
        class adriot_module        
</pre>

<br />
<hr>

## 19/01/2021 01:33:51
### Idée
<pre>
    1 séléction des modules voulllu.
    2 sauvegarde de la séléction
    1 chargement de ma séméction des modules
    ----
    modules dynamique
        relay
        solMoisture
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
    class dht22Class
        constructor dyname DHT
    class dht22Management
        private:
            int _pos = 0;
        public:
            dht22Management();
            ~dht22Management(){};
            void create             (int value, int & result);
            void read_temperature   (float & result, boolean & isNan);
            void read_temperature   (int pos, float & result, boolean & isNan);
            void read_humidity      (float & result, boolean & isNan);
            void read_humidity      (int pos, float & result, boolean & isNan);
            dht22Class * dht22(int pos);
    class adriot_main
        dht22Management     * _dht22Managment;
    class adriot_module
        enum mModule
        enum mType
        mModule _mName  = mn_unk;
        mType   _mType  = mt_unk;
        int     _pin    = -1;
        int     _id     = -1;
        public:
            adriot_module(mModule name, mType type, int pin);
            void nameToString(mModule value, String & result); 
            void typeToString(mType value, String & result); 
            void create();
</pre>