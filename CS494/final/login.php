<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	if(!empty($_GET['username']) && !empty($_GET['password'])) {
		$username = mysqli_real_escape_string($con, $_GET['username']);
		$password = mysqli_real_escape_string($con, $_GET['password']);
		$result = mysqli_query($con, "SELECT id FROM users WHERE username='$username' AND password='$password'");
		$count=mysqli_num_rows($result);
		$row=mysqli_fetch_array($result,MYSQLI_ASSOC);
		if($count == 1) {
			$arr = array('success' => 'true', 'id' => $row['id']);
		}
		else {
			$arr = array('success' => 'false', 'reason' => 'Username or Password incorrect');
		}
		echo json_encode($arr);
	}

	else {
		if(empty($_GET['username'])) {
			$arr = $arr = array('success' => 'false', 'reason' => 'Username cannot be empty');
		}
		if(empty($_GET['password'])) {
			$arr = $arr = array('success' => 'false', 'reason' => 'Password cannot be empty');
		}
		echo json_encode($arr);
	}

	

	
?>