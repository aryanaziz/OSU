<?php
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
			            <li class="active"><a href="/home">Home</a></li>
			            <li><a href="#">Create User</a></li>
		          	</ul>
		        </div><!--/.nav-collapse -->
	      	</div>
	    </nav>
	    <div class="container" id="body">
	    	<div class="row">
	    		<div class="col-md-8 col-md-offset-2">
	    			<div class="well">
	    				<form class="form-horizontal" action="submitUser.php" method="POST">
	    					<fieldset>
	    						<legend>Create User</legend>
	    						<div class="form-group">
	    							<label for="inputUsername" class="col-md-4 control-label">Username</label>
	    							<div class="col-md-8">
	    								<input type="text" class="form-control" id="inputUsername" name="username" placeHolder="username" required>
	    							</div>
	    						</div>
	    						<div class="form-group">
	    							<label for="inputPassword" class="col-md-4 control-label">Password</label>
	    							<div class="col-md-8">
	    								<input type="password" class="form-control" id="inputPassword" name="password" placeHolder="password" required>
	    							</div>
	    						</div>
	    						<div class="form-group">
	    							<label for="inputEmail" class="col-md-4 control-label">Email</label>
	    							<div class="col-md-8">
	    								<input type="email" class="form-control" id="inputEmail" name="email" placeHolder="email" required>
	    							</div>
	    						</div>
	    						<div class="form-group">
	    							<label for="inputEmail" class="col-md-4 control-label">Gender</label>
	    							<div class="col-md-8">
	    								<div clas="radio">
	    									<label>
	    										<input type="radio" name="gender" id="inputGender1" value="m" required>
	    										Male
	    									</label>
	    								</div>
	    								<div clas="radio">
	    									<label>
	    										<input type="radio" name="gender" id="inputGender2" value="f">
	    										Female
	    									</label>
	    								</div>
	    							</div>
	    						</div>
	    						<br>
	    						<div class="form-group">
	    							<div class="col-md-8 col-md-offset-4">
	    								<label>
	    									<input type="checkbox" value="y" name="checkbox">
	    									Allow emails?
	    								</label>
	    							</div>
	    						</div>
	    						<div class="form-group">
	    							<div class="col-md-8 col-md-offset-4">
	    								<button type="submit" class="btn btn-primary">Submit</button>
	    							</div>
	    						</div>
	    					</fieldset>
	    				</form>
	    			</div>
	    		</div>
	    	</div>
	    </div>
	</body>
</html>