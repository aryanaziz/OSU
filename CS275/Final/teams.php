<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$conferences = mysqli_query($con,"SELECT * FROM conferences");
	$divisions = mysqli_query($con,"SELECT * FROM divisions");
	$teams = mysqli_query($con,"SELECT * FROM teams");
	$conference_cnt = mysqli_num_rows($conferences);
	$division_cnt = mysqli_num_rows($divisions);
	$team_cnt = mysqli_num_rows($teams);
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Teams</title>
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
						<li class="active"><a href="#">Teams</a></li>
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
					<h1>Teams <small><?php echo $conference_cnt . ' Conferences found, ' . $division_cnt . ' Divisions found, and ' . $team_cnt . ' Teams found.'; ?> <br><a href="createConference.php" class="btn btn-md btn-primary">Add Conference</a> <a href="createDivision.php" class="btn btn-md btn-primary">Add Division</a> <a href="createTeam.php" class="btn btn-md btn-primary">Add Team</a></h1>
					<hr class="colorgraph">
				</div>
			</div>
			<?php
			$dbhost = 'localhost';
			$dbuser = 'root';
			$dbpass = 'mysql';
			$dbname = 'CS275Final';
			$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

			$conferences = mysqli_query($con,"SELECT * FROM conferences");
			while($row = mysqli_fetch_row($conferences)) {
				echo '<div class="row"><div class="well"><h1>' . $row[1] . ' Conference</h1>';
				$divisions = mysqli_query($con,"SELECT * FROM divisions WHERE conferenceId = $row[0]");
				while($row2 = mysqli_fetch_row($divisions)) {
					echo '<div class="panel panel-primary"><div class="panel-heading"><h3 class="panel-title">' . $row2[1] . '</h3></div><div class="panel-body"><ul>';
					$teams = mysqli_query($con,"SELECT * FROM teams WHERE divisionId = $row2[0]");
					while($row3 = mysqli_fetch_row($teams)) {
						echo '<li><a href="team.php?id=' . $row3[0] .'">' . $row3[1] . ' ' . $row3[2] . '</a></li>';
					}
					echo '</ul></div></div>';
				}

				echo '</div></div>';
			}
			?>
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
	</body>
</html>