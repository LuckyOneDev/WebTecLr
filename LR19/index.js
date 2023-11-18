var http = require('http');
var fs = require('fs');
var path = require('path');

function getMimeType(extention) {
    console.log(extention);
    switch (extention) {
        case '.html':
            return 'text/html';
            break;
        case '.js':
            return 'text/javascript';
            break;
        case '.css':
            return 'text/css';
            break;
        case '.json':
            return 'application/json';
            break;
        case '.png':
            return 'image/png';
            break;      
        case '.jpg':
            return 'image/jpg';
            break;
        case '.webp':
            return 'image/webp';
        case '.wav':
            return 'audio/wav';
            break;
        case '.ico':
            return 'image/x-icon';
            break;
    }
}

http.createServer(function (request, response) {
    console.log('request starting...');

    var filePath = '.' + request.url;
    if (filePath == './') filePath = './index.html';

    var fileExtension = path.extname(filePath);
    var mimeType = getMimeType(fileExtension);

    fs.readFile(filePath, function(error, content) {
        if (error) {
            if(error.code == 'ENOENT'){
                fs.readFile('./notfound.html', function(error, content) {
                    response.writeHead(404, { 'Content-Type': "text/html" });
                    response.end(content, 'utf-8');
                });
            }
        }
        else {
            response.writeHead(200, { 'Content-Type': mimeType });
            response.end(content, 'utf-8');
        }
    });

}).listen(8080);
