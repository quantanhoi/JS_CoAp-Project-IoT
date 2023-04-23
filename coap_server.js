'use strict';
const coap = require('coap');
const server = coap.createServer();

server.on('request', (req, res) => {
  console.log(`Received message: ${req.payload.toString()}`);

  if (req.payload.toString() === 'E') {
    res.end('received from client 1\n');
  }
  else if(req.payload.toString() === 'E2') {
    res.end('received from client 2\n')

  } else {
    res.end('unknown message\n');
  }
});

server.listen(() => {
  console.log('CoAP server started');
});
