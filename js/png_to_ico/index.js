const fs = require('fs');
const pngToIco = require('png-to-ico');

pngToIco('./logo.png')
  .then(buf => {
    fs.writeFileSync('app.ico', buf);
  })
  .catch(console.error);
