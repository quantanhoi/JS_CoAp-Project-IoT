'use strict';
const coap = require('coap');
const server = coap.createServer();

server.on('request', (req, res) => {
  console.log(`Received message: ${req.payload.toString()}`);

  if (req.payload.toString() === 'E') {
    res.end('received from client 1');
  }
  else if(req.payload.toString() === 'E2') {
    res.end('received from client 2')

  } else {
    res.end('unknown message');
  }
});

server.listen(() => {
  console.log('CoAP server started');
});
