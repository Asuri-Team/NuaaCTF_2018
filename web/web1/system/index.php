<?php
require './config.php';
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Asuri-Team Managment System</title>
	<link rel="stylesheet" href="css/style.css">
</head>

<body>
	<p class="tip">Asuri-Team Managment System</p>
	<div class="cont">
		<div class="form sign-in">
			<form action="login.php" method="post">
				<h2>Welcome to NuaaCTF 2018</h2>
				<label>
					<span>Usernmae</span>
					<input type="text" name="username"/>
				</label>
				<label>
					<span>Password</span>
					<input type="password" name="password"/>
				</label>
				<button type="submit" class="submit">Sign In</button>
			</form>
			
		</div>
		<div class="sub-cont">
			<div class="img">
				<div class="img__text m--up">
					<h2>New here?</h2>
					<p>Sign up and discover great amount of new opportunities!</p>
				</div>
				<div class="img__text m--in">
					<h2>One of us?</h2>
					<p>If you already has an account, just sign in. We've missed you!</p>
				</div>
				<div class="img__btn">
					<span class="m--up">Sign Up</span>
					<span class="m--in">Sign In</span>
				</div>
			</div>
			<div class="form sign-up">
				<h2>Time to feel like home,</h2>
                <form action="register.php" method="post">
                    <label>
                        <span>Username</span>
                        <input type="text" name="username"/>
                    </label>
                    <label>
                        <span>Email</span>
                        <input type="email" name="email"/>
                    </label>
                    <label>
                        <span>Password</span>
                        <input type="password" name="password"/>
                    </label>
                    <button type="submit" class="submit">Sign Up</button>
                </form>
			</div>
		</div>
	</div>
	<script src="js/index.js"></script>
</body>
</html>