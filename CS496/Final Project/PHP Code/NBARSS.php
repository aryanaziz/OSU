<?php

$connection = new MongoClient(); 
$dbname = $connection->CS496FinalProject;
$teams = $dbname->nbaTeams;
$collection = $connection->$dbname->nbaTeams;
$teamId = $_GET['team'];

$teamArray = array('teamId' => intval($teamId));
$result = $collection->findOne($teamArray);
$team = $result['nbaId'];


$feed = new DOMDocument();
$url = "http://www.nba.com/" . $team . "/rss.xml";
$feed->load($url);
$json = array();

$json['title'] = $feed->getElementsByTagName('channel')->item(0)->getElementsByTagName('title')->item(0)->firstChild->nodeValue;
$json['description'] = $feed->getElementsByTagName('channel')->item(0)->getElementsByTagName('description')->item(0)->firstChild->nodeValue;
$json['link'] = $feed->getElementsByTagName('channel')->item(0)->getElementsByTagName('link')->item(0)->firstChild->nodeValue;


$items = $feed->getElementsByTagName('channel')->item(0)->getElementsByTagName('item');

$json['items'] = array();
$i = 0;

foreach($items as $item) {

	$title = $item->getElementsByTagName('title')->item(0)->firstChild->nodeValue;
	$description = $item->getElementsByTagName('description')->item(0)->firstChild->nodeValue;
	$pubDate = $item->getElementsByTagName('pubDate')->item(0)->firstChild->nodeValue;
	$link = $item->getElementsByTagName('link')->item(0)->firstChild->nodeValue;

	$json['items'][] = array("title"=>$title, "description"=>$description, "pubdate"=>$pubDate, "link"=>$link); 
}


echo json_encode($json);

?>