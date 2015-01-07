<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$query = $_GET['query'];

	$result = mysqli_query($con,"SELECT * FROM players INNER JOIN teams ON teams.teamId = players.teamId WHERE playerFirstName LIKE '$query' OR playerLastName LIKE '$query'");
	$row_cnt = mysqli_num_rows($result);
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Index</title>
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
						<li><a href="creation.php">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1>Search Results <small><?php echo $row_cnt . ' results found!'; ?></h1>
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
								<th>Position Name</th>
								<th>Team</th>
							</tr>
						</thead>
						<tbody id="results">
							<?php
								while($row = mysqli_fetch_row($result)) {
									echo '<tr><td>' . $row[0] . '</td><td><a href="player.php?id=' . $row[0] . '">' . $row[1] . ' ' . $row[2] . '</a></td><td><a href="team.php?id=' . $row[10] . '">' . $row['11'] . ' ' . $row['12'] . '</a></td></tr>';
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