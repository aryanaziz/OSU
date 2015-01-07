<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$countryId = $_GET['id'];

	$result = mysqli_query($con,"SELECT * FROM countries WHERE countries.countryId = $countryId");
	$resultArray=mysqli_fetch_array($result,MYSQLI_ASSOC);
	$result2 = mysqli_query($con,"SELECT * FROM countries INNER JOIN players ON players.countryId = countries.countryId INNER JOIN teams ON teams.teamId = players.teamId WHERE countries.countryId = $countryId");
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Country</title>
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
						<li class="active"><a href="countries.php">Countries</a></li>
						<li><a href="creation.php">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1><?php echo $resultArray['countryName']; ?></h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="col-md-8 col-md-offset-2">
				<table class="table table-bordered table-hover">
					<caption>Please click on any link for more info!</caption>
					<thead>
						<tr>
							<th>Player Id</th>
							<th>Player Name</th>
							<th>Height</th>
							<th>Weight</th>
							<th>DOB</th>
							<th>Team</th>
							<th>Position(s)</th>
						</tr>
					</thead>
					<tbody id="players">
						<?php
							while($row = mysqli_fetch_row($result2)) {
								echo '<tr><td>' . $row[2] . '</td><td><a href="player.php?id=' . $row[2] . '">' . $row[3] . ' ' . $row[4] . '</td><td>' . floor($row[6] / 12) . 'ft ' . $row[6] % 12 . 'in</td><td>' . $row[7] . 'lbs</td><td>' . $row[8] . '</td><td><a href="team.php?id=' . $row[11] . '">' . $row[13] . ' ' . $row[14] . '</a></td><td>';
								$result3 = mysqli_query($con,"SELECT * FROM player_positions INNER JOIN positions ON player_positions.positionId = positions.positionId WHERE playerId = $row[2]");
								while($row3 = mysqli_fetch_row($result3)) {
									echo '<a href="position.php?id=' . $row3[2] . '">' . $row3[5] . '</a> ';
								}
								echo '</td></tr>';
							}						
						?>
					</tbody>
				</table>
			</div>
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
	</body>
</html>