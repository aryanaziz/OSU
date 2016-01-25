<?php

$connection = new MongoClient(); 
$dbname = $connection->CS496FinalProject;
$users = $dbname->users;
$collection = $connection->$dbname->users;

if($_SERVER['REQUEST_METHOD'] === 'GET') { 
	if(isset($_GET['username'])) {
		$username = $_GET['username'];
		if(isset($_GET['password'])) {
			$password = $_GET['password'];
			$user = array(
				'username' => $username,
				'password' => $password
			);

			$result = $collection->findOne($user);
			if(empty($result)) {
				$jsonArray = array('error' => 'Invalid Username or Password');
				echo json_encode($jsonArray);
			}
			else {
				$result['_id'] = (string) $result['_id'];
				echo json_encode($result); //Display it to the user
			}
		}
		else {
			$usernameArray = array('username' => $_GET['username']);
			$result = $collection->findOne($usernameArray);
			if(empty($result)) {
				$jsonArray = array('error' => 'No users found');
				echo json_encode($jsonArray);
			}
			else {
				$result['_id'] = (string) $result['_id'];
				unset($result['password']);
				echo json_encode($result); //Display it to the user
			}
		}
	}
	else {
		$result = $collection->find();
		foreach($result as $user) {
			$user['_id'] = (string) $user['_id'];
			$username = $user['username'];
			$user['link'] = "http://52.11.75.34/users.php?username=$username";
			unset($user['password']);
			//$user += array('url' => "http://52.11.75.34/users.php?username=")
			$usersArray[] = $user;
		}
		$jsonArray = array();
		$jsonArray += array('users' => $usersArray);
		echo json_encode($jsonArray);
	}
	
}
elseif($_SERVER['REQUEST_METHOD'] === 'POST') {
	$username = $_POST['username'];
	$password = $_POST['password'];

	$user = array(
		'username' => $username,
		'password' => $password
	);

	$searchArray = array('username' => $username);
	$result = $collection->findOne($searchArray);
	if(!empty($result)) {
		$jsonArray = array('error' => 'User Already Exists');
		echo json_encode($jsonArray);
	}
	else {
		$users->insert($user); //Create the user
		$result = $collection->findOne(array('_id' => new MongoId($user['_id']))); //Grab the user id
		$result['_id'] = (string) $result['_id'];
		echo json_encode($result); //Display it to the user
	}
}
//PUT for array
/*elseif($_SERVER['REQUEST_METHOD'] === 'PUT') {
	parse_str(file_get_contents('php://input'), $post_vars); //handle the put vars
	$type = $post_vars['type'];
	$teamId = $post_vars['teamId'];
	if(isset($post_vars['username'])) {
		$usernameArray = array('username' => $post_vars['username']);
		if($type == 1) { //Add a team
			$putResult = $collection->findOne($usernameArray);
			if(isset($putResult['teams'])) {
				$collection->update($usernameArray, array('$addToSet' => array("teams" => intval($teamId))));
			}
			else {
				$teamsArray = array(intval($teamId));
				$collection->update(
            		$usernameArray,
            		array('$set' => array('teams' => $teamsArray))
        		);
			}
		}
		else { //Remove a team (type == 2)
			$collection->update($usernameArray, array('$pullAll' => array("teams" => array(intval($teamId)))));
		}
	}
}*/
//PUT for single value
elseif($_SERVER['REQUEST_METHOD'] === 'PUT') {
	parse_str(file_get_contents('php://input'), $post_vars); //handle the put vars
	$teamId = $post_vars['teamId'];
	if(isset($post_vars['username'])) {
		if(isset($post_vars['teamId'])) {
			$usernameArray = array('username' => $post_vars['username']);
			$collection->update($usernameArray, array('$set' => array('nbaTeam' => intval($teamId))));
			$result = $collection->findOne($usernameArray);
			$result['_id'] = (string) $result['_id'];
			unset($result['password']);
			echo json_encode($result); //Display it to the user
			//$jsonArray = array('success' => 'Team Updated');
		}
		else {
			$jsonArray = array('error' => 'No Team Specified');
			echo json_encode($jsonArray);
		}
	}
	else {
		$jsonArray = array('error' => 'No User Specified');
		echo json_encode($jsonArray);
	}
}
elseif($_SERVER['REQUEST_METHOD'] === 'DELETE') {
	parse_str(file_get_contents('php://input'), $post_vars); //handle delete vars
	if(isset($post_vars['username'])) {
		$username = $post_vars['username'];
	}
	else {
		$username = $_GET['username'];
	}
    $collection->remove(array('username' => $username)); //remove the player
	$jsonArray = array('success' => 'User Account Deleted');
	echo json_encode($jsonArray);
}

?>