<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';


	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
	mysqli_query($con,"DELETE FROM assignment6 WHERE id = $_POST[id]");
	mysqli_close($con);

	$url = "http://aryanaziz.com/OSU/2014/Fall/CS494/assignment6/";
	header('Location: ' . $url);
?>		