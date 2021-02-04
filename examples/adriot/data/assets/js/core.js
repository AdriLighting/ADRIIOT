// 	###################################################################################### VARIABLES
// 	SOCKET VARIABLES 
var socket_connect_display    = true;
var socket_display            = true;
var web_socket                = null;
var socket_connected          = false;
var socket_keep_alive_period  = 500;
var socket_keep_alive_enabled = false;
var response_display          = true;

// 	MODULES VARIABLES 
let mModulesList_Array2D = (r,c) => [...Array(r)].map(x=>Array(c).fill(0));
let mModulesValue_Array2D = (r,c) => [...Array(r)].map(x=>Array(c).fill(0));
var mModulesList_array;
var mModulesList_array_id = 8;
var mModulesValue_array;
var mModulesList_arraySize = 0;
// 	###################################################################################### ["4","prise",1,1,1,2,14,"_id"]


// 	###################################################################################### FUNCTIONS
// 	
// 	###########################################
// 	SOCKET FUNCTIONS 
// 	
function socket_initialize(){
	console.log("\n[socket_initialize]\n");
	// web_socket = new WebSocket('ws://'+document.location.host+'/ws',['arduino']);
	// web_socket = new WebSocket('ws://' + window.location.hostname + ':81/');
	web_socket = new ReconnectingWebSocket('ws://' + window.location.hostname + ':81/', ['arduino']);
	web_socket.binaryType = "arraybuffer";
	web_socket.debug = true;
	console.log('ws://'+document.location.host+'/ws\n');

	web_socket.onopen = function(e) { 
		if (socket_connect_display) console.log("\n[socket onopen]\n\t", e);
		socket_connected=true;
		socket_status_display();
		if (socket_keep_alive_enabled) keep_alive_time_out=setTimeout(socket_keep_alive, socket_keep_alive_period);
	};
	 
	web_socket.onclose = function(e){
		if (socket_connect_display) console.log("\n[socket onclose]\n\t", e);
		socket_connected=false;
		socket_status_display();
		// setTimeout(function() {  socket_init()  }, 1000);
	};
	 
	web_socket.onerror = function(e){
		if (socket_connect_display) console.log("\n[socket onerror]\n\t", e);
		socket_connected=false;
		// setTimeout(function() {  socket_init()  }, 1000);
		socket_status_display();
	};
	 
	web_socket.onmessage = function(e){
		var msg = "";
		if (e.data instanceof ArrayBuffer){
			msg = "BIN:";
			var bytes = new Uint8Array(e.data);
			for (var i = 0; i < bytes.length; i++) {
				msg += String.fromCharCode(bytes[i]);
			}
		} else {
			msg = e.data;
		}
		socket_receive(msg);
	};
}

function socket_keep_alive() {
	if (!web_socket) return;
	if (web_socket.readyState !== 1) return;
	// client_request("socket_keep_alive");
	keep_alive_time_out=setTimeout(socket_keep_alive, socket_keep_alive_period);
}

function socket_receive(msg) {
	if (socket_display) console.log("\n[socket_receive]\n\t"+msg+"\n");
	server_response(msg);
}

function socket_send(msg) {
	if (! socket_connected ) socket_initialize();
	web_socket.send(msg); 
	if (socket_display) console.log("\n[socket_send]\n\t"+msg+"\n");
}

function socket_status_display() {
	// if (socket_connected) document.getElementById('lbl_upd').value = "connected";
	// else document.getElementById('lbl_upd').value = "disconnected";
}


// 	###########################################
// 	JSON FUNCTIONS 
// 	
function hasJsonStructure(str) {
    if (typeof str !== 'string') return false;
    try {
        const result = JSON.parse(str);
        const type = Object.prototype.toString.call(result);
        return type === '[object Object]' 
            || type === '[object Array]';
    } catch (err) {
        return false;
    }
}
function safeJsonParse(str) {
    try {
        return [null, JSON.parse(str)];
    } catch (err) {
        return [err];
    }
}

function printValues(obj) {
    for(var [k, v] in obj) {
        if(obj[k] instanceof Object) {
            printValues(obj[k] );

        } else {
            document.write(obj[k] + "<br>");

        };
    }
};
// printValues(response) ;
function visit(object) {
    if (isIterable(object)) {
        forEachIn(object, function (accessor, child) {
            visit(child);
        });
    }
    else {
        var value = object;
        console.log(value);
    }
}

