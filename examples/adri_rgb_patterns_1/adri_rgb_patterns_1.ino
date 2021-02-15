#include <adri_tools_v2.h>
#include <ALS_leds_effects.h>
#include <adri_rgb_patterns.h>


programme_loop          * _programme;
playlist_management     * _playlist;

PROGMEM chooseEffectList chooseEffect [] = { 
	{chooseEffect_color},
    {chooseEffect_noise},
    {chooseEffect_noise_2},
    {chooseEffect_flock},
    {chooseEffect_bouncingBalls},
    {chooseEffect_sinusoid},
    {chooseEffect_plasma},
    {chooseEffect_fire18},
    {chooseEffect_fire},
    {chooseEffect_torch},
    {chooseEffect_rainbow_Matrix},
    {chooseEffect_rainbow_MatrixV},
    {chooseEffect_rainbow_MatrixH},
    {chooseEffect_rainbow_smoke},
    {chooseEffect_tower_h1},
    {chooseEffect_tower_h2},
    {chooseEffect_tower_h3},
};
uint8_t chooseEffectCnt = ARRAY_SIZE(chooseEffect);
void setup()
{
			_playlist       = new playlist_management(); 
			_programme      = new programme_loop(); 
			_programme->patternList_initialize(chooseEffectList_cnt);
			for (int j = 0; j < chooseEffectList_cnt; ++j) {
			    _programme->patternList_item_add(adri_toolsv2Ptr_get()->ch_toString(chooseEffectList_ptr[j].name));
			}         
	
}
void loop()
{
	
}