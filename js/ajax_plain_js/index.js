var siteId = 'xxxx';
var api = 'https://a7it3ymo7g.execute-api.us-west-2.amazonaws.com/dev/midas/product.query/v1';

var xmlhttp = new XMLHttpRequest();
xmlhttp.open("POST", api, true);
xmlhttp.setRequestHeader("Content-Type", "application/json");
xmlhttp.send(JSON.stringify({
  siteId: siteId
}));
xmlhttp.onreadystatechange = function() {
  if (this.readyState === 4 && this.status === 200) {
    const response = JSON.parse(this.responseText);
    // todo...
  }
};
