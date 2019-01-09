<?php
/**
 * Created by PhpStorm.
 * User: zedd
 * Date: 2018-12-14
 * Time: 02:55
 */
require './config.php';
session_destroy();
header('location:./index.php');
?>