<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	mysqli_query($con,"DELETE FROM player_positions WHERE playerId = $_POST[id]");
	mysqli_query($con,"DELETE FROM players WHERE playerId = $_POST[id]");
	mysqli_close($con);

	$url = "http://localhost/OSU/CS275/final/players.php";
	header('Location: ' . $url);
?>