<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$playerId = $_GET['id'];

	$result = mysqli_query($con,"SELECT * FROM players WHERE playerId = $playerId");
	$playerArray=mysqli_fetch_array($result,MYSQLI_ASSOC);

	$country = mysqli_query($con,"SELECT * FROM countries WHERE countryId = {$playerArray['countryId']}");
	$countryArray=mysqli_fetch_array($country,MYSQLI_ASSOC);

	$team = mysqli_query($con,"SELECT * FROM teams WHERE teamId = {$playerArray['teamId']}");
	$teamArray=mysqli_fetch_array($team,MYSQLI_ASSOC);

	$positions = mysqli_query($con,"SELECT * FROM player_positions WHERE playerId = {$playerArray['playerId']}");
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
						<li class="active"><a href="players.php">Players</a></li>
						<li><a href="coaches.php">Coaches</a></li>
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
					<h1> <?php echo $playerArray['playerFirstName'] . ' ' . $playerArray['playerLastName'] . ' '; ?><form style="display: inline-block;" method="post" action="deletePlayer.php"><input type="hidden" name="id" value="<?php echo $playerArray['playerId']; ?>"><input type="submit" value="Delete" class="btn btn-md btn-danger"></form></h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-4" style="text-align: center;">
					<img src="http://a.espncdn.com/combiner/i?img=/i/headshots/nba/players/full/<?php echo $playerArray['playerESPNId']; ?>.png&w=350&h=254" />
				</div>
				<div class="col-md-8">
					<h3>Information</h3>
					<ul>
						<li><strong>Number:</strong> <?php echo $playerArray['playerNumber']; ?></li>
						<li><strong>Height:</strong> <?php echo floor($playerArray['playerHeight'] / 12) . 'ft ' . $playerArray['playerHeight'] % 12 . 'in'; ?></li>
						<li><strong>Weight:</strong> <?php echo $playerArray['playerWeight'] . 'lbs'; ?></li>
						<li><strong>Date Of Birth:</strong><?php echo $playerArray['playerDOB']; ?></li>
						<li><strong>Country Of Birth:</strong><?php echo '<a href="country.php?id=' . $countryArray['countryId'] .'">' . $countryArray['countryName'] . '</a>'; ?></li>
						<li><strong>Current Team:</strong><?php echo '<a href="team.php?id=' . $teamArray['teamId'] . '">' . $teamArray['teamCity'] . ' ' . $teamArray['teamName'] . '</a>'; ?></li>
					
						<li><strong>Positions Played:</strong>
							<?php
									while($row = mysqli_fetch_row($positions)) {
										$positionName = mysqli_query($con,"SELECT * FROM positions WHERE positionId = $row[2]");
										$positionArray=mysqli_fetch_array($positionName,MYSQLI_ASSOC);
										echo '<a href="position.php?id=' . $positionArray['positionId'] . '">' . $positionArray['positionAbbrev'] . '</a> ';
									}
							?>
						</li>
					</ul>
				</div>
			</div>
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
	</body>
</html>