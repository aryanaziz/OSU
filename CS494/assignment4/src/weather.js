var httpRequest;
if (window.XMLHttpRequest) { // Mozilla, Safari, ...
    httpRequest = new XMLHttpRequest();
} else if (window.ActiveXObject) { // IE 8 and older
    httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
}

function getWeatherData() {
  var parameterString = '';
  var city = document.getElementById('cityInput').value;
  var state = document.getElementById('stateInput').value;
  parameterString += city + ',' + state;
  var fullURL = 'http://api.openweathermap.org/data/2.5/weather?q=' +
  parameterString + '&units=imperial';
  httpRequest.onreadystatechange = alertContents;
  httpRequest.open('GET', fullURL);
  httpRequest.send();
}

function alertContents() {
  var cityOutputDiv = document.getElementById('cityOutput');
  var stateOutputDiv = document.getElementById('stateOutput');
  var windSpeedOutputDiv = document.getElementById('windOutputSpeed');
  var windDirectionOutputDiv = document.getElementById('windOutputDirection');
  var maxTempOutputDiv = document.getElementById('maxTempOutput');
  var minTempOutputDiv = document.getElementById('minTempOutput');
  var currentTempOutputDiv = document.getElementById('currentTempOutput');

  cityOutputDiv.innerHTML = '';
  stateOutputDiv.innerHTML = '';
  windSpeedOutputDiv.innerHTML = '';
  windDirectionOutputDiv.innerHTML = '';
  maxTempOutputDiv.innerHTML = '';
  minTempOutputDiv.innerHTML = '';
  currentTempOutputDiv.innerHTML = '';
  if (httpRequest.readyState === 4) {
    if (httpRequest.status === 200) {
      var response = JSON.parse(httpRequest.responseText);

      cityOutputDiv.innerHTML += document.getElementById('cityInput').value;
      stateOutputDiv.innerHTML += document.getElementById('stateInput').value;

      if (document.getElementById('windInput').checked == true) {
        windSpeedOutputDiv.innerHTML += response.wind.speed;
        windDirectionOutputDiv.innerHTML += response.wind.deg;
      }
      else {
        windSpeedOutputDiv.innerHTML += 'You have not selected this data point';
      }

      if (document.getElementById('maxTempInput').checked == true) {
        maxTempOutputDiv.innerHTML += response.main.temp_max;
      }
      else {
        maxTempOutputDiv.innerHTML += 'You have not selected this data point';
      }

      if (document.getElementById('minTempInput').checked == true) {
        minTempOutputDiv.innerHTML += response.main.temp_min;
      }
      else {
        minTempOutputDiv.innerHTML += 'You have not selected this data point';
      }

      if (document.getElementById('currentTempInput').checked == true) {
        currentTempOutputDiv.innerHTML += response.main.temp_min;
      }
      else {
        currentTempOutputDiv.innerHTML +=
          'You have not selected this data point';
      }
    }
  }
}

function saveLocalStorage() {
  localStorage.setItem('city', document.getElementById('cityInput').value);
  localStorage.setItem('state', document.getElementById('stateInput').value);
  localStorage.setItem('displayWind',
    document.getElementById('windInput').checked);
  localStorage.setItem('displayMaxTemp',
    document.getElementById('maxTempInput').checked);
  localStorage.setItem('displayMinTemp',
    document.getElementById('minTempInput').checked);
  localStorage.setItem('displayCurrTemp',
    document.getElementById('currentTempInput').checked);
}

function loadLocalStorage() {
  document.getElementById('cityInput').value = localStorage.getItem('city');
  document.getElementById('stateInput').value = localStorage.getItem('state');
  if (localStorage.getItem('displayWind') == 'true') {
    document.getElementById('windInput').checked = true;
  }
  if (localStorage.getItem('displayMaxTemp') == 'true') {
    document.getElementById('maxTempInput').checked = true;
  }
  if (localStorage.getItem('displayMinTemp') == 'true') {
    document.getElementById('minTempInput').checked = true;
  }
  if (localStorage.getItem('displayCurrTemp') == 'true') {
    document.getElementById('currentTempInput').checked = true;
  }
}
