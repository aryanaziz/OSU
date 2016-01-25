<?php
	$mysqli = new mysqli(
		null, // host
		'***', // username
		'',     // password
		'***', // database name
		null,
		'***'
	);
?>

<!DOCTYPE html>
<html lang="en">
	<head>
		<title>CS496 - Assignment 2</title>
		<link href="css/bootstrap.min.css" rel="stylesheet">
		<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    	<!--[if lt IE 9]>
      		<script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      		<script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    	<![endif]-->

    	<style>
    		#body {
    			padding-top: 100px;
    		}
    	</style>
    </head>
    <body>
		<nav class="navbar navbar-inverse navbar-fixed-top">
  			<div class="container">
	        	<div class="navbar-header">
	          		<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
			            <span class="sr-only">Toggle navigation</span>
			            <span class="icon-bar"></span>
			            <span class="icon-bar"></span>
			            <span class="icon-bar"></span>
	          		</button>
	          		<a class="navbar-brand" href="#">CS496 - Assignment 2</a>
	        	</div>
		        <div id="navbar" class="collapse navbar-collapse">
		          	<ul class="nav navbar-nav">
			            <li class="active"><a href="#">Home</a></li>
			            <li><a href="/createuser">Create User</a></li>
		          	</ul>
		        </div><!--/.nav-collapse -->
	      	</div>
	    </nav>
	    <div class="container" id="body">
	    	<div class="row">
	    		<div class="col-md-8 col-md-offset-2">
	    			<table class="table table-hover table-bordered">
	    				<thead>
	    					<tr>
	    						<th>User Id</th>
	    						<th>Username</th>
	    						<th>Email</th>
	    						<th>Password</th>
	    						<th>Gender</th>
	    						<th>Allow Emails?</th>
	    						<th>Edit</th>
	    					</tr>
	    				</thead>
	    				<tbody>
	    					<?php
	    						if($result = $mysqli->query("SELECT * FROM users")) {
	    							while($row = $result->fetch_row()) {
	    								echo "<tr><td>$row[0]</td><td>$row[1]</td><td>$row[3]</td><td>$row[2]</td><td>$row[4]</td><td>$row[5]</td><td><a class=\"btn btn-sm btn-info\" href=\"edituser?id=".$row[0]."\">Edit User</a></td></tr>";
	    							}
	    						}
	    					?>
	    				</tbody>
	    			</table>
	    		</div>
	    	</div>
	    </div>
	</body>
</html>