function forEachIn(iterable, functionRef) {
    for (var accessor in iterable) {
        functionRef(accessor, iterable[accessor]);
    }
}

function isIterable(element) {
    return isArray(element) || isObject(element);
}

function isArray(element) {
    return element.constructor == Array;
}

function isObject(element) {
    return element.constructor == Object;
}

function isUndefined(element) {
    return element == undefined;
}

// 	###########################################
// 	ARRAY FUNCTIONS
// 	
function getDim(a) {
    var dim = [];
    for (;;) {
        dim.push(a.length);

        if (Array.isArray(a[0])) {
            a = a[0];
        } else {
            break;
        }
    }
    return dim;
}

// 	###########################################
// 	REQUEST FUNCTIONS
// 	
function literal_item(name, value) {
   var x="<"+name+">"+value+"</"+name+">";
   return x;
}

function request_format_http(name, arg, value){
	var ret = "/" + name + "?&" + arg + "=" + value;
	return ret;
}
function request_format_socket(name, arg, value){
	var cmd = "&" + arg + "=" + value;
	var op 	= literal_item("op", name);
	var msg = literal_item("cmd", cmd);
	return op + msg;
}

function request_send(name, arg, value){
//	console.log(" window.location.hostname");
//	request_http("/json/currentSetting.json");
	var msg="";
	if (socket_connected) {
		msg = request_format_socket(name, arg, value);
		socket_send(msg);
	} else {
		msg = request_format_http(name, arg, value);
		request_http(msg);
	}
}

function request_http(msg){
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
	    if (this.readyState == 4 && this.status == 200) {
	       // Typical action to be performed when the document is ready:
	       document.getElementById("p1").innerHTML = xhttp.responseText;
	       server_response(xhttp.responseText);
	    }
	};
	xhttp.open("GET", msg, true);
	xhttp.send();	
}


// 	#############################################################################################
// 	######################################################################################
// 								PARSING SOCKET REQUEST RECIEVE 
								
// 	SOCKET RECEIVE DATA 
function server_response(json) {
	if (json == "{\"}") return;

	if (response_display) { console.log("\n[server_response]\n\t string:\n"+json+"\n"); }

	const [err, result] = safeJsonParse(json);
	if (err) {
		if (response_display) console.log('\tFailed to parse JSON: ' + err.message);
		return;
	}
	
	var response = JSON.parse(json);

	if (response_display) {console.log('\tjson:\n');console.log(response);console.log("\n");}

	mModulesList_array_parse(response, 0);
	mModulesValue_array_parse(response, "mValue", 0);
	mModulesValue_array_parse(response, "mValues", 0);

	gui_update(response);
}
function gui_update(json){
	html_createCard_light("replace_light");
	html_createCard_light("replace_home_light");

	html_createCard_plug_home("replace_home_plug");
	html_createCard_plug("replace_ac");

	html_createCard_temp("replace_climat");
	html_createCard_temp("replace_home_climat");

	html_cardSetValue();		
}


function json_array_parse(val) {
	for (const okey of  Object.entries(val)) {
		console.log("\t" + "\t" + okey[0]  + " : " + okey[1]);
	}
}

