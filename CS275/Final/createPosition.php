<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Position Creation</title>
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="css/bootstrap.css">
	</head>
	<body>
		<nav class="navbar navbar-default navbar-fixed-top" role="navigation">
			<div class="container">
				<div class="navbar-header">
					<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
						<span class="sr-only">Toggle Navigation</span>
						<span class="icon-bar"></span>
						<span class="icon-bar"></span>
						<span class="icon-bar"></span>
					</button>
					<a class="navbar-brand" href="index.php">NBA Database</a>
				</div>
				<div id="navbar" class="collapse navbar-collapse">
					<ul class="nav navbar-nav">
						<li><a href="players.php">Players</a></li>
						<li><a href="coaches.php">Coaches</a></li>
						<li><a href="teams.php">Teams</a></li>
						<li><a href="positions.php">Positions</a></li>
						<li><a href="countries.php">Countries</a></li>
						<li class="active"><a href="#">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1>Position Creation</h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-8 col-md-offset-2">
					<div id="error"></div>
					<form method="get" action="create.php">
						<input type="hidden" name="type" value="position">
						<input type="text" name="name" required="" class="form-control" placeholder="Position Name">
						<br>
						<input type="text" name="abbrev" required="" class="form-control" placeholder="Position Abbrev">
						<br>
						<input type="submit" class="btn btn-block btn-md btn-primary" value="Create">
					</form>
				</div>
			</div>
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
		<script src="js/site.js"></script>
		<script>
			window.onload = function() {
				var error = gup('error');
				if(error == 1) {
					document.getElementById('error').innerHTML += '<div class="alert alert-danger">Position Abbrev must be unique. Please try again.</div>';
				}
			}
		</script>
	</body>
</html>