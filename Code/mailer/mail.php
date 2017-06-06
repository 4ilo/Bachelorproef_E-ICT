<?php

require __DIR__ . '/vendor/autoload.php';
require "SimKnx.php";

$config = include("config.php");
$simKnx = new SimKnx;

// We get the status of object x
if($simKnx->getObject($config["activityObject"]) == $config["activityObject"])
{
	echo "sending mail!\n";
	sendMail();
}


function sendMail()
{
	$config = include("config.php");

	// We send the mail thrue google smtp
	// A gmail account is required
	$transport = (new Swift_SmtpTransport("smtp.gmail.com","465", "ssl"))
	    ->setUsername($config["googleLogin"])
	    ->setPassword($config["googlePass"]);

	$mailer = new Swift_Mailer($transport);

	// We send the message
	$message = (new Swift_Message($config["subject"]))
	  ->setFrom(array('KNX.IoT@home.com' => 'KNX IoT'))
	  ->setTo(array($config["sendTo"]))
	  ->setBody($config["body"]);

	$result = $mailer->send($message);
}