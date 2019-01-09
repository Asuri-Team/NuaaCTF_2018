<?php
require './config.php';
if(!isset($_SESSION['username']) || empty($_SESSION['username'])){
    echo "<script>alert(\"请先登录！\");window.location=\"./index.php\"</script>";
}
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
            <h2>Welcome back,<?php echo $_SESSION['username'];?></h2>
			<label>
				<p>How is it going?</p>
                <img src="imgs/img1.jpg" style="width: 70%;margin-top: 5%">
                <?php
                    if($_SESSION['is_admin'] === 1){
                        echo $flag;
                    }
                ?>
			</label>
		</div>
		<div class="sub-cont">
			<div class="img">
				<div class="img__text m--up">
					<h2>Personal Settings</h2>
				</div>
				<div class="img__text m--in">
					<h2>Index</h2>
				</div>
				<div class="img__btn">
					<span class="m--up">Settins</span>
					<span class="m--in">Index</span>
				</div>
			</div>
			<div class="form sign-up">
				<h2>Rest Passoword</h2>
                <form action="handler.php" method="post">
                    <label>
                        <input type="hidden" name="username" value="<?php echo $_SESSION['username'];?>">
                    </label>
                    <label>
                        <p>The password reset result will be sent to your email address:<?php echo $_SESSION['email'];?></p>
                    </label>
                    <label>
                        <p>If you can't receive the mail, please check the trash can !</p>
                    </label>
                    <button type="submit" class="submit">Confirm Reset</button>
                </form>
                <button id="Logout" type="button" class="submit">Logout</button>
			</div>
		</div>
	</div>
	<script src="js/index.js"></script>
    <script>
        document.getElementById("Logout").onclick = function(){
            window.location="./logout.php";
        };
    </script>
</body>
</html>