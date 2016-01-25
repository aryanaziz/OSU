<?php
	$dbhost = '***';
	$dbuser = '***';
	$dbpass = '***';
	$dbname = '***';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$triggerAmount =  $_POST['trigger']; 

	$result = mysqli_query($con,"UPDATE cs361_triggers SET trigger_amount = $triggerAmount WHERE user_id = 1");

	header('Location: http://aryanaziz.com/OSU/2015/CS361/trigger.php');
?>