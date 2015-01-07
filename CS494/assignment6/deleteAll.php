<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';


	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
	mysqli_query($con,"TRUNCATE TABLE assignment6");

	mysqli_close($con);

	$url = "http://aryanaziz.com/OSU/2014/Fall/CS494/assignment6/";
	header('Location: ' . $url);
?>		