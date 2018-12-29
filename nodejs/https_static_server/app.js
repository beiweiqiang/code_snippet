/**
 ＃生成私钥key文件
 openssl genrsa 1024 > /path/to/private.pem
 ＃通过私钥文件生成CSR证书签名
 openssl req -new -key /path/to/private.pem -out csr.pem
 ＃通过私钥文件和CSR证书签名生成证书文件
 openssl x509 -req -days 365 -in csr.pem -signkey /path/to/private.pem -out /path/to/file.crt
 */

var express = require('express');
var https = require('https');
var http = require('http');
var fs = require('fs');

// This line is from the Node.js HTTPS documentation.
var options = {
  key: fs.readFileSync('/Users/beiweiqiang/Downloads/ssl/private.pem'),
  cert: fs.readFileSync('/Users/beiweiqiang/Downloads/ssl/private.crt')
};

// Create a service (the app object is just a callback).
var app = express();

app.use(express.static('public'));

// Welcome
// app.get('/', function(req, res) {
//   if(req.protocol === 'https') {
//     res.status(200).send('Welcome to Safety Land!');
//   }
//   else {
//     res.status(200).send('Welcome!');
//   }
// });

// Create an HTTP service.
http.createServer(app).listen(8080);
// Create an HTTPS service identical to the HTTP service.
https.createServer(options, app).listen(8081);
