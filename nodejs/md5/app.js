const data = "do shash'owania";
const crypto = require('crypto');
crypto.createHash('md5').update(data).digest("hex");