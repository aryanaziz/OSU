<?php
	$dbhost = '***';
	$dbuser = '***';
	$dbpass = '***';
	$dbname = '***';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$result = mysqli_query($con,"SELECT * FROM cs361_user");

	while($row = mysqli_fetch_row($result)) {
		$arr = array('id' => $row[0], 'username' => $row[1], 'password_hash' => $row[2]);
		$jsonData[] = $arr;
	}

	echo json_encode($jsonData);
?>