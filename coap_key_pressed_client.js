const coap = require('coap');
const keypress = require('keypress');

// Make `process.stdin` begin emitting "keypress" events
console.log("Listening to keypress...");
keypress(process.stdin);

// Listen for 'E' keypress
process.stdin.on('keypress', (ch, key) => {
  if (key && key.name !== 'q') {
    // Create a CoAP request
    const req = coap.request('coap://localhost');

    req.on('response', (res) => {
      res.pipe(process.stdout);
      res.on('end', () => {
      });
    });

    // Send the 'E' key message
    req.end(`${key.name}`);
  }

  // Exit the program when 'q' is pressed
  if (key && key.name === 'q') {
    process.exit(0);
  }
});

// Allow the program to keep running and listening for keypress events
process.stdin.setRawMode(true);
process.stdin.resume();
