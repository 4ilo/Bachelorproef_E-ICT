<?php

	if(isset($_GET["object"]) && isset($_GET["status"]))
	{
		$object = $_GET["object"];
		$status = $_GET["status"];
		echo "Object: " . $object . " Status: " . $status . "\n";

		if(isset($_GET["count"]))
		{
			setObject($object,2,$status,$_GET["count"]);
		}
		else if(isset($_GET["nummer"]))
		{
			echo "ok";
			setObject($object,4, $_GET["nummer"]);
		}
		else
		{
			setObject($object,1,$status);
		}

		
		//$type = getObjectType($object);
		//$request = "";

		//echo $type . "\n";
		//setObject($object,$type,$status);
	}

	if(isset($_GET["get"]) && isset($_GET["object"]))
	{
		// We want to get a value
		$object = $_GET["object"];

		echo "Get object: " . $object . "\n";

		echo getObject($object);
	}

/**
 * Set data to an object
 *
 * @param      int  $object  The object number
 * @param      string  $type    The type received from getObjectType()
 * @param      string  $data1   The data for 1 data objects
 * @param      string  $data2   The data for dimming objects
 */
function setObject($object, $type, $data1, $data2="")
{
	$request = "";

	// Depending on the type we send a different message
	switch ($type) 
	{
		case '1':		// 1 is bool
			$request = "set " . $object ." ". $data1;
			break;

		case '2':		// 2 is dimmer
			$request = "set " . $object . " " . $data1 . " " . $data2;
			break;

		case '3':		// 3 is percentage
			$request = "set " . $object ." ". $data1;
			break;

		case '4':		// 4 is scene
			$request = "set " . $object ." ". $data1;
			break;
		
		default:
			$request = "";
			break;
	}

	// Create socket
	$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

	// Send the message
	socket_sendto($socket, $request, strlen($request), 0, "localhost",1234);

	socket_close($socket);
}

/**
 * Get the type of an object
 *
 * @param      int  $object  The object number
 *
 * @return     string  The object type.
 */
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

function getObject($object)
{
	$message = "get " . $object;

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