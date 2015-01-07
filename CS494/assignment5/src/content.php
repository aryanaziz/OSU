<?php
	/*if(strpos($_SERVER['HTTP_REFERER'],'login.php') === false) {
		header('Location: login.php');
	}
	else {*/
		session_start();
		if(!isset($_SESSION["numVisits"])) {
			$_SESSION["numVisits"] = 0;
		}
		if($_SESSION["visited"] == false) {
			$_SESSION["numVisits"] = 0;
		}
		else {
			$_SESSION["numVisits"] = $_SESSION["numVisits"] + 1;
		}
		$_SESSION["visited"] = true;
	/*}*/
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS494 - Assignment 5</title>
	</head>
	<body>
		<?php
			if(empty($_POST[username])) {
				echo "A username must be entered. Click <a href='login.php'>here</a> to return to the login screen.";
			}
			else {
				$username = $_POST[username];
				$visits = $_SESSION["numVisits"];
				echo "Hello $username you have visited this page $visits times before. Click <a href='login.php'>here</a> to logout.";
			}
		?>
	</body>
</html>