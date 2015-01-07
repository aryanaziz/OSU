<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$result = mysqli_query($con,"SELECT * FROM players");
	$row_cnt = mysqli_num_rows($result);
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Players</title>
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
						<li class="active"><a href="#">Players</a></li>
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
					<h1>Players <small><?php echo $row_cnt . ' players found!'; ?></small> <a href="createPlayer.php" class="btn btn-md btn-primary">Add Player</a></h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-6 col-md-offset-3">
					<table class="table table-bordered table-hover">
						<caption>Please click on a player or team for more info!</caption>
						<thead>
							<tr>
								<th>Player Id</th>
								<th>Player Name</th>
								<th>Team Name</th>
								<th>Options</th>
							</tr>
						</thead>
						<tbody id="players">
							<?php
								while($row = mysqli_fetch_row($result)) {
									$team = mysqli_query($con,"SELECT * FROM teams WHERE teamId = $row[9]");
									$teamArray=mysqli_fetch_array($team,MYSQLI_ASSOC);
									echo '<tr><td>' . $row[0] . '</td><td><a href="player.php?id=' . $row[0] . '">' . $row[1] . ' ' . $row[2] . '</a></td><td><a href="team.php?id=' . $teamArray['teamId'] . '">' . $teamArray['teamCity'] . ' ' . $teamArray['teamName'] . '</a></td><td><form method="post" action="deletePlayer.php"><input type="hidden" name="id" value="' . $row[0] . '"><input type="submit" value="Delete" class="btn btn-sm btn-danger"></form></td></tr>';
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