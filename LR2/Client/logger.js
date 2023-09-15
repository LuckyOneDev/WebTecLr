const fs = require("fs");

class Logger {
  constructor(fileName) {
    this.file = fs.createWriteStream(fileName, { flags: "a" });
  }

  log(message) {
    console.log(message);
    this.file.write(`[${new Date().toISOString()}] ${message}\n`);
  }

  close() {
    this.file.end();
  }
}

module.exports = Logger;
