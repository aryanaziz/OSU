<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$teams = mysqli_query($con,"SELECT * FROM teams");
	$positions = mysqli_query($con,"SELECT * FROM positions");
	$countries = mysqli_query($con,"SELECT * FROM countries");
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Player Creation</title>
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
					<h1>Player Creation</h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-8 col-md-offset-2">
					<form method="get" action="create.php">
						<input type="hidden" name="type" value="player">
						<input type="text" name="firstName" required="" class="form-control" placeholder="Player First Name">
						<br>
						<input type="text" name="lastName" required="" class="form-control" placeholder="Player Last Name">
						<br>
						<input type="text" name="height" required="" class="form-control" placeholder="Player Height (in inches)">
						<br>
						<input type="text" name="weight" required="" class="form-control" placeholder="Player Weight (in pounds)">
						<br>
						<input type="text" name="number" required="" class="form-control" placeholder="Player Number">
						<br>
						<input type="text" name="espn" class="form-control" placeholder="ESPN ID (used for profile picture) - Can be left blank">
						<br>
						<input type="text" name="dob" required="" class="form-control" placeholder="DOB - yyyy-mm-dd">
						<br>
						<select name="team" class="form-control">
						<?php
							while($row = mysqli_fetch_array($teams)) {
								echo '<option value="' . $row[0] . '">' . $row[1] . ' ' . $row[2] . '</option>';
							}
						?>
						</select>
						<br>
						You can select multiple positions
						<select multiple name="positions[]" class="form-control">
						<?php 
							while($row = mysqli_fetch_array($positions)) {
								echo ' <option value="' . $row[0] . '">' . $row[1] . '</option>';
							}
						?>
						</select>
						<br>
						<select name="country" class="form-control">
						<?php
							while($row = mysqli_fetch_array($countries)) {
								echo ' <option value="' . $row[0] . '">' . $row[1] . '</option>';
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
	</body>
</html>