<?php
	$type = $_SERVER['REQUEST_METHOD'];

	if($type == "GET") { //If the page was requested via GET
		$queryString = $_SERVER['QUERY_STRING'];
		if(empty($queryString)) {
			$response = array('Type' => $type, 'parameters' => null);
			echo json_encode($response);
		}
		else {
			parse_str($queryString, $output);
			$parameterJson = json_encode($output);
			$response = array('Type' => $type, 'parameters' => $parameterJson);
			echo json_encode($response);
		}
	}
	else { //If the page was requested via POST
		if(empty($_POST)) {
			$response = array('Type' => $type, 'parameters' => null);
			echo json_encode($response);
		}
		else {
			$queryString = json_encode($_POST);
			$response = array('Type' => $type, 'parameters' => $queryString);
			echo json_encode($response);
		}
	}
?>