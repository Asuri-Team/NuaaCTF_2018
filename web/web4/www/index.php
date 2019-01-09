<?php
    if ($_GET['action'] != "") {
        @include $_GET['action'];
    } else {
        header("Location: /index.php?action=show.php"); 
        exit;
    }

?>  
