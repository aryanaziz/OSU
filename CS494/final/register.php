<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$username = mysqli_real_escape_string($con, $_GET['username']);
	$password = mysqli_real_escape_string($con, $_GET['password']);
	$name = mysqli_real_escape_string($con, $_GET['name']);
	$email = mysqli_real_escape_string($con, $_GET['email']);

	//See if Username already exists
	$result = mysqli_query($con, "SELECT id FROM users WHERE username='$username'");
	$count=mysqli_num_rows($result);
	if($count == 1) {
		$arr = array('success' => 'false', 'reason' => 'username already exists');
		
	}
	else {
		if(mysqli_query($con,"INSERT INTO users (`username`, `password`, `name`, `email`) VALUES ('$username','$password','$name','$email')")) {
			$result = mysqli_query($con,"SELECT * FROM users WHERE username = '$username'");
			$row=mysqli_fetch_array($result,MYSQLI_ASSOC);
			$arr = array('success' => true, 'id' => $row['id']);
		}
		else {
			$arr = array('success' => 'false', 'reason' => 'query could not be completed');
		}
	}

	echo json_encode($arr);
?>