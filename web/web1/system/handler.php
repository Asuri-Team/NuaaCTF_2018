<?php
/**
 * Created by PhpStorm.
 * User: zedd
 * Date: 2018-12-13
 * Time: 23:05
 */
require "./config.php";
require "./email.php";

function generatePasswd(){
    mt_srand((double) microtime() * 1000000);
    var_dump(mt_rand());
    return substr(md5(mt_rand()),0,6);
}

function changePasswd($username, $password){
    $password = md5($password);
    $stmt = $GLOBALS['dbh']->prepare("UPDATE users SET password = ? WHERE username = ?");
    $stmt->bind_param('ss', $password, $username);
    $stmt->execute();
    if ($stmt->affected_rows === 1){
        echo "<script>alert(\"Success!\");history.back(-1);</script>";
        return;
    }
    else
        echo "<script>alert(\"Error!\");history.back(-1);</script>";
    $stmt->free_result();
    $stmt->close();
}


function getEmail($username){
    if ($username){
        $stmt = $GLOBALS['dbh']->prepare("SELECT email From users where username = ?");
        $stmt->bind_param('s', $username);
        $stmt->bind_result($email);
        $stmt->execute();
        if($stmt->fetch()){
            return $email;
        }
        else
            return "error!";
        $stmt->free_result();
        $stmt->close();
    }
    else{
        return "error!";
    }
}

$username = isset($_POST['username']) ? trim($_POST['username']) : NULL;
$email = getEmail($username);
if ($email == "error!"){
    echo "Error!";
    die();
}
$passwd = generatePasswd();
if(sendMail($email,$passwd)){
    changePasswd($username,$passwd);
}
else{
    echo "<script>alert(\"Error! Check your Email address plz!\");history.back(-1);</script>";
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
