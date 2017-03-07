<?php

	if(isset($_GET["object"]) && isset($_GET["status"]))
	{
		$object = $_GET["object"];
		$status = $_GET["status"];
		echo "Object: " . $object . " Status: " . $status . "\n";


		$message = "set " . $object . " " . $status;

		// $sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
		// socket_bind($sock, "localhost");
		// socket_sendto($sock, $message, strlen($message), 0, "localhost",1234);

		// $addr = "";
		// $port = 0;

		// echo socket_recvfrom($sock, $data, 7, 0, $addr, $port) . "\n";

		// echo "Data: " . $data . "\n";
		// echo "Addr: " . $addr . "\n";
		// echo "Port: " . $port . "\n";
		
		$type = getObjectType($object);
		$request = "";

		switch ($type) 
		{
			case 'bool':
				$request = "set" . $object . $status;
				break;
			
			default:
				$request = "";
				break;
		}

		setObject($message);
	}

	function setObject($message)
	{
		// Create socket
		$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

		// Send the message
		socket_sendto($socket, $message, strlen($message), 0, "localhost",1234);

		socket_close($socket);
	}

	function getObjectType($object)
	{

		$message = "type " . $object;

		// Create socket and bind it to localhost for a response
		$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
		socket_bind($socket, "localhost");

		// Send the message and ask for the object type
		socket_sendto($socket, $message, strlen($message), 0, "localhost",1234);

		$addr = "";
		$port = 0;
		$response = "";

		socket_recvfrom($socket, $response, 10, 0, $addr, $port);

		socket_close($socket);

		return $response;

	}