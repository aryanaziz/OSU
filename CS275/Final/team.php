<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$teamId = $_GET['id'];

	$teamInfo = mysqli_query($con,"SELECT * FROM teams INNER JOIN divisions ON divisions.divisionId = teams.divisionId INNER JOIN conferences ON conferences.conferenceId = divisions.conferenceId WHERE teams.teamId = $teamId");
	$resultArray=mysqli_fetch_array($teamInfo,MYSQLI_ASSOC);
	$coachInfo = mysqli_query($con,"SELECT * FROM coaches WHERE teamId = $teamId");
	$coachArray = mysqli_fetch_array($coachInfo,MYSQLI_ASSOC);
	$result2 = mysqli_query($con,"SELECT * FROM teams INNER JOIN players ON players.teamId = teams.teamId INNER JOIN divisions ON divisions.divisionId = teams.divisionId INNER JOIN conferences ON divisions.conferenceId = conferences.conferenceId INNER JOIN coaches ON coaches.teamId = teams.teamId INNER JOIN countries ON countries.countryId = players.countryId WHERE teams.teamId = $teamId");
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Team</title>
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
						<li class="active"><a href="teams.php">Teams</a></li>
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
					<h1><?php echo $resultArray['teamCity'] . ' ' . $resultArray['teamName']; ?></h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-3">
					<h3>Team Info</h3>
					<li><strong>City:</strong> <?php echo $resultArray['teamCity'] ?></li>
					<li><strong>Name:</strong> <?php echo $resultArray['teamName'] ?></li>
					<li><strong>Division:</strong> <a href="teams.php"><?php echo $resultArray['divisionName']; ?></a></li>
					<li><strong>Conference:</strong> <a href="teams.php"><?php echo $resultArray['conferenceName']; ?></a></li>
					<li><strong>Head Coach:</strong> <a href="coach.php?id=<?php echo $coachArray['coachId']; ?>"><?php echo $coachArray['coachFirstName'] . ' ' . $coachArray['coachLastName']; ?></a></li>
				</div>
				<div class="col-md-9">
					<table class="table table-bordered table-hover">
						<caption>Please click on any link for more info!</caption>
						<thead>
							<tr>
								<th>Player Id</th>
								<th>Player Name</th>
								<th>Player Number</th>
								<th>Height</th>
								<th>Weight</th>
								<th>DOB</th>
								<th>Country Of Birth</th>
								<th>Position(s)</th>
							</tr>
						</thead>
						<tbody id="players">
							<?php
								while($row = mysqli_fetch_row($result2)) {
									echo '<tr><td>' . $row[4] . '</td><td><a href="player.php?id=' . $row[4] . '">' . $row[5] . ' ' . $row[6] . '</td><td>' . $row[7] . '</td><td>' . floor($row[8] / 12) . 'ft ' . $row[8] % 12 . 'in</td><td>' . $row[9] . 'lbs</td><td>' . $row[10] . '</td><td><a href="country.php?id=' . $row[23] . '">' . $row[24] . '</a></td><td>';
									$result3 = mysqli_query($con,"SELECT * FROM player_positions INNER JOIN positions ON player_positions.positionId = positions.positionId WHERE playerId = $row[4]");
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
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
	</body>
</html>