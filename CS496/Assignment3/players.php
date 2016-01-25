<?php

//Initialize all the stuff
$connection = new MongoClient("***");
$dbname = $connection->CS494;
$players = $dbname->players;
$collection = $connection->$dbname->players;

//Check what the request type is
if($_SERVER['REQUEST_METHOD'] === 'GET') {
    if(isset($_GET['id'])) { //if they put a specific id
        $result = $collection->findOne(array('_id' => new MongoId($_GET['id'])));
        $result['_id'] = (string) $result['_id'];
        echo json_encode($result);
    }
    else { //If they didn't put a specific id
        $playersArray = array();
        $result = $collection->find();
        foreach($result as $player) {
            $playerArray = array("_id" => (string) $player["_id"], "url" => "http://54.68.100.174/api/players.php?id=" . (string) $player["_id"], "first" => $player["first"], "last" => $player["last"], "team" => $player["team"], "country" => $player["country"], "positions" => $player["positions"]);
            array_push($playersArray, $playerArray);
        }
        echo json_encode($playersArray);
    }
}
elseif($_SERVER['REQUEST_METHOD'] === 'POST') {
    if(isset($_POST['first'])) { //If a first name is entered
        if(isset($_POST['last'])) { //If a last name is entered
            if(isset($_POST['country'])) { //If a country is entered
                if(isset($_POST['positions'])) { //If positions are entered
                    $player = array( //setup the array
                            'first' => $_POST['first'], 
                            'last' => $_POST['last'],
                            'country' => $_POST['country'],
                            'team' => $_POST['team'], 
                            'positions' => $_POST['positions'], 
                        );
                        $players->insert($player);
                        $result = $collection->findOne(array('_id' => new MongoId($player['_id'])));
                        $result['_id'] = (string) $result['_id'];
                        echo json_encode($result);
                }
                else { //If positions isn't entered
                    $arr = array("error" => "Missing param: positions");
                    echo json_encode($arr);
                }
            }
            else { //If country isn't entered
                $arr = array("error" => "Missing param: country");
                echo json_encode($arr);
            }
        }
        else { //If last name isn't entered
            $arr = array("error" => "Missing param: last");
            echo json_encode($arr);
        }
    }
    else { //If first name isn't entered
        $arr = array("error" => "Missing param: first");
        echo json_encode($arr);
    }
}
elseif($_SERVER['REQUEST_METHOD'] === 'PUT') { //Code here is pretty much identical to the team side, just modified collection naming/pointing
    parse_str(file_get_contents('php://input'), $post_vars); //handle the put vars
    $teamCollection = $connection->$dbname->teams;
    $result = $teamCollection->findOne(array('_id' => new MongoId($post_vars['id'])));
    $players = $result['players'];
    $alreadyExist = 0;
    foreach($players as $player) {
        if($player === $post_vars['pid']) { //Check if player is on the team's player array
            $alreadyExist = 1;
            $arr = array("error" => "player " . $post_vars['pid'] . " already on team " . $post_vars['id']);
            echo json_encode($arr);
        }
    }
    if($alreadyExist === 0) { //if not
        if(empty($players)) { //if team currently has no players
            $players = array($post_vars['pid']);
        }
        else { //if team has players
            array_push($players, $post_vars['pid']);
        }
        $teamCollection->update(
            array('_id' => new MongoId($post_vars['id'])),
            array('$set' => array('players' => $players))
        );
        //Update player's team
        $collection = $connection->$dbname->players;
        $oldPlayerInfo = $collection->findOne(array('_id' => new MongoId($post_vars['pid'])));
        $collection->update(
            array('_id' => new MongoId($post_vars['pid'])),
            array('$set' => array('team' => $post_vars['id']))
        );
        $result = $collection->findOne(array('_id' => new MongoId($post_vars['pid'])));
        $result['_id'] = (string) $result['_id'];
        echo json_encode($result);
    }
}
elseif($_SERVER['REQUEST_METHOD'] === 'DELETE') {
    parse_str(file_get_contents('php://input'), $post_vars); //handle delete vars
    $collection->remove( array('_id' => new MongoId($post_vars['id']))); //remove the player
    $playersArray = array();
    $result = $collection->find();
    foreach($result as $player) {
        $playerArray = array("_id" => (string) $player["_id"], "url" => "http://54.68.100.174/api/players.php?id=" . (string) $player["_id"], "first" => $player["first"], "last" => $player["last"], "country" => $player["country"], "positions" => $player["positions"]);
        array_push($playersArray, $playerArray);
    }
    echo json_encode($playersArray);
}
else {
    $arr = array("error" => "invalid request method");
    echo json_encode($arr);
}




?>
