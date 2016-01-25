<?php
	$dbhost = '***';
	$dbuser = '***';
	$dbpass = '***';
	$dbname = '***';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$username = mysqli_real_escape_string($con, $_POST['username']);
	$password = mysqli_real_escape_string($con, $_POST['password']);
	if(mysqli_query($con, "INSERT INTO cs361_user (`username`, `password_hash`) VALUES ('$username', '$password')")) {
		$result = mysqli_query($con, "SELECT * FROM cs361_user WHERE username = '$username'");
		$row=mysqli_fetch_array($result,MYSQLI_ASSOC);
		$arr = array('success' => true, 'userId' => $row['id']);
	}

	else {
		$arr = array('success' => false);
	}

	echo json_encode($arr);
?>