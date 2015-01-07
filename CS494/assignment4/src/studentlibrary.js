var httpRequest;
if (window.XMLHttpRequest) { // Mozilla, Safari, ...
    httpRequest = new XMLHttpRequest();
} else if (window.ActiveXObject) { // IE 8 and older
    httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
}

function ajaxRequest(URL, Type, Parameters) {
  var parameterString = '';
  for (var key in Parameters) {
    if (Parameters.hasOwnProperty(key)) {
      parameterString += encodeURIComponent(key) + '=' +
      encodeURIComponent(Parameters[key]);
    }
    parameterString += '&';
  }
  var stringLength = parameterString.length;
  stringLength -= 1;
  parameterString = parameterString.substr(0, stringLength);

  if (Type == 'POST') {
    var responseObject = {};
    httpRequest.onreadystatechange = function() {
      if (httpRequest.readyState === 4) {
        if (httpRequest.status >= 200 && httpRequest.status <= 226) {
          responseObject['success'] = true;
          responseObject['code'] = httpRequest.status;
          responseObject['codeDetail'] = httpRequest.statusText;
          responseObject['response'] = httpRequest.responseText;
        }
        else {
          responseObject['success'] = false;
          responseObject['code'] = httpRequest.status;
          responseObject['codeDetail'] = httpRequest.statusText;
          responseObject['response'] = httpRequest.responseText;
        }
      }
    };
    httpRequest.open('POST', URL, false);
    httpRequest.setRequestHeader('Content-Type',
    'application/x-www-form-urlencoded');
    httpRequest.send(parameterString);
    return responseObject;
  }

  else if (Type == 'GET') {
    var responseObject = {};
    httpRequest.onreadystatechange = function() {
      if (httpRequest.readyState === 4) {
        if (httpRequest.status >= 200 && httpRequest.status <= 226) {
          responseObject['success'] = true;
          responseObject['code'] = httpRequest.status;
          responseObject['codeDetail'] = httpRequest.statusText;
          responseObject['response'] = httpRequest.responseText;
        }
        else {
          responseObject['success'] = false;
          responseObject['code'] = httpRequest.status;
          responseObject['codeDetail'] = httpRequest.statusText;
          responseObject['response'] = httpRequest.responseText;
        }
      }
    };
    var fullURL = URL + '?' + parameterString;
    httpRequest.open('GET', fullURL, false);
    httpRequest.send(null);
    return responseObject;
  }

  else {
    console.log('Please enter a valid Request type.');
    return null;
  }
}

function alertContents() {

}

function localStorageExists() {
  if (window.localStorage != undefined) {
    return true;
  }
  else {
    return false;
  }
}
