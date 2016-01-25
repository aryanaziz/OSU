<?php
	$dbhost = '***';
	$dbuser = '***';
	$dbpass = '***';
	$dbname = '***';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$userId = 1; //Assuming UserId would be pulled from the session?
	$activityName = mysqli_real_escape_string($con, $_POST['activity']);
	$result = mysqli_query($con, "SELECT * FROM cs361_activity WHERE activity_name = '$activityName'");
		$row= mysqli_fetch_array($result,MYSQLI_ASSOC);
		$activityId = $row['id'];
	$duration = mysqli_real_escape_string($con, $_POST['duration']);
	$intensity = mysqli_real_escape_string($con, $_POST['intensity']);
	$date = mysqli_real_escape_string($con, $_POST['date']);

	if(mysqli_query($con, "INSERT INTO cs361_activity_record (`user_id`, `activity_id`, `duration`, `intensity`, `date_done`) VALUES ('$userId', '$activityId', $duration, '$intensity', '$date')")) {
		$arr = array('success' => true, 'entryId' => mysqli_insert_id($con));
	}
	else {
		$arr = array('success' => false);
	}

	echo json_encode($arr);
?>