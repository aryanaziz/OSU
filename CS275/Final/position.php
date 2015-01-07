<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$positionId = $_GET['id'];

	$info = mysqli_query($con,"SELECT * FROM positions WHERE positions.positionId = $positionId");
	$infoArray=mysqli_fetch_array($info,MYSQLI_ASSOC);
	$result = mysqli_query($con,"SELECT * FROM positions INNER JOIN player_positions ON positions.positionId = player_positions.positionId INNER JOIN players ON players.playerId = player_positions.playerId INNER JOIN teams ON players.teamId = teams.teamId WHERE positions.positionId = $positionId");
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Position</title>
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
						<li class="active"><a href="positions.php">Positions</a></li>
						<li><a href="countries.php">Countries</a></li>
						<li><a href="creation.php">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1><?php echo $infoArray['positionName']; ?> </h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-6 col-md-offset-3">
					<table class="table table-bordered table-hover">
						<caption>Please click on a position for more info!</caption>
						<thead>
							<tr>
								<th>Player Id</th>
								<th>Player Name</th>
								<th>Team</th>
							</tr>
						</thead>
						<tbody id="player_positions">
							<?php
								while($row = mysqli_fetch_row($result)) {
									echo '<tr><td>' . $row[4] . '</td><td><a href="player.php?id=' . $row[4] . '">' . $row[7] . ' ' . $row[8] . '</td><td><a href="team.php?id=' . $row[16] . '">' . $row[17] . ' ' . $row[18] . '</td></tr>';
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