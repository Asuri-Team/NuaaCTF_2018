<?php
require "./config.php";

function login($username, $password){
    if ( $username && $password){
        $stmt = $GLOBALS['dbh']->prepare("select * from users where username = ? and password = ?");
        $stmt->bind_param('ss',$username,$password);
        $stmt->bind_result($user,$passwd,$id,$is_admin,$email);
        $stmt->execute();
        if($stmt->fetch()){
            $_SESSION['username'] = $user;
            $_SESSION['is_admin'] = $is_admin;
            $_SESSION['email'] = $email;
            $url = "location:./info.php";
            header($url);
        }
        else
            echo "<script>alert(\"Username or Password is wrong!\");window.location=\"./index.php\";</script>";
        $stmt->free_result();
        $stmt->close();
    }
    else{
        echo "<script>alert(\"Username or Password cant be NULL!\");window.location=\"./index.php\";</script>";
    }


}

$username = isset($_POST['username'])? trim($_POST['username']) : NULL;
$password = isset($_POST['password'])? md5(trim($_POST['password'])) : NULL;
login($username,$password);
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Asuri-Team Managment System</title>
</head>
<body>

</body>
