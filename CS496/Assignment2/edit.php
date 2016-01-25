<?php

$username = $_POST['username'];
$password = $_POST['password'];
$email = $_POST['email'];
$gender = $_POST['gender'];
$checkbox = $_POST['checkbox'];
$userId = $_POST['userId'];

$mysqli = new mysqli(
	null, // host
	'***', // username
	'',     // password
	'***', // database name
	null,
	'***'
);

if($mysqli->query("UPDATE users SET `password`='$password', `email`='$email', `gender`='$gender', `checkbox`='$checkbox' WHERE userId = $userId") === TRUE) {
	$mysqli->close();
	header('Location: http://cs494-assignment2.appspot.com/home');
}
else {
	echo $mysqli->error;
}

