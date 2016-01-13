/*
*	
*	Description Bluetooth connection and two slider controller app for the Brozabot_mk1 
*	by Jose Marco de la Rosa
*
*/

var vel, dir, stop = false;

// Connect BT
var btClient = network.bluetooth.connectSerial(function(status) {
        console.log("connected " + status);
});

var var0 = ui.addText("Reset", 0, 70);

var btn = ui.addButton("Stop", 0, 100, 500, 100).onClick(function(){
    //console.log("Stop");
    stop = true;
});

var var0 = ui.addText("Speed", 0, 280);

var slider = ui.addSlider(0, 310, 500, 100, 30, 70).onChange(function(val) { 
    //console.log("Speed: "+val);
    vel = val;
});
slider.setValue(50);

var var0 = ui.addText("Steering", 0, 440);

var slider2 = ui.addSlider(0, 470, 500, 100, 0, 100).onChange(function(val) { 
    dir = val;
    //console.log("Steering: "+dir);
});
slider2.setValue(50);

ui.addButton("Disconnect", 0, 0).onClick(function() {
    btClient.disconnect();
});

var loop = util.loop( 100, function(){
    btClient.send( parseInt(vel)+","+parseInt(dir)+"\n" );
    
    if (stop) {
        slider.setValue(50);
        slider2.setValue(50);
        stop = false;
    }
});

loop.start();
