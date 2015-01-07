<?php
	session_start();
	session_unset($_SESSION["numVisits"]);
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS494 - Assignment 5</title>
	</head>
	<body>
		<form method="post" action="content.php">
			<input type="text" name="username">
			<br>
			<input type="submit" value="Login">
		</form>
	</body>
</html>