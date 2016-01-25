<?php
	$dbhost = '***';
	$dbuser = '***';
	$dbpass = '***';
	$dbname = '***';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$result = mysqli_query($con,"SELECT * FROM cs361_activity_record");

	while($row = mysqli_fetch_row($result)) {
		$arr = array('id' => $row[0], 'user_id' => $row[1], 'activity_id' => $row[2], 'duration' => $row[3], 'intensity' => $row[4], 'date_done' => $row[5]);
		$jsonData[] = $arr;
	}

	echo json_encode($jsonData);
?>