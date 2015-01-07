<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$teams = mysqli_query($con,"SELECT * FROM teams LEFT JOIN coaches on coaches.teamId = teams.teamId WHERE coachId IS NULL");
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Coach Creation</title>
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
					<h1>Coach Creation</h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-8 col-md-offset-2">
					<div id="error"></div>
					<form method="get" action="create.php">
						<input type="hidden" name="type" value="coach">
						<input type="text" name="firstName" required="" class="form-control" placeholder="Coach First Name">
						<br>
						<input type="text" name="lastName" required="" class="form-control" placeholder="Coach Last Name">
						<br>
						<p>Please note, there must be a team without a coach for any teams to appear in this dropdown (1 to 1 relationship). If there are no teams, coach will be created as a Free Agent</p>
						<select name="team" class="form-control">
						<?php
							while($row = mysqli_fetch_array($teams)) {
								echo '<option value="' . $row[0] . '">' . $row[1] . ' ' . $row[2] . '</option>';
							}
						?>
						</select>
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
					document.getElementById('error').innerHTML += '<div class="alert alert-danger">Something went wrong. Please try again.</div>';
				}
			}
		</script>
	</body>
</html>