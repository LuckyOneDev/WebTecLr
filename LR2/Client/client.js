var net = require('net');
const Logger = require('./logger');

var logger = new Logger("client.log");
var client = new net.Socket();
client.connect(8888, '127.0.0.1', function() {
	logger.log('Client connected');
    setTimeout(() => {
        client.write('Hello, server! Love, Client.');
		logger.log('Sent message');
    }, 500);
});

client.on('data', function(data) {
	logger.log('Received: ' + data);
	client.destroy();
});

client.on('close', function() {
	logger.log('Connection closed');
});