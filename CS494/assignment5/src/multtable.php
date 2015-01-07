<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>CS494 - Assignment 5</title>
	</head>
	<body>
		<?php
		$minMultiplicand = $_GET['min-multiplicand'];
		$maxMultiplicand = $_GET['max-multiplicand'];
		$minMultiplier = $_GET['min-multiplier'];
		$maxMultiplier = $_GET['max-multiplier'];

		//Make sure all of the values are passed
		if(empty($minMultiplicand) || empty($maxMultiplicand) || empty($minMultiplier) || empty($maxMultiplier)) { //If one of the values are empty
			if(empty($minMultiplicand)) { //If the min multiplicand is missing
				echo "Missing parameter min-multiplicand.<br>";
			}
			if(empty($maxMultiplicand)) { //If the max multiplicand is missing
				echo "Missing parameter max-multiplicand.<br>";
			}
			if(empty($minMultiplier)) { //If the min multiplier is missing
				echo "Missing parameter min-multiplier.<br>";
			}
			if(empty($maxMultiplier)) { //If the max multiplier is missing
				echo "Missing parameter max-multiplier.<br>";
			}
		}

		else { //If none of the values are empty
			//Make sure all of the values are numbers
			if(!ctype_digit($minMultiplicand) || !ctype_digit($maxMultiplicand) || !ctype_digit($minMultiplier) || !ctype_digit($maxMultiplier)) { //If one of the values is not an integer
				if(!ctype_digit($minMultiplicand)) { //If the min multiplicand is not an integer
					echo "min-multiplicand must be an integer.<br>";
				}
				if(!ctype_digit($maxMultiplicand)) { //If the max multiplicand is not an integer
					echo "max-multiplicand must be an integer.<br>";
				}
				if(!ctype_digit($minMultiplier)) { //If the min multiplier is not an integer
					echo "min-multiplier must be an integer.<br>";
				}
				if(!ctype_digit($maxMultiplier)) { //If the max multiplier is not an integer
					echo "max-multipler must be an integer.<br>";
				}
			}

			else { //If none of the values are empty AND all of the values are integers
				if($minMultiplicand > $maxMultiplicand || $minMultiplier > $maxMultiplier) { //If one of the min values is greater than the max
					if($minMultiplicand > $maxMultiplicand) { //If the min multiplicand is greater
						echo "Minimum multiplicand larger than maximum.<br>";
					}
					if($minMultiplier > $maxMultiplier) { //If the min multipler is greater
						echo "Minimum multiplier larger than maximum.<br>";
					}
				}
				else { //If everything passes.
					echo "<table><tbody><tr><td></td>";
					for($i = $minMultiplier; $i <= $maxMultiplier; $i++) {
						echo "<td>$i</td>";
					}
					echo "</tr>";
					for($row = $minMultiplicand; $row <= $maxMultiplicand; $row++) {
						echo "<tr><td>$row</td>";
						for($column = $minMultiplier; $column <= $maxMultiplier; $column++) {
							echo "<td>" . $column * $row . "</td>";
						}
						echo "</tr>";
					}
					echo "</tbody></table>";
				}
			}
		}
		?>
	</body>
</html>