// 	######################################################################################
// 	JSON MODULE LISTE PARSING TO MODULE LISTE ARRAY
/*

	json from esp
	object[F("1")] 	= _name;
	object[F("2")] 	= _mName;
	object[F("3")] 	= _mType;
	object[F("4")] 	= _rType;
	object[F("5")] 	= _sType;
	object[F("6")] 	= _pin;
	object[F("7")] 	= _id;
*/
function mModulesList_array_parse(json, debug){

	var jsonObject = json["mListe"];

	if (jsonObject == undefined) return;

	mModulesList_array = mModulesList_Array2D(Object.keys(jsonObject).length,7);
	mModulesValue_array = mModulesValue_Array2D(Object.keys(jsonObject).length,3);
	mModulesList_arraySize = 0;	
	if (debug) {
		console.log(jsonObject);
		console.log(Object.keys(jsonObject).length);
		console.log("\n");
	}	
	var row = 0;
	var col = 0;
	for (const key of Object.keys(jsonObject)) {
		if (debug) console.log(key);
		mModulesList_array[row][0] = key;
		if (isObject(jsonObject[key])) {
			for (const okey of  Object.entries(jsonObject[key])) {
				col++;
				if (isObject(okey[1])) {
					if (debug) console.log("\t" + okey[0]);
					if (debug) json_array_parse(okey[1]) ;
				} else {
					if (debug) console.log("\t" + "\t" + okey[0]  + " : " + okey[1]);
					mModulesList_array[row][col] = okey[1];
				}
			}	
		}else {
			if (debug) console.log(key + " : " + jsonObject[key]);
		}
		col = 0;
		row++;
	}
	mModulesList_arraySize = getDim(mModulesList_array)[0];	

	if (debug) {
		console.log("getDim : " + mModulesList_arraySize);
		console.log(JSON.stringify(mModulesList_array)
		  .replace(/(\[\[)(.*)(\]\])/g,'[\n  [$2]\n]').replace(/],/g,'],\n  ')
		);
	}
}

// 	######################################################################################
// 	MODULE LISTE CREATE SENSOR MODULE
// 	
function html_createCard_temp(div_name){
	if (document.getElementById(div_name) == null) return;
	var cnt 	= 0;
	var html  	= "";
	var path = window.location.pathname;
	var page = path.split("/").pop();
	for (var i = 0; i < mModulesList_arraySize; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		if (mModulesList_array[i][2] == 0) {
			if (mModulesList_array[i][5] == 1) {

				if ((page == "index.html")||(page == "")) html += card_temperature_home(mModulesList_array[i][0], mModulesList_array[i][1]);
				else html += card_temperature(mModulesList_array[i][0], mModulesList_array[i][1], false);
			}
		}
	}
	document.getElementById(div_name).innerHTML = html;
}

// 	######################################################################################
// 	MODULE LISTE UPDATE GUI MODULE
// 	
function html_createCard_light(div_name){

	if (document.getElementById(div_name) == null) return;

	var cnt 	= 0;
	var cnt_2 	= 0;
	var html  	= "";
	var create	= false;
	var slider	= false;

	var path 	= window.location.pathname;
	var page 	= path.split("/").pop();
	// console.log("page : " + page);

	for (var i = 0; i < mModulesList_arraySize; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		create = false;
		slider = false;

		if (mModulesList_array[i][2] == 2) { 			// name module = luminaire
			create = true;
			// console.log("mModulesList_array[i][3] : " + mModulesList_array[i][3]);
			if (mModulesList_array[i][3] == 2) { 		// module type = lightDimmer
				slider = true;
			}			
		} else {
			if (mModulesList_array[i][2] == 1) {   		// name module = relay
				if (mModulesList_array[i][4] == 0) { 	// relay type = luminaire
					create = true;
				}
			}			
		}
		if (create) {
			mModulesList_array[cnt_2][mModulesList_array_id] = "switch-light-"+cnt;
			obj = document.getElementById("switch-card-"+cnt);
			obj.style.display  = "";
			document.getElementById("switch-title-"+cnt).innerHTML  = mModulesList_array[i][1];		
			if (slider) {
				obj = document.getElementById("switch-card-slider-"+cnt);
				if(obj!=null) obj.style.display  = "";
			}
			cnt++;				
		}
		cnt_2++;
	}
	// document.getElementById(div_name).innerHTML = html;
}
function request_card_light(name){
	for (var i = 0; i < mModulesList_arraySize; i++) {
		if (mModulesList_array[i][mModulesList_array_id] == name) {
			console.log(mModulesList_array[i][0]);
			console.log(mModulesList_array[i][1]);
			console.log(mModulesList_array[i][2]);
			console.log(mModulesList_array[i][3]);
			console.log(mModulesList_array[i][4]);
			console.log(mModulesList_array[i][5]);
			console.log(mModulesList_array[i][3]);
		}
	}
}
function html_createCard_plug_home(div_name){

	if (document.getElementById(div_name) == null) return;

	var cnt 	= 0;
	var cnt_2 	= 0;

	var html  	= "";
	var create	= false;

	var path 	= window.location.pathname;
	var page 	= path.split("/").pop();
	// console.log("page : " + page);

	for (var i = 0; i < mModulesList_arraySize; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		create = false;
		if (mModulesList_array[i][2] == 1) {   		// name module = relay
			if (mModulesList_array[i][4] == 1) { 	// relay type = luminaire
				create = true;
			}
		}			
		if (create) {
			mModulesList_array[cnt_2][mModulesList_array_id] = "switch-plug-"+cnt;
			obj = document.getElementById("switch-plug-card-"+cnt);
			obj.style.display  = "";
			document.getElementById("switch-plug-title-"+cnt).innerHTML  = mModulesList_array[i][1];		
			cnt++;				
		}
		cnt_2++;
	}
	// document.getElementById(div_name).innerHTML = html;
}
function html_createCard_plug(div_name){

	if (document.getElementById(div_name) == null) return;

	var cnt 	= 0;
	var cnt_2 	= 0;

	var html  	= "";
	var create	= false;

	var path 	= window.location.pathname;
	var page 	= path.split("/").pop();

	for (var i = 0; i < mModulesList_arraySize; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		create = false;
		if (mModulesList_array[i][2] == 1) {   		// name module = relay
			if (mModulesList_array[i][4] == 1) { 	// relay type = prise
				create = true;
			}
		}			
		if (create) {
			mModulesList_array[cnt_2][mModulesList_array_id] = "switch-plug-"+cnt;
			obj = document.getElementById("switch-card-"+cnt);
			obj.style.display  = "";
			document.getElementById("switch-title-"+cnt).innerHTML  = mModulesList_array[i][1];		
			cnt++;				
		}
		cnt_2++;

	}
	// document.getElementById(div_name).innerHTML = html;
}

