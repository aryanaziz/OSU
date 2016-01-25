<?php
	$mysqli = new mysqli(
  		null, // host
  		'***', // username
		'',     // password
		'***', // database name
  		null,
  		'***'
  	);

  	if($mysqli->connect_error) {
  		die('Connect Error, '. $mysqli->connect_errno . ': ' . $mysqli->connect_error);
  		echo "Error connecting";
  	}
  	else {
  		echo "Woah, you're connected!" . mysqli_get_host_info($mysqli) . "<br>";
  	}

  	if ($mysqli->query("CREATE TABLE IF NOT EXISTS users (userId SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, username VARCHAR(20) NOT NULL, password VARCHAR(20) NOT NULL, email VARCHAR(30) NOT NULL, gender VARCHAR(1) NOT NULL, checkbox VARCHAR(1) NOT NULL, PRIMARY KEY (userId), UNIQUE (username)) ENGINE=InnoDB DEFAULT CHARSET=utf8") === TRUE) {
    	printf("Table 'users' successfully created.\n");
	}

	if($result = $mysqli->query("SELECT * FROM users")) {
		echo "Select returned " . $result->num_rows . " rows.";
	}

  	$mysqli->close();
