<?php

$username = $_POST['username'];
$password = $_POST['password'];
$email = $_POST['email'];
$gender = $_POST['gender'];
$checkbox = $_POST['checkbox'];


$mysqli = new mysqli(
	null, // host
	'***', // username
	'',     // password
	'***', // database name
	null,
	'***'
);

//echo "$username<br>$password<br>$email<br>$gender<br>$checkbox<br>";

if($mysqli->query("INSERT INTO users (`username`, `password`, `email`, `gender`, `checkbox`) VALUES ('$username', '$password', '$email', '$gender', '$checkbox')") === TRUE) {
	$mysqli->close();
	//echo "Insert Completed";
	header('Location: http://cs494-assignment2.appspot.com/home');
}
else {
	echo $mysqli->error;
}

