<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$userId = mysqli_real_escape_string($con, $_GET['userId']);
	$rating = mysqli_real_escape_string($con, $_GET['rating']);
	$imdbID = mysqli_real_escape_string($con, $_GET['imdbID']);
	$date = date( 'Y-m-d', time() );
	$review = mysqli_real_escape_string($con, $_GET['review']);

	if(mysqli_query($con,"INSERT INTO reviews (`userId`, `rating`, `date`, `imdbID`, `review`) VALUES ('$userId','$rating','$date','$imdbID','$review')")) {
		$arr = array('userId' => $userId, 'rating' => $rating, 'date' => $date, 'review' => $review, 'success' => true);
	}

	else {
		$arr = array('userId' => $userId, 'rating' => $rating, 'date' => $date, 'review' => $review, 'success' => false);
	}
	
	echo json_encode($arr);
?>