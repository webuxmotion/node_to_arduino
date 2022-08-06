const express = require('express');
const app = express();
var SerialPort = require('serialport').SerialPort;

var port = 3000;

var arduinoCOMPort = "/dev/cu.usbserial-0001";

var arduinoSerialPort = new SerialPort({ 
  path: arduinoCOMPort,
  baudRate: 9600
});

arduinoSerialPort.on('open',function() {
  console.log('Serial Port ' + arduinoCOMPort + ' is opened.');
});

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
})

app.get('/:action', function (req, res) {
    
   var action = req.params.action || req.param('action');
    
    if(action == 'led') {
        arduinoSerialPort.write("w");
        return res.send({ on: true });
    } 
    if(action == 'off') {
        arduinoSerialPort.write("t");
        return res.send({ on: false });
    }
    
    return res.send({ action });
});

app.listen(port, function () {
  console.log('Example app listening on port http://0.0.0.0:' + port + '!');
});