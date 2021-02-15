#include "patterns.h"


char arp_fsprintf_buufer[255];


uint32_t pInitHeap;

#ifdef PATHEAPSTATS

	heap_stats * heapStatArray[30];

	int heap_recall = 0;
	int heap_lastPos = -1;
	int heap_newPos = -1;
	int heap_pass = 0;

void pattern_list::heapStats_print(){
	arp_fsprintf("\n[pattern_list::heapStats_print]\n");
	String 		s;
	String 		pName;
	uint32_t 	tMax 	= 0;
	uint32_t 	tMin 	= 0;
	uint32_t 	tTime 	= 0;
	uint32_t 	tIte 	= 0;
	for (int i = 0; i < _maxcnt; i++) { 
		heap_stats * p = heapStatArray[i];
		heap_stats_get(p, "", s);
		if(p->_heap_total 	> 0) tMax 	+= p->_heap_total;
		if(p->_timer_total	> 0) tTime 	+= p->_timer_total;
		if(p->_iteration 	> 0) tIte 	+= p->_iteration;
		arp_fsprintf("%s\n", s.c_str());
	}	

	static 	int tcnt 	= 0;
	static 	int ttot 	= 0;
	static	int tused 	= 0;
			if (pInitHeap > ESP.getFreeHeap()) 	tused = (pInitHeap - ESP.getFreeHeap());
	static	int trest 	= 0;
			if (ESP.getFreeHeap() > tMax) 		trest = (ESP.getFreeHeap() - tMax);
			tcnt++;
			ttot+=tused;
	arp_fsprintf("[TOTAL] ite:%5d heap-total:%7d heap-rest:%7d heap-moy:%7d - heap-used:%7d |%d/%d|%d| init:%7d free:%7d duration:%5s\n",
		tIte,
		tMax,
		trest,
		tMax/tIte,
		tused,
		ttot,
		tcnt,
		ttot/tcnt,
		pInitHeap,
		ESP.getFreeHeap(),
		on_time(tTime).c_str()
	);

}

heap_stats::heap_stats(String name){
	_initial 		= ESP.getFreeHeap();
	_name 			= name;
}
void heap_stats::start(){
	_heap_befor 	= ESP.getFreeHeap();
	_timer_befor 	= millis();	
}
void heap_stats::end(){
		_heap_after 	= ESP.getFreeHeap() ;

		// if (_iteration > 0) { // no calculation 1st time, because time between init and 1st run may be very long


			int curr=0;

			if (_heap_befor > _heap_after) curr = _heap_befor-_heap_after;
			else {
			// if(_iteration>0) curr = _heap_last;
			}

			_heap_last 	= curr;

			_heap_total += curr;

			// arp_fsprintf("\n_name : %s\n", _name.c_str());
			// arp_fsprintf("_heap_befor : %d\n", _heap_befor);
			// arp_fsprintf("_heap_after : %d\n", _heap_after);
			// arp_fsprintf("curr : %d\n", curr);
			// arp_fsprintf("_heap_total : %d\n", _heap_total);
			// 
			// if (_iteration>0) {
			// 
				if (_heap_total>0) _heap_moy = _heap_total / (_iteration+1);

				if (curr>_heap_max)					_heap_max=curr;
				if ((curr>0) && (curr<_heap_max)) 	_heap_min=curr;			
			// }


			_timer_duration = millis() - _timer_befor;
			_timer_total += _timer_duration;		
		// }

		_iteration++;	
}

void heap_stats_get(heap_stats * heap_stat, String _name, String & value) {
	char buf[200];
	sprintf(buf, "%-40s\tite:%5d befor:%5d after:%5d\t heap [mean:%5d min:%5d max:%5d last:%5d] - duration [last:%10s total:%10s] init : %5d",
		heap_stat->_name.c_str(), 
		heap_stat->_iteration, 
		heap_stat->_heap_befor, 
		heap_stat->_heap_after, 
		heap_stat->_heap_moy,
		heap_stat->_heap_min,
		heap_stat->_heap_max,
		heap_stat->_heap_last,
		on_time(heap_stat->_timer_duration).c_str(),
		on_time(heap_stat->_timer_total).c_str(),
		heap_stat->_initial
	);	
	value = String(buf);
}
#else
	void heapStatsPatternLoop_print(String & ret){
		// arp_fsprintfs("\n[heapStatsPatternLoop_print]\n");

		char buffer[255];

		static 	int tcnt 	= 0;
		static 	int ttot 	= 0;
		static	int tused 	= 0;
				if (pInitHeap > ESP.getFreeHeap()) 	tused = (pInitHeap - ESP.getFreeHeap());
				tcnt++;
				ttot+=tused;
		sprintf(buffer, "\n[heapStatsPatternLoop_print]\n\theap-used:%7d |%d/%d|%d| init:%7d free:%7d \n",
			tused,
			ttot,
			tcnt,
			ttot/tcnt,
			pInitHeap,
			ESP.getFreeHeap()
		);

		ret = String(buffer);	
	}
#endif

void heapStats_print(){
	arp_fsprintf("\n[heapStatsPatternLoop_print]\n");

	static	int tused 	= 0;
			if (pInitHeap > ESP.getFreeHeap()) 	tused = (pInitHeap - ESP.getFreeHeap());


	arp_fsprintf("\tused:%-10d pInitHeap: %-10d getFreeHeap: %-10d\n",
		tused,
		pInitHeap,
		ESP.getFreeHeap()
	);
}





