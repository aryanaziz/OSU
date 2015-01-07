<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';


	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
	$percent = $_POST[percent];
	$percent = $percent / 100;
	mysqli_query($con,"UPDATE assignment6 SET `price` = `price` * $percent WHERE `category` = '$_POST[category]'");
	mysqli_close($con);

	$url = "http://aryanaziz.com/OSU/2014/Fall/CS494/assignment6/";
	header('Location: ' . $url);
?>		