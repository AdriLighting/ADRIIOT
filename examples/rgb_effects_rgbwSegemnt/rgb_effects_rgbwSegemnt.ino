// #include <adri_leds_strip_neo.h>

/*

    #include <Arduino.h>
    #include <FastLED.h>
    #include <adri_timer.h>
    #include <ArduinoJson.h>
    #include <adri_tools.h>
    #include <adri_leds_colors.h>

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <adri_rgb_patterns.h>
#include <adri_rgb_effects.h>
#include <adri_tools.h>

    leds<D4 /* NOT USED */, GRB /* NOT USED */>     myLed(
                                                            110 /*110  nbr leds */, 
                                                            D1 /* leds data pin */, 
                                                            NEO_GRBW + NEO_KHZ800 /* leds order */ 
    );

    leds_setting * _leds_setting;
    PROGMEM chooseEffectList chooseEffect [] = { 
        {chooseEffect_color},

        {chooseEffect_pride},
        {chooseEffect_prideSyncro},

        {chooseEffect_colorpalette},
        {chooseEffect_colorpalette_syncro},

        {chooseEffect_colorwave},
        {chooseEffect_colorwaveSyncro},
        
        {chooseEffect_amrmoire_staticrnd},
        {chooseEffect_amrmoire_statichue},
        {chooseEffect_amrmoire_cychue},

        {chooseEffect_cw},
        {chooseEffect_cwrevinv},
        {chooseEffect_cwrnd},
        {chooseEffect_breath},
        // {chooseEffect_fade},
        // {chooseEffect_neorainbow},
        // {chooseEffect_neorainbowcycle},
        {chooseEffect_multidynamic},

        // {chooseEffect_neo_wave},
        // {chooseEffect_neo_rainbow},


    };
    uint8_t chooseEffectCount = ARRAY_SIZE(chooseEffect);

programme_loop          * _programme;
playlist_management     * _playlist;
effect_manager          * _effect_manager;
adriTools_serialRead    * _serial;

String _serial_effectsSettingToSerial(String cmd, String value){
    effectIdInstance()->settingToSerial();
    Serial.println(F("__"));    
}
String _serial_effectsSettingSav(String cmd, String value){
    uint8_t pos = effect_manager_instance()->activeEffectIndex();
    effect_manager_sav(pos);
}
String _serial_effectsPrintList(String cmd, String value){
    effect_manager_instance()->print_list();
}
String _serial_ESPreset(String cmd, String value){
    ESP.restart();
}
String _serial_activateEffect(String cmd, String value) {
   effect_manager_instance()->activateEffect(value.toInt()); 
}
String _serial_log(String cmd, String value) {
   fsprintf("\n[LOG]\n");
}
String _serial_settingFromSerial(String cmd, String value) {
    effectIdInstance()->settingFromSerial(cmd, value, true);
}
String _serial_menu(String cmd, String value) {
    adriTools_serialReadPtr_get()->menu();
}
void setup()
{
        Serial.begin(115200);
        Serial.println("");
        delay(1000);


        WiFi.persistent(false);
        WiFi.disconnect(true);
        WiFi.setPhyMode(WIFI_PHY_MODE_11N);
        wifi_set_sleep_type(NONE_SLEEP_T);

        SPIFFS.begin();



        _serial = new adriTools_serialRead();
        _serial->cmd_array(1, 5);
        _serial->cmd_item_add(1, "effectsPrintList",        "a", "", _serial_effectsPrintList);
        _serial->cmd_item_add(1, "effectsSettingToSerial",  "z", "", _serial_effectsSettingToSerial);
        _serial->cmd_item_add(1, "effectsSettingSav",       "e", "", _serial_effectsSettingSav);
        _serial->cmd_item_add(1, "effects_print_list",      "q", "", _serial_ESPreset);
        _serial->cmd_item_add(1, "menu",                    "m", "", _serial_menu);
        _serial->cmd_array(2, 2);
        _serial->cmd_item_add(2, "activateEffect",    "p",    "", _serial_activateEffect);
        _serial->cmd_item_add(2, "log",               "log",  "", _serial_log);

        _serial->cmd_3("&", "settingFromSerial", _serial_settingFromSerial);
        _serial->menu();

        chooseEffect_update(chooseEffect, chooseEffectCount);



        _playlist       = new playlist_management(); 

        /*
        programme_loop
        control les class 
                            pattern_list = création et gestion des items
                            pattern_loop = rotation des items
        */
        _programme      = new programme_loop(); 

        // création de linstance 'pattern_list'   
        // création de linstance 'pattern_loop'   
        _programme->patternList_initialize(chooseEffectCount);

        // ajout des effets a la list de patterns pour l'instance 'pattern_list'
        for (int j = 0; j < chooseEffectCount; ++j) {
            _programme->patternList_item_add(ch_toString(chooseEffect[j].name));
        }         
         _programme->patternList_print();



        _leds_setting = new leds_setting(&myLed);
        neoStripArray_get()->setBrightness(60); 

        leds_segment * setSeg = leds_settingPtr_get()->_segments;
        setSeg->segemnt_new(0,                      (myLed._num_leds/2),    true    );
        setSeg->segemnt_new((myLed._num_leds/2),    myLed._num_leds,        false   );


        RGBeffecPalette_ptr_get()->palette_init();  
        _effect_manager = new effect_manager();
        

        effect_manager_instance()->activateEffect(0);

        pInitHeap     = ESP.getFreeHeap() ;

}
void patterns_loop(){
    programme_loop * ptr = programmeLoop_instance();

    static mod_pattern_loop pat_check   = ptr->patternLoop_statuDefault();
    static String           pat_name    = "";
    static boolean          playlist;

    ptr->loop(pat_check, pat_name, playlist);                
    if (pat_check == ptr->patternLoop_statuNext()) {

        // _setting->_effect_play = true;

        pat_check =  ptr->patternLoop_statuDefault();

        effect_manager_instance()->changeEffectByName(pat_name);

        // _updateCleint->patterns_loop(pat_name + " vient d'étre activé");

        // #ifdef DEBUG
            fsprintf("\n[lamp_server::patterns_loop]\n%s\n", pat_name.c_str());

            #ifdef PATHEAPSTATS
                if (heap_pass>=2) patternList_instance()->heapStats_print();
            #else
                String ret;
                heapStatsPatternLoop_print(ret);

                Serial.print(ret);

            #endif
        // #endif

        // lampSettingInstance()->savRequiered_effect();

    }

}

void loop()
{
    patterns_loop();
    effect_manager_instance()->loop();    
    _serial->loop(); 
}
