<?php
$url = "localhost";
$usr = "nuaactf";
$paw = "nuaaCTF";
$database = "web1";

//$link = 0;
$GLOBALS['dbh'] = mysqli_connect($url,$usr,$paw,$database) or die("Error " . mysqli_error($link));

$flag = "NUAACTF{1s_Th15_re411y_r4nd0m?}";
session_start();