<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$coachId = $_GET['id'];

	$result = mysqli_query($con,"SELECT * FROM coaches WHERE coachId = $coachId");
	$coachArray=mysqli_fetch_array($result,MYSQLI_ASSOC);

	if($coachArray['teamId'] > 0) {
		$team = mysqli_query($con,"SELECT * FROM teams WHERE teamId = {$coachArray['teamId']}");
		$teamArray=mysqli_fetch_array($team,MYSQLI_ASSOC);
	}
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Player</title>
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
						<li class="active"><a href="coaches.php">Coaches</a></li>
						<li><a href="teams.php">Teams</a></li>
						<li><a href="positions.php">Positions</a></li>
						<li><a href="countries.php">Countries</a></li>
						<li><a href="creation.php">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1> <?php echo $coachArray['coachFirstName'] . ' ' . $coachArray['coachLastName'] . ' '; ?><form style="display: inline-block;" method="post" action="deleteCoach.php"><input type="hidden" name="id" value="<?php echo $coachArray['coachId']; ?>"><input type="submit" value="Delete" class="btn btn-md btn-danger"></form></h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-6 col-md-offset-3">
					<h3>Information</h3>
					<ul>
						<li><strong>Current Team:</strong><?php echo '<a href="team.php?id=' . $teamArray['teamId'] . '">' . $teamArray['teamCity'] . ' ' . $teamArray['teamName'] . '</a>'; ?></li>
					</ul>
				</div>
			</div>
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
	</body>
</html>