// 	######################################################################################
// 	JSON MODULE VALUE PARSING TO MODULEVALUE LISTE ARRAY
// 	
function mModulesValue_array_parse(json, name, debug){
	var jsonObject = json[name];

	if (jsonObject == undefined) return;

	// mModulesList_array = mModulesList_Array2D(Object.keys(jsonObject).length,7);
	// mModulesList_arraySize = 0;	
	if (debug) {
		console.log(jsonObject);
		console.log(Object.keys(jsonObject).length);
		console.log("\n");
	}	
	var pos 	= -1;
	var vPos 	= 0;
	for (const key of  Object.keys(jsonObject)) {
		if (debug) console.log(key);
		pos = key;
		// mModulesList_array[row][0] = key;
		if (isObject(jsonObject[key])) {
			vPos = 0;
			for (const okey of  Object.entries(jsonObject[key])) {
				if (isObject(okey[1])) {
					if (debug) console.log("\t" + okey[0]);
					if (debug) json_array_parse(okey[1]) ;
				} else {
					if (debug) console.log("\t 1|" + "\t" + okey[0]  + " : " + okey[1]);
					mModulesValue_array[pos][vPos] = okey[1];
					vPos++;
				}
				
			}	
		}else {
			if (debug) console.log(key + " : " + jsonObject[key]);
		}
		
	}
	// mModulesList_arraySize = getDim(mModulesList_array)[0];	

	if (debug) {
		console.log("mModulesValue_array_parse");
		console.log("getDim : " + mModulesList_arraySize);
		console.log(JSON.stringify(mModulesValue_array)
		  .replace(/(\[\[)(.*)(\]\])/g,'[\n  [$2]\n]').replace(/],/g,'],\n  ')
		);
	}
}

