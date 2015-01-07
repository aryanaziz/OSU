<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$result = mysqli_query($con,"SELECT * FROM positions");
	$row_cnt = mysqli_num_rows($result);
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Positions</title>
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
						<li class="active"><a href="#">Positions</a></li>
						<li><a href="countries.php">Countries</a></li>
						<li><a href="creation.php">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1>Positions <small><?php echo $row_cnt . ' Positions found!'; ?></small> <a href="createPosition.php" class="btn btn-md btn-primary">Add Position</a> </h1>
					<hr class="colorgraph">
				</div>
			</div>
			<div class="row">
				<div class="col-md-6 col-md-offset-3">
					<table class="table table-bordered table-hover">
						<caption>Please click on a position for more info!</caption>
						<thead>
							<tr>
								<th>Position Id</th>
								<th>Position Name</th>
								<th>Position Abbreviation</th>
							</tr>
						</thead>
						<tbody id="positions">
							<?php
								while($row = mysqli_fetch_row($result)) {
									echo '<tr><td>' . $row[0] . '</td><td><a href="position.php?id=' . $row[0] . '">' . $row[1] . '</a></td><td>' . $row[2] . '</td></tr>';
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