<?php
/**
 * Created by PhpStorm.
 * User: zedd
 * Date: 2018-12-13
 * Time: 23:16
 */

require "./config.php";

function register($username, $password, $email){
    if ( $username && $password && $email){
        $password = md5($password);
        $stmt = $GLOBALS['dbh']->prepare("INSERT INTO users (username, password, is_admin, email) VALUES (?,?,0,?)");
        $stmt->bind_param('sss',$username,$password,$email);
        $stmt->execute();
        if ($stmt->errno === 1062){
            echo "<script>alert(\"Usr exist!\");window.location=\"./index.php\";</script>";
            return;
        }
        if ($stmt->affected_rows === 1){
            echo "<script>alert(\"Success!\");window.location=\"./index.php\";</script>";
        }
        $stmt->free_result();
        $stmt->close();
    }
    else{
        echo "<script>alert(\"Username or Password or Email cant be NULL！\");window.location=\"./index.php\";</script>";
    }
}

function checkLength($str){
    return strlen($str) > 20 ? True : False;
}

function checkEmail($email){
    $pattern = "/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,})$/";
    return preg_match($pattern, $email, $matches);
}

$username = isset($_POST['username'])? trim($_POST['username']) : NULL;
$email = isset($_POST['email'])? trim($_POST['email']) : NULL;
$password = isset($_POST['password'])? trim($_POST['password']) : NULL;
if(checkLength($username) || checkLength($email) || checkLength($password)){
    echo "<script>alert(\"Usrname or Email or Passwd is too long !\");window.location=\"./index.php\";</script>";
    die();
}
if(checkEmail($email))
    register($username,$password,$email);
else{
    echo "<script>alert(\"Check your Email Address!\");window.location=\"./index.php\";</script>";
}
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Asuri-Team Managment System</title>
</head>
<body>

</body>
