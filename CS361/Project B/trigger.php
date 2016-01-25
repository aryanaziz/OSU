<html>
	<head>
	</head>
	<body>
		<form action="updatetrigger.php" method="post">
			<input type="number" name="trigger" <?php
				$dbhost = '***';
				$dbuser = '***';
				$dbpass = '***';
				$dbname = '***';
				$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

				$result = mysqli_query($con,"SELECT * FROM cs361_triggers WHERE user_id = 1");

				while($row = mysqli_fetch_row($result)) {
					echo "value=\"$row[1]\"";
				}
			?>>
			<input type="submit" value="Update">
		</form>

		<?php 

		$result2 = mysqli_query($con,"SELECT max(date_done) FROM cs361_activity_record WHERE user_id = 1");
		while($row2 = mysqli_fetch_row($result2)) {
			echo $row[0];
		}
		?>
	</body>
</html>