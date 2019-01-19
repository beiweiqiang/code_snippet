const http = require('http');
const crypto = require('crypto');

const realm = 'user';
const ACCOUNT = {
  'username': 'psw'
};

class Nonce {
  constructor() {
    this.ids = [];
  }
  generate() {
    const id = crypto.randomBytes(16).toString('hex');
    this.ids.push(id);
    return id;
  }
  find(id) {
    const idx = this.ids.findIndex(i => i === id);
    if (idx > -1) {
      this.ids.splice(idx, 1);
      return true;
    } else {
      return false;
    }
  }
}

const nonce = new Nonce();

http.createServer((request, response) => {
  // magic happens here!
  const { method, url, headers } = request;

  const { authorization } = headers;
  if (authorization) {
    const p = resolveAuthorization(authorization);
    const { params, valid } = p;
    if (!valid) {
      failAuth(response);
    } else {
      if (nonce.find(params.nonce)) {
        const str = generateStr(params.username, ACCOUNT[params.username], params.realm, method, params.uri, params.nonce);
        if (params.response === str) {
          response.statusCode = 200;
        } else {
          failAuth(response);
        }
      } else {
        failAuth(response);
      }
    }

  } else {
    failAuth(response);
  }

  response.end();

}).listen(8000);

function failAuth(resp) {
  resp.statusCode = 401;
  resp.setHeader('WWW-Authenticate', `Digest realm=${realm}, nonce=${nonce.generate()}`);
}

function generateStr(user, psw, realm, method, uri, nonce) {
  const a1 = crypto.createHash('md5').update(`${user}:${realm}:${psw}`).digest('hex');
  const a2 = crypto.createHash('md5').update(`${method}:${uri}`).digest('hex');
  return crypto.createHash('md5').update(`${a1}:${nonce}:${a2}`).digest('hex');
}

function resolveAuthorization(str) {
  const ret = { valid: true, params: {} };
  const token = 'Digest ';
  if (!str.startsWith(token)) {
    return Object.assign({}, ret, { valid: false });
  }
  const json = str.substring(token.length).split(',').map(s => s.trim()).reduce((acc, itm) => {
    const itms = itm.split('=');

    return Object.assign(acc, { [itms[0]]: itms[1].substring(1, itms[1].length - 1) });

  }, {});
  return Object.assign({}, ret, { params: json });
}






