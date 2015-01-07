<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS494 - Assignment 6</title>
	</head>
	<body>
		<form method="post" action="add.php">
			Name: <input type="text" name="name">
			<br>
			Category: <input type="text" name="category">
			<br>
			Price: <input type="text" name="price">
			<br>
			<input type="submit" value="Add Product">
		</form>
		<hr>
		<table>
			<thead>
				<tr>
					<th>Name</th>
					<th>Category</th>
					<th>Price</th>
					<th>Delete</th>
				</tr>
			</thead>
			<tbody>
			<?php
				$dbhost = 'localhost';
				$dbuser = 'afgntcom_osu';
				$dbpass = 'osu123';
				$dbname = 'afgntcom_OSUCS494';
				$con = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
				$result = mysqli_query($con,"SELECT * FROM assignment6");
				$result2 = mysqli_query($con,"SELECT distinct(category) FROM assignment6");
				
				while($row = $result->fetch_assoc()) {
					echo '<tr>';
					echo '<td>' . $row["name"] . '</td>';
					echo '<td>' . $row["category"] . '</td>';
					echo '<td>' . $row["price"] . '</td>';
					echo '<td><form method="post" action="delete.php"><input type="hidden" name="id" value="'.$row['id'].'"><input type="submit" value="Delete Row"></form></td>';
					echo '</tr>';
				}

				mysqli_close($con);
				
			?>
			</tbody>
		</table>
		<hr>
		<form method="post" action="modify.php">
			<select name="category">
			<?php
				while($row = mysqli_fetch_array($result2)) {
					echo '<option value="' . $row['category'] . '">' . $row['category'] . '</option>';
				}
			?>
			</select>
			<br>
			Percent: <input type="number" name="percent">%
			<br>
			<input type="submit" value="Alter prices">
		</form>
		<hr>
		<form method="post" action="deleteAll.php">
			<input type="submit" value="Delete All Products">
		</form>
	</body>
</html>