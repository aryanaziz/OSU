<?php
	$dbhost = 'localhost';
	$dbuser = 'afgntcom_OSU275';
	$dbpass = 'osu275';
	$dbname = 'afgntcom_OSUCS275';
	$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

	$type = $_GET['type'];

	if($type == 'player') {
		$firstName = $_GET['firstName'];
		$lastName = $_GET['lastName'];
		$height = $_GET['height'];
		$weight = $_GET['weight'];
		$number = $_GET['number'];
		$espn = $_GET['espn'];
		$dob = $_GET['dob'];
		$teamId = $_GET['team'];
		$country = $_GET['country'];

		if(mysqli_query($con,"INSERT INTO players (`playerFirstName`, `playerLastName`, `playerNumber`, `playerHeight`, `playerWeight`, `playerDOB`, `playerESPNId`, `countryId`, `teamId`) VALUES ('$firstName', '$lastName', $number, $height, $weight, '$dob', $espn, $country, $teamId)")) {
			$playerId = mysqli_insert_id($con);
			foreach($_GET['positions'] as $selectedOption) {
				mysqli_query($con,"INSERT INTO player_positions (`playerId`, `positionId`) VALUES ($playerId, $selectedOption)");
			}

			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/player.php?id=" . $playerId;
			header('Location: ' . $url);
		}

		else {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createPlayer.php?error=1";
			header('Location: ' . $url);
		}
	}

	elseif($type == 'team') {
		$teamCity = $_GET['teamCity'];
		$teamName = $_GET['teamName'];
		$division = $_GET['division'];
		$coach = $_GET['coach'];

		if(empty($coach)) {
			if(mysqli_query($con,"INSERT INTO teams (`teamCity`, `teamName`, `divisionId`) VALUES ('$teamCity', '$teamName', $division)")) {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/team.php?id=" . mysqli_insert_id($con);
				header('Location: ' . $url);
			}

			else {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createTeam.php?error=1";
				header('Location: ' . $url);
			}
		}
		else {
			if(mysqli_query($con,"INSERT INTO teams (`teamCity`, `teamName`, `divisionId`) VALUES ('$teamCity', '$teamName', $division)")) {
				$teamId = mysqli_insert_id($con);
				if(mysqli_query($con,"UPDATE coaches SET teamId = $teamId WHERE coachId = $coach")) {
					$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/team.php?id=" . $teamId;
					header('Location: ' . $url);
				}
			}

			else {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createTeam.php?error=1";
				header('Location: ' . $url);
			}
		}

		
	}

	elseif($type === 'conference') {
		$conferenceName = $_GET['name'];

		if(mysqli_query($con,"INSERT INTO conferences (`conferenceName`) VALUES ('$conferenceName')")) {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/teams.php";
			header('Location: ' . $url);
		}

		else {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createConference.php?error=1";
			header('Location: ' . $url);
		}
	}

	elseif($type === 'division') {
		$divisionName = $_GET['name'];
		$conference = $_GET['conference'];

		if(mysqli_query($con,"INSERT INTO divisions (`divisionName`, `conferenceId`) VALUES ('$divisionName',$conference)")) {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/teams.php";
			header('Location: ' . $url);
		}

		else {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createDivision.php?error=1";
			header('Location: ' . $url);
		}
	}

	elseif($type === 'coach') {
		$coachFirstName = $_GET['firstName'];
		$coachLastName = $_GET['lastName'];
		$teamId = $_GET['team'];

		if(empty($teamId)) {
			if(mysqli_query($con,"INSERT INTO coaches (`coachFirstName`, `coachLastName`, `teamId`) VALUES ('$coachFirstName', '$coachLastName', NULL)")) {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/coach.php?id=" . mysqli_insert_id($con);
				header('Location: ' . $url);
			}

			else {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createCoach.php?error=1";
				header('Location: ' . $url);
			}
		}

		else {
			if(mysqli_query($con,"INSERT INTO coaches (`coachFirstName`, `coachLastName`, `teamId`) VALUES ('$coachFirstName', '$coachLastName', $teamId)")) {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/coach.php?id=" . mysqli_insert_id($con);
				header('Location: ' . $url);
			}

			else {
				$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createCoach.php?error=1";
				header('Location: ' . $url);
			}
		}
	}

	elseif($type === 'country') {
		$countryName = $_GET['name'];
		if(mysqli_query($con,"INSERT INTO countries (`countryName`) VALUES ('$countryName')")) {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/country.php?id=" . mysqli_insert_id($con);
			header('Location: ' . $url);
		}

		else {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createCountry.php?error=1";
			header('Location: ' . $url);
		}
	}

	else {
		$positionName = $_GET['name'];
		$positionAbbrev = $_GET['abbrev'];
		if(mysqli_query($con,"INSERT INTO positions (`positionName`, `positionAbbrev`) VALUES ('$positionName', '$positionAbbrev')")) {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/position.php?id=" . mysqli_insert_id($con);
			header('Location: ' . $url);
		}

		else {
			$url = "http://aryanaziz.com/OSU/2014/Fall/CS275/final/createPosition.php?error=1";
			header('Location: ' . $url);
		}
	}
?>