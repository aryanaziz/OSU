<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_osu';
	$dbpass = 'osu123';
	$dbname = 'afgntcom_OSUCS494';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$imdbID = mysqli_real_escape_string($con, $_GET['imdbID']);

	$result = mysqli_query($con,"SELECT * FROM reviews WHERE imdbID = '$imdbID'");
	$row_cnt = mysqli_num_rows($result);
	while($row = mysqli_fetch_row($result)) {
		$result2 = mysqli_query($con,"SELECT * FROM users WHERE id = $row[1]");
		$row2 = mysqli_fetch_row($result2);
		$arr = array('ratingId' => $row[0], 'userId' => $row[1], 'userName' => $row2[1], 'rating' => $row[3], 'date' => $row[4], 'review' => $row[2], 'imdbId' => $row[5]);
		$jsonData[] = $arr;
	}

	echo json_encode($jsonData);
?>