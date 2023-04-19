'using strict';
const coap = require('coap');
const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const sendButtonPress = () => {
  const req = coap.request('coap://localhost');

  req.write('E');
  req.on('response', (res) => {
    console.log(`Server response: ${res.payload.toString()}`);
    promptForInput();
  });

  req.end();
};

const promptForInput = () => {
  rl.question("Press 'E' and hit Enter to send button press, or 'Q' to quit: ", (input) => {
    if (input === 'E') {
      sendButtonPress();
    } else if (input === 'Q') {
      console.log('Exiting...');
      rl.close();
    } else {
      console.log('Invalid input');
      promptForInput();
    }
  });
};

promptForInput();
