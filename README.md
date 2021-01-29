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

## 20/01/2021 09:33:51
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
    class moduleClass
            mModule     _mName  = mn_unk;
            mType       _mType  = mt_unk;
            int         _pin    = -1;
        public:
            int         _id     = -1;
            moduleClass(mModule name, int pin);
            void nameToString(mModule value, String & result); 
            void typeToString(mType value, String & result); 
            void create();
    class moduleManagment
        private:
            int _pos = 0;
        public:
            moduleManagment();
            ~moduleManagment(){};
            void create (mModule name, int pin, int & result);
            void create (mModule name, int pin);
            moduleClass * module(int pos);
            void toggleRelay(unsigned long delay);
</pre>
## 29/01/2021 02:37:53
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
    NOUVELLES CLASS
        adriot_main.h
            enum mModule
            enum mType
            enum relayType
            enum sensorType

            class moduleClass
                private:
                    String      _name       = "myModule";
                    int         _nameId     = -1;
                    mModule     _mName      = mn_unk;
                    mType       _mType      = mt_unk;
                    relayType   _rType      = rt_unk;
                    sensorType  _sType      = st_unk;
                    int         _pin        = -1;
                    int         _id         = -1;
                public:
                    int         _mqttidx    = -1;

                    moduleClass(mModule name, mType module_type, relayType relay_type, int pin, String username);
                    moduleClass(mModule name, mType module_type, relayType relay_type, sensorType sType, int pin, String username);
                    void id_get(int & ret);
                    void nameId_get(int & ret);
                    void sType_get(sensorType & ret);
                    void mType_get(mType & ret);
                    void username_get(String & ret);
                    void create();
                    void print();
                    void json_value(JsonObject & root);
                    void json_domoticz_value(JsonObject & root);
                    void json(JsonObject & root);

                    class moduleManagment_spiff
                        String mListeFileName = "/spiff_mListe.txt";
                        String mListeArray[10];
                    public:
                        moduleManagment_spiff();
                        ~moduleManagment_spiff(){};
                        void create(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username, int idx, String & ret);
                        void add(int pos, String value);
                        boolean toSpiff();
                        void load(String file);
                        
                    class moduleManagment
                    {
                        private:
                            int _pos = 0;
                        public:
                            moduleManagment();
                            ~moduleManagment(){};

                            String modulesValue[MAX_MODULE];
                            void modulesValue_check();
                            adri_timer * modulesValue_checkTimer;

                            void mqqt_setidx(int idx);

                            void create(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username, int idx = -1);
                            void create_lightDimmer (int pin, String username, int idx = -1);
                            void create_temperature (int pin, String username, int idx = -1);
                            void create_plug        (int pin, String username, int idx = -1);
                            void create_light       (int pin, String username, int idx = -1);
                            void create_light       (mType type, int pin, String username, int idx = -1);
                            void create_sensor      (sensorType type, int pin, String username, int idx = -1);


                            moduleClass * module(int pos);

                            void toggleRelay(unsigned long delay);

                            void print();

                            int currentCnt();


                            void json_modules(String & ret);
                            void jsonObject_modules(JsonObject & root);

                            void json_modulesValue(String & ret);
                            void jsonObject_modulesValue(JsonObject & root);
                            void jsonObject_modulesValue(int pos, JsonObject & root);
                            void json_modulesValue(int pos, String & ret, boolean debug = true);
                            void json_modulesValue(String pos, String & ret);
                            void jsonObject_modulesValue(String pos, JsonObject & root);

                            void json_modulesValueList(String & ret);
                    
                            void jsonObject_domoticz_modulesValue(int pos, JsonObject & root);
                            void json_domoticz_modulesValue(int pos, String & ret, boolean debug = true);
                            void jsonObject_domoticz_modulesValue(JsonObject & root);
                            void json_domoticz_modulesValue(String & ret);
                            
                            void json_mName(String & ret);      
                            void jsonObject_mName(JsonObject & root);       
                            void json_mType(String & ret);      
                            void jsonObject_mType(JsonObject & root);       
                            void jsonObject_rtype(JsonObject & object);
                            void json_rType(String & ret);  
                            void jsonObject_stype(JsonObject & object);
                            void json_sType(String & ret);

                            void getByName(String search, int & ret);
                            void getIdByName(String search, int & ret);
                            void getIdByPos(int search, int & ret);

                            void mNameToString(mModule value, String & result); 
                            void mTypeToString(mType value, String & result);   
                            void rTypeToString(relayType value, String & result);   
                            void sTypeToString(sensorType value, String & result);  


</pre>