const dgram = require('dgram');
const server = dgram.createSocket('udp4');

server.on('listening', () => {
  const address = server.address();
  console.log(`UDP server listening on ${address.address}:${address.port}`);
});

server.on('message', (msg, rinfo) => {
  console.log(`Received message: ${msg} from ${rinfo.address}:${rinfo.port}`);
  server.send(msg, rinfo.port, rinfo.address, (error) => {
    if (error) {
      console.error(`Error sending message: ${error}`);
    } else {
      console.log(`Message sent back to ${rinfo.address}:${rinfo.port}`);
    }
  });
});
const port = 8888;
const hostname = 'localhost';
server.bind(port);
