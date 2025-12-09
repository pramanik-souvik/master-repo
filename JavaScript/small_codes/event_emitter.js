const EventEmitter = require('events');

// Custom event emitter
class Chat extends EventEmitter {}
const chat = new Chat();

// Listener 1: user joined
chat.on('join', user => {
  console.log(`${user} joined the chat.`);
});

// Listener 2: new message
chat.on('message', (user, msg) => {
  console.log(`${user}: ${msg}`);
});

// Listener 3: user left
chat.on('leave', user => {
  console.log(`${user} left the chat.`);
});

// Emit events
chat.emit('join', 'Souvik');
chat.emit('message', 'Souvik', 'Hello everyone!');
chat.emit('leave', 'Souvik');