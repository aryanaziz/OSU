var httpRequest;
if (window.XMLHttpRequest) { // Mozilla, Safari, ...
	httpRequest = new XMLHttpRequest();
} else if (window.ActiveXObject) { // IE 8 and older
	httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
}

window.onload = function() {
	if(localStorage.getItem('loggedIn') === 'true') {
		document.getElementById('userInfo').innerHTML += '<li><a href="#" onclick="logout()">Click Here to Log Out</a></li>';
		console.log("Logged In");
		if(window.location.href === 'http://aryanaziz.com/OSU/2014/Fall/CS494/final/login.html') {
			document.getElementById('loginForm').style.visibility = "hidden";
			document.getElementById('error').innerHTML += '<div class="alert alert-danger"><strong>Oh Snap!</strong> You are already logged in! Please logout if you want to login again.</div>';
		}
		if(window.location.href === 'http://aryanaziz.com/OSU/2014/Fall/CS494/final/register.html') {
			document.getElementById('registration').style.visibility = "hidden";
			document.getElementById('error').innerHTML += '<div class="alert alert-danger"><strong>Oh Snap!</strong> You are already logged in! Please logout if you want to create an account.</div>';
		}
		if(window.location.pathname === '/OSU/2014/Fall/CS494/final/results.html' || window.location.pathname === '/OSU/2014/Fall/CS494/final/movie.html' || window.location.pathname === '/OSU/2014/Fall/CS494/final/movie.php') {
			makeRequest();
			if(window.location.pathname === '/OSU/2014/Fall/CS494/final/movie.html') {
				//getReviews();
			}
		}
	}
	else {
		document.getElementById('userInfo').innerHTML += '<li><a href="login.html">Click Here to Log In</a></li>';
		if(window.location.pathname === '/OSU/2014/Fall/CS494/final/results.html' || window.location.pathname === '/OSU/2014/Fall/CS494/final/movie.html' || window.location.pathname === '/OSU/2014/Fall/CS494/final/movie.php') {
			makeRequest();
			if(window.location.pathname === '/OSU/2014/Fall/CS494/final/movie.html') {
				document.getElementById('writeReview').style.display = "none";
				document.getElementById('error').innerHTML += '<div class="alert alert-danger"><strong>Oh Snap!</strong> You must be logged in to write a review!</div>';
				//getReviews();
			}
		}
	}
}

function logout() {
	localStorage.removeItem('loggedIn');
	localStorage.removeItem('userId');
	location.reload();
}

//From NetLobo
function gup( name )
{
  name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");
  var regexS = "[\\?&]"+name+"=([^&#]*)";
  var regex = new RegExp( regexS );
  var results = regex.exec( window.location.href );
  if( results == null )
    return "";
  else
    return results[1];
}