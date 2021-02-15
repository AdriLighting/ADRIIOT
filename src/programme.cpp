#include "programme.h"

programme_loop * programmeLoop_ptr;

programme_loop::programme_loop(){
	
}


		
void programme_loop::patternList_initialize(uint8_t maxCnt){
	programmeLoop_ptr = this;
	_patterns_list 	= new pattern_list(maxCnt);
	_patterns 		= new pattern_loop(_patterns_list);
}

void programme_loop::patternList_item_add(String value){
	uint8_t cnt = _patterns_list->item_add(value);
	_patterns->posMax_set(cnt-1);
}
void programme_loop::patternList_item_getName(String & value, uint8_t pos){
	_patterns_list->item_getName(value, pos);
}

boolean programme_loop::patternList_itemGetPosByName(String search, int & result){
	return _patterns_list->item_getPosByName(search, result);
}
boolean programme_loop::pattern_list_changeEffect(String search, int & result){
	if (patternList_itemGetPosByName(search, result)){
		_patterns->pos_set(result);
		return true;
	}
	return false;
}
void programme_loop::patternList_randomEffect(String & ret){
	uint8_t pos=0;
	String value;	
	_patterns->rnd();
	_patterns->pos_get(pos);
	_patterns_list->item_getName(ret, pos);
	// lampServer_instance()->lampEffects_instance()->changeEffectByName(value);
}
boolean programme_loop::pattern_list_changeEffect(boolean dir, String & ret){
	_patterns->pattern_set(dir);
	uint8_t pos;
	_patterns->pos_get(pos);
	String value;
	_patterns_list->item_getName(ret, pos);
	// lampServer_instance()->lampEffects_instance()->changeEffectByName(value);
}
void programme_loop::patternList_print(){
	_patterns_list->print();
}
void programme_loop::patternList_jsonObject(JsonObject & root){
	_patterns_list->jsonObject(root);
}





mod_pattern_loop 	programme_loop::patternLoop_statuDefault()	{return _patterns->statuDefault();}
mod_pattern_loop 	programme_loop::patternLoop_statuNext() 	{return _patterns->statuNext();}
boolean 			programme_loop::patternLoop_isPlaying() 	{return _patterns->isPlaying();}
boolean 			programme_loop::patternLoop_isRndPlaying() 	{return _patterns->isRndPlaying();}

void programme_loop::patternLoop_delay_get 			(uint32_t & value) 	{_patterns->delay_get(value);}
void programme_loop::patternLoop_delayCurrent_get	(uint32_t & value) 	{_patterns->delayCurrent_get(value);}
void programme_loop::patternLoop_delayManual_get 	(boolean & value) 	{_patterns->delayManual_get(value);}

void programme_loop::patternLoop_posMin_get 		(uint8_t & value) 	{_patterns->posMin_get(value);}
void programme_loop::patternLoop_posMax_get 		(uint8_t & value) 	{_patterns->posMax_get(value);}

void programme_loop::patternLoop_pos_get 			(uint8_t & value) 	{_patterns->pos_get(value);}


void programme_loop::patternLoop_pos_set 			(uint8_t pos) 		{_patterns->pos_set(pos);}
void programme_loop::patternLoop_play_set			(boolean pos) 		{_patterns->play_set(pos);}
void programme_loop::patternLoop_playRnd_set		(boolean pos) 		{_patterns->playRnd_set(pos);}
void programme_loop::patternLoop_delay_set 			(int pos) 			{_patterns->delay_set(pos);}
void programme_loop::patternLoop_delayCurrent_set	(int pos) 			{_patterns->delayCurrent_set(pos);}
void programme_loop::patternLoop_delayManual_set	(boolean pos) 		{_patterns->delayManual_set(pos);}

void programme_loop::patternLoop_autoPlay () {
	if (patternLoop_isPlaying()) 	patternLoop_play_set(false);
	else 							patternLoop_play_set(true);
}
void programme_loop::patternLoop_autoPlayRnd () {

	if (patternLoop_isRndPlaying()) 	patternLoop_playRnd_set(false);
	else 								patternLoop_playRnd_set(true);
}


void programme_loop::loop(mod_pattern_loop & mod, String & v1, boolean & _playList){
	// boolean _playList;
	playlist_statu(_playList);

	if (_playList) 	playlist_instance()->item_loop(_patterns, mod, v1);
	else 			_patterns->loop(mod, v1);
}


programme_loop * programmeLoop_instance(){return programmeLoop_ptr;}
