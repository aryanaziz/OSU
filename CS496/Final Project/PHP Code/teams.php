<?php

$connection = new MongoClient(); 
$dbname = $connection->CS496FinalProject;
$teams = $dbname->nbaTeams;
$collection = $connection->$dbname->nbaTeams;

if(isset($_GET['teamId'])) {
	$teamArray = array('teamId' => intval($_GET['teamId']));
	$result = $collection->findOne($teamArray);
	if(empty($result)) {
		$jsonArray = array('error' => 'No teams with that id found');
		echo json_encode($jsonArray);
	}
	else {
		$result['_id'] = (string) $result['_id'];
		$jsonArray = array();
		$jsonArray += array('teams' => $result);
		echo json_encode($jsonArray); //Display it to the user
	}
}
else if (isset($_GET['username'])) {
	$users = $dbname->users;
	$usersCollection = $connection->$dbname->users;
	$usernameArray = array('username' => $_GET['username']);
	$userResult = $usersCollection->findOne($usernameArray);
	if(empty($userResult)) {
		$jsonArray = array('error' => 'No users found');
		echo json_encode($jsonArray);
	}
	else {
		$userTeams = $userResult['teams'];
		if($_GET['type'] == 1) { //Get all teams for a specific user
			$teamsArray = array();
			foreach($userTeams as $userTeamId) {
				$teamArray = array('teamId' => "$userTeamId");
				$teamResult = $collection->findOne($teamArray);
				$teamResult['_id'] = (string) $teamResult['_id'];
				$teamsArray[] = $teamResult;
			}
			$jsonArray = array();
			$jsonArray += array('teams' => $teamsArray);
			echo json_encode($jsonArray); //Display it to the user
		}
		else { //Get all the teams user doesn't have
			$teamsArray = array();
			$allTeams = array();
			$allTeamsResult = $collection->find();
			foreach($allTeamsResult as $team) {
				foreach($userTeams as $userTeamId) {
					if($team['teamId'] != $userTeamId) {
						$team['_id'] = (string) $team['_id'];
						$teamsArray[] = $team;
					}
				}
			}
			$jsonArray = array();
			$jsonArray += array('teams' => $teamsArray);
			echo json_encode($jsonArray);
		}
	}
}
else if (isset($_GET['lat'])) {
	if(isset($_GET['long'])) {
		$lat = $_GET['lat'];
		$long = $_GET['long'];
		$coordinateArray = array($lat, $long);
		$teamsArray = array();
		$result = $collection->find();
		$distance = 1000;
		$closestTeam = "";
		foreach($result as $team) {
			$team['_id'] = (string) $team['_id'];
			$teamsArray[] = $team;
		}
		foreach($teamsArray as $team) {
			$teamLat = $team['lat'];
			$teamLong = $team['long'];
			if(distance($lat, $long, $teamLat, $teamLong) < $distance) {
				$distance = distance($lat, $long, $teamLat, $teamLong);
				$closestTeam = $team['teamId'];
			}
		}
		$teamArray = array('teamId' => $closestTeam);
		$result = $collection->findOne($teamArray);
		$result['_id'] = (string) $result['_id'];
		$jsonArray = array();
		$jsonArray += array('teams' => $result);
		echo json_encode($jsonArray); //Display it to the user
	}
	else {
		$jsonArray = array('error' => 'Missing long coordinate');
		echo json_encode($jsonArray);
	}
}
else {
	$teamsArray = array();
	$result = $collection->find();
	foreach($result as $team) {
		$team['_id'] = (string) $team['_id'];
		$teamsArray[] = $team;
	}

	$jsonArray = array();
	$jsonArray += array('teams' => $teamsArray);

	echo json_encode($jsonArray);
}

function distance($lat1, $lon1, $lat2, $lon2, $unit) {
  $theta = $lon1 - $lon2;
  $dist = sin(deg2rad($lat1)) * sin(deg2rad($lat2)) +  cos(deg2rad($lat1)) * cos(deg2rad($lat2)) * cos(deg2rad($theta));
  $dist = acos($dist);
  $dist = rad2deg($dist);
  $miles = $dist * 60 * 1.1515;
  $unit = strtoupper($unit);

  if ($unit == "K") {
    return ($miles * 1.609344);
  } else if ($unit == "N") {
      return ($miles * 0.8684);
    } else {
        return $miles;
      }
}

?>