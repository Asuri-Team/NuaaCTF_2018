<?php

function traverseDir($filedir) {
    //打开目录
    // $addr = md5("hac425".$_SERVER['REMOTE_ADDR']);
    // $filedir = $addr;
    $dir = @dir($filedir);
    //列出目录中的文件
    while (($file = $dir->read())!==false){
        if(is_dir($filedir."/".$file) AND ($file!=".") AND ($file!="..")){
            //递归遍历子目录
            traverseDir($filedir."/".$file);
        } else {
            if(($file!=".") AND ($file!="..")){
                echo '<div><img src="'.$filedir."/".$file .'" class="pic1"/></div>';
            }
           
        }
    }
    $dir->close();
}

?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="initial-scale=1.0, maximum-scale=1.0, user-scalable=no" /> 
    <title></title>
    <link rel="stylesheet" type="text/css" href="style.css" />
    </head>
<body >

    <div>
        <h1>
        个人照片墙
        </h1>
    </div>
        <?php
            traverseDir("img");
            traverseDir(md5("hac425".$_SERVER['REMOTE_ADDR']));
        ?>
	
</body>
</html>