// 	######################################################################################
// 	MODULE LISTE UPDATE GUI MODULE DATA
// 	
function html_cardSetValue(){
	var obj = null;
	var mName;
  for (var i = 0; i < mModulesList_arraySize; i++) { 
  		mName = mModulesList_array[i][2];
  		if ((mName == 1 ) || (mName == 2)) {
  			obj = document.getElementById(mModulesList_array[i][mModulesList_array_id]);
			if (obj != null) {
				if (mModulesValue_array[i][0] === true) {
					$('[data-unit="' + mModulesList_array[i][mModulesList_array_id] + '"]').addClass("active");
					$("#" + mModulesList_array[i][mModulesList_array_id]).prop('checked', true);
					$("#" + mModulesList_array[i][mModulesList_array_id]).closest("label").addClass("checked");
				} else {
					$('[data-unit="' + mModulesList_array[i][mModulesList_array_id] + '"]').removeClass("active");
					$("#" + mModulesList_array[i][mModulesList_array_id]).prop('checked', false);
					$("#" + mModulesList_array[i][mModulesList_array_id]).closest("label").removeClass("checked");
				}
			}	  			
  		}
  		if (mName == 0) {
          	obj = document.getElementById("sensor-temp-C-"+mModulesList_array[i][0]);
            if (obj != null) obj.innerHTML  = mModulesValue_array[i][0];
            obj = document.getElementById("sensor-temp-F-"+mModulesList_array[i][0]);
            if (obj != null) obj.innerHTML  = mModulesValue_array[i][1];	  			
  		}
  }
}
function toggleCheckbox(_id){
    // obj = document.getElementById("switch-light-"+_id);
    //  if (obj != null){ 
    //  	var check = obj.checked;
    //  	console.log(check);
    //  	iot.switchSingle("switch-light-"+_id, !check);	
    //  }
}

function card_temperature_data(nbr_id, tempC, tempF){
  document.getElementById("sensor-temp-C-"+nbr_id).innerHTML  = tempC;
  document.getElementById("sensor-temp-F-"+nbr_id).innerHTML  = tempF;
}




// 	######################################################################################
// 	GUI FUNCTIONS
// 	
// 	CREATE DEFAULT STATIC SWITCH MODULE 
function html_createCardSwitch(div_name, cnt, slider, name, ico, rgbPicker){
	if (document.getElementById(div_name) == null) return;
  	var html = "";
  	for (var i = 0; i < cnt; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		html += card_switch(i, "switch-light-"+i, slider, name, ico, rgbPicker);
	}
    document.getElementById(div_name).innerHTML = html;
}
function html_createCardSwitch_home(div_name, cnt){
	if (document.getElementById(div_name) == null) return;
  	var html = "";
  	for (var i = 0; i < cnt; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		html += card_switch_home(i, "switch-light-"+i);
	}
    document.getElementById(div_name).innerHTML = html;
}
function html_createCardSwitch_plug_home(div_name, cnt){
	if (document.getElementById(div_name) == null) return;
  	var html = "";
  	for (var i = 0; i < cnt; i++) { // {"mType":{"0":"sensor","1":"relay"}}
		html += card_switch_plug_home(i, "switch-light-"+i);
	}
    document.getElementById(div_name).innerHTML = html;
}
// 	INITIIALISE
function gui_initialize(){
	html_createCardSwitch("replace_rgb", 10, true,'colorpicker', 'bulb-eco', true);



	// 		let text = new ColorPicker(document.getElementById('text'), '#1a00ad');
 // var cars = ["Saab", "text", "BMW"]; 

	// 		for (var i = 0; i < 2; i++) {
	// 			if (document.getElementById(cars[i]) == null) continue;
	// 			document.getElementById(cars[i]).addEventListener('colorChange', function () {
	// 				console.log(event.detail);
	// 				document.getElementById('te').style.color = event.detail.color.hexa;
	// 			});				
	// 		}
			
			for (var i = 0; i < 10; i++) {
				// if (document.getElementById("switch-card-rgb-colorpicker-"+i) == null) continue;
				let text = new ColorPicker(document.getElementById("switch-card-rgb-colorpicker-"+i), '#1a00ad');
				document.getElementById("switch-card-rgb-colorpicker-"+i).addEventListener('colorChange', function () {
					console.log(event.detail);
					// document.getElementById('te').style.color = event.detail.color.hexa;
				});				
			}	
	html_createCardSwitch("replace_light", 10, true,'light', 'bulb-eco', false);
	html_createCardSwitch("replace_ac", 10, true,'plug', 'appliances', false);
	html_createCardSwitch_home("replace_home_light", 10);
	html_createCardSwitch_plug_home("replace_home_plug", 10);
}


// 	###################################################################################### 
//	INITIIALISE JS
//	
socket_initialize();
gui_initialize();
