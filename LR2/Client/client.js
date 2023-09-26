const net = require('net');
const Logger = require('./logger');
const fs = require('fs');
const config = require('./config.json')
var logger = new Logger("client.log");
var client = new net.Socket();

client.on('data', function(data) {
	logger.log('Received: ' + data);
	client.destroy();
});

client.on('close', function() {
	logger.log('Connection closed');
});

setTimeout(main, 1066);

function main() {
	client.connect(config.port, config.address, function() {
		logger.log('Client connected');
		setTimeout(() => {
			client.write('Mokshin Ivan Nikolayevich');
			logger.log('Sent message');
		}, 500);
	});
}