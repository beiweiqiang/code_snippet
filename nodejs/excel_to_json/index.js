
'use strict';
const excelToJson = require('convert-excel-to-json');

const result = excelToJson({
  sourceFile: './chinese.xlsx'
});

const json = {};
result['Sheet1'].map(item => {
  json[item['A']] = item['B']
});

console.log('app.js: 9 ->  -> ', JSON.stringify(json));


