<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$countries = mysqli_query($con,"SELECT * FROM countries");
	$row_cnt = mysqli_num_rows($countries);
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS275 - Final - Countries</title>
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
						<li class="active"><a href="#">Countries</a></li>
						<li><a href="creation.php">Creation</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<div class="container" id="content">
			<div class="row">
				<div class="page-header">
					<h1>Countries <small><?php echo $row_cnt . ' Countries found!'; ?></small> <a href="createCountry.php" class="btn btn-md btn-primary">Add Country</a>
					<hr class="colorgraph">
				</div>
			</div>
			<ul>
				<?php
					while($row = mysqli_fetch_row($countries)) {
						echo '<li><a href="country.php?id=' . $row[0] . '">' . $row[1] . '</a></li>';
					}
				?>
			</ul>
		</div>
		<script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
		<script src="js/bootstrap.js"></script>
	</body>
</html>