<?php

//Initialize all the stuff
$connection = new MongoClient("***");
$dbname = $connection->CS494;
$teams = $dbname->teams;
$collection = $connection->$dbname->teams;

//Check what the request type is
if($_SERVER['REQUEST_METHOD'] === 'GET') {
	if(isset($_GET['id'])) { //if they put a specific id
		$result = $collection->findOne(array('_id' => new MongoId($_GET['id']))); //Query the table
		$result['_id'] = (string) $result['_id']; //Get rid of the weird array
		echo json_encode($result); //Display the result
	}
	else { //if no specific id
		$teamsArray = array();
		$result = $collection->find(); //Grab all teams from the db
		foreach($result as $team) { //build the array (not necessary, but I wanted to put the url at a specific spot)
			$teamArray = array("_id" => (string) $team["_id"], "url" => "http://54.68.100.174/api/teams.php?id=" . (string) $team["_id"],"city" => $team["city"], "name" => $team["name"], "abbrev" => $team["abbrev"], "conference" => $team["conference"], "division" => $team["division"], "wins" => $team["wins"], "losses" => $team["losses"], "players" => $team["players"]);
			array_push($teamsArray, $teamArray);
		}
		echo json_encode($teamsArray); //Display the result
	}
}
elseif($_SERVER['REQUEST_METHOD'] === 'POST') {
	if(isset($_POST['city'])) { //If a city is entered
		if(isset($_POST['name'])) { //If a name is entered
			if(isset($_POST['abbrev'])) { //If an abbreviation is entered
				if(isset($_POST['conference'])) { //If a conference is entered
					if(isset($_POST['division'])) { //If a division is entered (everything necessary is now entered)
						$team = array( //Setup the array
							'city' => $_POST['city'], 
							'name' => $_POST['name'],
							'abbrev' => $_POST['abbrev'], 
							'conference' => $_POST['conference'], 
							'division' => $_POST['city'],
							'wins' => $_POST['wins'],
							'losses' => $_POST['losses'],
							'players' => $_POST['players']
						);
						$teams->insert($team); //Create the team
						$result = $collection->findOne(array('_id' => new MongoId($team['_id']))); //Grab the team id
						$result['_id'] = (string) $result['_id'];
						echo json_encode($result); //Display it to the user
					}
					else { //If division isn't entered
						$arr = array("error" => "Missing param: division");
						echo json_encode($arr);
					}
				}
				else { //If conference isn't entered
					$arr = array("error" => "Missing param: conference");
					echo json_encode($arr);
				}
			}
			else { //If abbreviation isn't entered
				$arr = array("error" => "Missing param: abbrev");
				echo json_encode($arr);
			}
		}
		else { //If name isn't entered
			$arr = array("error" => "Missing param: name");
			echo json_encode($arr);
		}
	}
	else { //If city isn't entered
		$arr = array("error" => "Missing param: city");
		echo json_encode($arr);
	}
}
elseif($_SERVER['REQUEST_METHOD'] === 'PUT') {
	parse_str(file_get_contents('php://input'), $post_vars); //PUT variables are tough to manage in PHP
	$result = $collection->findOne(array('_id' => new MongoId($post_vars['id']))); //Grab the team id
	$players = $result['players']; //Grab the players array
	$alreadyExist = 0;
	foreach($players as $player) {
		if($player === $post_vars['pid']) { //Check if the player is already on the team (in the array)
			$alreadyExist = 1; //In retrospect, I should've only checked on the player side instead since I wanted historic team info. 
			$arr = array("error" => "player " . $post_vars['pid'] . " already on team " . $post_vars['id']);
			echo json_encode($arr);
		}
	}
	if($alreadyExist === 0) { //If they aren't already on the team
		if(empty($players)) { //If the team has no players
			$players = array($post_vars['pid']);
		}
		else { //If the team has players already
			array_push($players, $post_vars['pid']);
		}
		$collection->update( //Update the db
			array('_id' => new MongoId($post_vars['id'])),
			array('$set' => array('players' => $players))
		);
		//Update player's team in their collection
		$playersCollection = $connection->$dbname->players;
		$oldPlayerInfo = $playersCollection->findOne(array('_id' => new MongoId($post_vars['pid'])));
		$playersCollection->update(
			array('_id' => new MongoId($post_vars['pid'])),
			array('$set' => array('team' => $post_vars['id']))
		);

		$result = $collection->findOne(array('_id' => new MongoId($post_vars['id'])));
		$result['_id'] = (string) $result['_id'];
		echo json_encode($result);
	}
}
elseif($_SERVER['REQUEST_METHOD'] === 'DELETE') {
	parse_str(file_get_contents('php://input'), $post_vars); //DELETE variables are difficult to manage in PHP
	$collection->remove( array('_id' => new MongoId($post_vars['id']))); //Remove the document
	$teamsArray = array(); //Display all the teams
	$result = $collection->find();
	foreach($result as $team) {
		$teamArray = array("_id" => (string) $team["_id"], "url" => "http://54.68.100.174/api/teams.php?id=" . (string) $team["_id"],"city" => $team["city"], "name" => $team["name"], "abbrev" => $team["abbrev"], "conference" => $team["conference"], "division" => $team["division"], "wins" => $team["wins"], "losses" => $team["losses"], "players" => $team["players"]);
		array_push($teamsArray, $teamArray);
	}
	echo json_encode($teamsArray);
}
else {
	$arr = array("error" => "invalid request method");
	echo json_encode($arr);
}

?>
