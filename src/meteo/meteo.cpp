#include "meteo.h"


void meteo_update(boolean WifiConnected){
	if (!WifiConnected) return;

	httpGetJsonReaderCurrent reader;

	apiMod = API_MOD_OPENWATHERMAP;
	reader.updateCurrentById("http://api.openweathermap.org/data/2.5/weather?id=6612251&appid=603ef62761eb23b76ac8c8af7711776f&units=metric&lang=fr");
	httpGetJsonReader_print(openWeatherMapList_key, openWeatherMapList_keyCount, "METEO", 50, "openweather");
	
	// apiMod = API_MOD_WEATHERBIT;
	// reader.updateCurrentById("http://api.weatherbit.io/v2.0/current?city_id=2972214&lang=fr&key=b1b971c226e641e58ea0b0872058fca9");
	// httpGetJsonReader_print(weatherbitList_key, weatherbitList_keyCount, "METEO", 50, "weatherbit");	
}
unsigned long 	meteo_update_loop_timer;
unsigned int  	meteo_update_loop_timer_max = 3600000L;
void meteo_update_loop(boolean WifiConnected){
	if ( ((millis()-meteo_update_loop_timer)>meteo_update_loop_timer_max) ) {
		meteo_update(WifiConnected);
		meteo_update_loop_timer=millis();
	}  
}

String getMeteoconIcon_1(String icon) {
	// clear sky
	// 01d
	if (icon == "01d") 	{
		return "B";
	}
	// 01n
	if (icon == "01n") 	{
		return "B";
	}
	// few clouds
	// 02d
	if (icon == "02d") 	{
		return "H";
	}
	// 02n
	if (icon == "02n") 	{
		return "H";
	}
	// scattered clouds
	// 03d
	if (icon == "03d") 	{
		return "N";
	}
	// 03n
	if (icon == "03n") 	{
		return "N";
	}
	// broken clouds
	// 04d
	if (icon == "04d") 	{
		return "Y";
	}
	// 04n
	if (icon == "04n") 	{
		return "Y";
	}
	// shower rain
	// 09d
	if (icon == "09d") 	{
		return "R";
	}
	// 09n
	if (icon == "09n") 	{
		return "R";
	}
	// rain
	// 10d
	if (icon == "10d") 	{
		return "Q";
	}
	// 10n
	if (icon == "10n") 	{
		return "Q";
	}
	// thunderstorm
	// 11d
	if (icon == "11d") 	{
		return "P";
	}
	// 11n
	if (icon == "11n") 	{
		return "P";
	}
	// snow
	// 13d
	if (icon == "13d") 	{
		return "W";
	}
	// 13n
	if (icon == "13n") 	{
		return "W";
	}
	// mist
	// 50d
	if (icon == "50d") 	{
		return "M";
	}
	// 50n
	if (icon == "50n") 	{
		return "M";
	}
	// Nothing matched: N/A
	return ")";

}
// String getMeteoconIcon_weather bit(String iconText) {
//   if (iconText == "200")    return "tstorms";
//   if (iconText == "201")    return "tstorms";
//   if (iconText == "202")    return "tstorms";
//   if (iconText == "230")    return "tstorms";
//   if (iconText == "231")    return "tstorms";
//   if (iconText == "232")    return "tstorms";
//   if (iconText == "233")    return "tstorms";

//   if (iconText == "300")    return "chanceflurries";
//   if (iconText == "301")    return "flurries";
//   if (iconText == "302")    return "flurries";

//   if (iconText == "500")    return "chancerain";
//   if (iconText == "501")    return "rain";
//   if (iconText == "502")    return "rain";

//   if (iconText == "511")    return "rain";

//   if (iconText == "520")    return "rain";
//   if (iconText == "521")    return "rain";
//   if (iconText == "522")    return "rain";

//   if (iconText == "600")    return "chancesnow";
//   if (iconText == "601")    return "snow";
//   if (iconText == "602")    return "snow";
//   if (iconText == "610")    return "snow";

//   if (iconText == "611")    return "chancesleet";
//   if (iconText == "612")    return "sleet";

//   if (iconText == "621")    return "snow";
//   if (iconText == "622")    return "snow";

//   if (iconText == "623")    return "flurries";
	
//   if (iconText == "623")    return "flurries";

//   if (iconText == "208")    return "fog";
//   if (iconText == "209")    return "hazy";
//   if (iconText == "210")    return "mostlycloudy";
//   if (iconText == "211")    return "mostlysunny";
//   if (iconText == "212")    return "partlycloudy";
//   if (iconText == "213")    return "partlysunny";
//   if (iconText == "214")    return "sleet";
//   if (iconText == "215")    return "rain";
//   if (iconText == "216")    return "snow";
//   if (iconText == "B")    return "sunny";
//   if (iconText == "P")    return "tstorms";
//   return "unknown";
// }
String getMeteoconIcon_2(String iconText) {
	if (iconText == "F") return "chanceflurries";
	if (iconText == "Q") return "chancerain";
	if (iconText == "W") return "chancesleet";
	if (iconText == "V") return "chancesnow";
	if (iconText == "S") return "chancetstorms";
	if (iconText == "B") return "clear";
	if (iconText == "Y") return "cloudy";
	if (iconText == "F") return "flurries";
	if (iconText == "M") return "fog";
	if (iconText == "E") return "hazy";
	if (iconText == "Y") return "mostlycloudy";
	if (iconText == "H") return "mostlysunny";
	if (iconText == "H") return "partlycloudy";
	if (iconText == "J") return "partlysunny";
	if (iconText == "W") return "sleet";
	if (iconText == "R") return "rain";
	if (iconText == "W") return "snow";
	if (iconText == "B") return "sunny";
	if (iconText == "P") return "tstorms";
	if (iconText == "N") return "cloudy";
	return "unknown";
}

String getMeteoconIcon_3(String iconText){
		String s_1 = getMeteoconIcon_1(iconText);
		// Serial.printf("\ngetMeteoconIcon_3 1: %s\n", s_1.c_str());
		String s_2 = getMeteoconIcon_2(s_1);
		// Serial.printf("\ngetMeteoconIcon_3 2: %s\n", s_2.c_str());
		return s_2;
}