pattern_list * patternList_ptr;

pattern_list::pattern_list(uint8_t maxCnt){
	patternList_ptr = this;
	_listName 	= new String[maxCnt];
	_maxcnt 	= maxCnt;
}

uint8_t pattern_list::item_add(String value){
	#ifdef PATHEAPSTATS
		heapStatArray[_initialize_cnt] = new heap_stats(value);
	#endif
	#ifdef DEBUG
		arp_fsprintf("\n[pattern_list::item_add]pos: %d name: %S\n", _initialize_cnt, value.c_str());
	#endif
	_listName[_initialize_cnt] = value;
	_initialize_cnt++;
	return _initialize_cnt;
}

void pattern_list::print(){
	arp_fsprintf("\n[pattern_list::print]\n");
	for (int i = 0; i < _maxcnt; ++i)
	{
		arp_fsprintf("[%5d] - %s\n", i, _listName[i].c_str());
	}
}

void pattern_list::item_getName(String & value, uint8_t pos){
	value = _listName[pos];
}
void pattern_list::item_getRandomName(String & value){
	value = _listName[random(0, _maxcnt)];
}

int pattern_list::item_getPosByName(String search){
	int ret = -1;
	for (int i = 0; i < _maxcnt; i++) {
		if ( _listName[i] == search) {
			ret = i;
			break;
		}
	}
	return ret;
}
boolean pattern_list::item_getPosByName(String search, int & result){
	result = -1;
	for (int i = 0; i < _maxcnt; i++) {
		if ( _listName[i] == search) {
			result = i;
			break;
		}
	}
	if (result == -1) return false; else return true;
}

void pattern_list::jsonObject(JsonObject & root){
	for (int i = 0; i < _maxcnt; i++) {
		root[String(i)] = _listName[i] ;
	}
}


int patternList_itemGetPosByName(pattern_list * ptr, String search) {return ptr->item_getPosByName(search);}

void 			patternList_setPtr(pattern_list * ptr) 	{patternList_ptr = ptr;}
pattern_list 	* patternList_instance() 				{return patternList_ptr;}





pattern_loop * patternLoop_ptr;

pattern_loop 	* patternLoop_instance() 				{return patternLoop_ptr;}
void 			patternLoop_setPtr(pattern_loop * ptr) 	{patternLoop_ptr = ptr;}

pattern_loop::pattern_loop(pattern_list * ptr){
	patternLoop_ptr = this;
	_timer 			= new adri_timer(_delayCurrent*1000, "pattern delay", true);
	_patterns_list 	= ptr;
}

void pattern_loop::loop(mod_pattern_loop & mod, String & v1){
	String name;


	if ( !isPlaying() ) {
		return;
	} 

	if (_timer->loop(_delayCurrent*1000)) {

		#ifdef PATHEAPSTATS
			heap_pass++;

			heap_lastPos = _pos;
		#endif

		loop_next();

		#ifdef PATHEAPSTATS
			heap_newPos = _pos;
		#endif

		_patterns_list->item_getName(name, _pos);

		// arp_fsprintf("\n[pattern_loop::loop] : next item set to : [%d] - %s\n", _pos, name.c_str());


		mod		= mpl_next;
		v1 		= name;		
	}
}

void pattern_loop::loop_next(){
	if (_random) 	rnd();
	else 			next();
}
void pattern_loop::next(){
	_pos++;
	if (_pos > _posMax) _pos = _posMin;
}
void pattern_loop::prev(){
	_pos--;
	if (_pos < _posMin) _pos = _posMax;
}
void pattern_loop::rnd(){
	_pos = random(_posMin, _posMax);
	if (_pos > _posMax) _pos = _posMin;
}

void pattern_loop::pattern_set(boolean dir){
	if (dir) 	next();
	else 		prev();
}

boolean pattern_loop::isPlaying() 		{return _play;}
boolean pattern_loop::isRndPlaying() 	{return _random;}

mod_pattern_loop pattern_loop::statuDefault() 	{return mpl_off;}
mod_pattern_loop pattern_loop::statuNext() 		{return mpl_next;}

void pattern_loop::pos_set 		(uint8_t value){_pos 	= value;}
void pattern_loop::posMin_set 	(uint8_t value){_posMin = value;}
void pattern_loop::posMax_set 	(uint8_t value){_posMax = value;}

void pattern_loop::pos_get 		(uint8_t & value){value = _pos;}
void pattern_loop::posMin_get 	(uint8_t & value){value = _posMin;}
void pattern_loop::posMax_get 	(uint8_t & value){value = _posMax;}

void pattern_loop::delay_get 		(uint32_t 	& value) 	{value = _delay;}
void pattern_loop::delayCurrent_get (uint32_t 	& value) 	{value = _delayCurrent;}
void pattern_loop::delayManual_get 	(boolean 	& value) 	{value = _delayManual;}

void pattern_loop::play_set	 			(boolean 	value){_play 			= value;}
void pattern_loop::playRnd_set 			(boolean 	value){_random 			= value;}

void pattern_loop::delayCurrent_set 	(uint32_t 	value){_delayCurrent 	= value;}
void pattern_loop::delay_set 			(uint32_t 	value){_delay 			= value;}
void pattern_loop::delayManual_set 		(boolean 	value){_delayManual 	= value;}


