<?php
	if(empty($_POST[name]) || empty($_POST[price]) || !is_numeric($_POST[price])) {
		if(empty($_POST[name])) {
			echo "Whoops, you left the name field blank. Please go back and enter a name.<br>";
		}
		if(empty($_POST[price])) {
			echo "Whoops, you left the price field blank. Please go back and enter a name.<br>";
		}
		if(!is_numeric($_POST[price])) {
			echo "Whoops, price has to be a number!";
		}	
		echo "Please click <a href='index.php'>HERE</a> to go back to the form.";
	}

	else {
		$dbhost = 'localhost';
		$dbuser = 'afgntcom_osu';
		$dbpass = 'osu123';
		$dbname = 'afgntcom_OSUCS494';


		$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

		if(mysqli_query($con,"INSERT INTO assignment6 (`name`, `category`, `price`) VALUES ('$_POST[name]','$_POST[category]','$_POST[price]')")) {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS494/assignment6/";
			header('Location: ' . $url);
		}
		else {
			if(mysqli_errno($con) == 1062) {
				echo "You have entered a duplicate value for the name field, which must be unique.<br>Please click <a href='index.php'>HERE</a> to go back to the form.";
			}
		}

		mysqli_close($con);
	}
?>