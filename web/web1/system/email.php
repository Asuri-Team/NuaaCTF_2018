<?php
/**
 * Created by PhpStorm.
 * User: zedd
 * Date: 2018-12-14
 * Time: 01:17
 */

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require 'PHPMailer/Exception.php';
require 'PHPMailer/PHPMailer.php';
require 'PHPMailer/SMTP.php';

/**
 *发送邮件方法
 *@param $to：接收者 $title：标题 $content：邮件内容
 *@return bool true:发送成功 false:发送失败
 */

function sendMail($to,$pass){

    //实例化PHPMailer核心类
    $mail = new PHPMailer();

    //使用smtp鉴权方式发送邮件
    $mail->isSMTP();

    //smtp需要鉴权 这个必须是true
    $mail->SMTPAuth=true;

    //链接qq域名邮箱的服务器地址
    $mail->Host = 'smtp.163.com';

    //设置使用ssl加密方式登录鉴权
    $mail->SMTPSecure = 'ssl';

    //设置ssl连接smtp服务器的远程服务器端口号，以前的默认是25，但是现在新的好像已经不可用了 可选465或587
    $mail->Port = 465;

    //设置发件人的主机域 可有可无 默认为localhost 内容任意，建议使用你的域名
    $mail->Hostname = 'www.asuri.org';

    //设置发送的邮件的编码 可选GB2312 我喜欢utf-8 据说utf8在某些客户端收信下会乱码
    $mail->CharSet = 'UTF-8';

    //设置发件人姓名（昵称） 任意内容，显示在收件人邮件的发件人邮箱地址前的发件人姓名
    $mail->FromName = 'admin';

    //smtp登录的账号 这里填入字符串格式的qq号即可
    $mail->Username ='';

    //smtp登录的密码 使用生成的授权码（就刚才保存的最新的授权码）
    $mail->Password = '';

    //设置发件人邮箱地址 这里填入上述提到的“发件人邮箱”
    $mail->From = '';

    //邮件正文是否为html编码 注意此处是一个方法 不再是属性 true或false
    $mail->isHTML(true);

    //设置收件人邮箱地址 该方法有两个参数 第一个参数为收件人邮箱地址 第二参数为给该地址设置的昵称 不同的邮箱系统会自动进行处理变动 这里第二个参数的意义不大
    $mail->addAddress($to,'尊敬的客户');

    //添加该邮件的主题
    $mail->Subject = "密码重置结果";

    //添加邮件正文 上方将isHTML设置成了true，则可以是完整的html字符串
    $mail->Body = "您的密码重置结果为：".$pass. "。 若非您本人操作请无视该封邮件。Have Fun In NuaaCTF_2018.";

    $status = $mail->send();

    //判断与提示信息
    if($status) {
        return true;
    }else{
        return false;
    }
}