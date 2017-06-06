<?php


class SimKnx {
	
	private $simKnx_host;
	private $simKnx_port;

	/**
	 * Constructor
	 *
	 * @param      string  $host   The SIM_KNX host
	 * @param      string  $port   The SIM_KNX port
	 */
	public function __construct($host = "localhost", $port = 1234)
	{
		$this->simKnx_host = $host;
		$this->simKnx_port = $port;
	}

	/**
	 * Sets a bool object.
	 *
	 * @param      string  $objectNumber  The object number
	 * @param      Bool  $bool          The bool
	 */
	public function setBoolObject($objectNumber, $bool)
	{
		$request = "set " . $objectNumber . " " . $bool;
		$this->setObject($request);
	}

	/**
	 * Sets a dimmer object.
	 *
	 * @param      string	$objectNumber  The object number
	 * @param      Bool    	$direction     The direction
	 * @param      Int 	   	$value         The value
	 */
	public function setDimmerObject($objectNumber, $direction, $value)
	{
		$request = "set " . $objectNumber . " " . $direction . " " . $value;
		$this->setObject($request);
	}

	/**
	 * Sets a integer object.
	 *
	 * @param      string  	$objectNumber  The object number
	 * @param      Int  	$value         The value
	 */
	public function setIntegerObject($objectNumber, $value)
	{
		$request = "set " . $objectNumber . " " . $value;
		$this->setObject($request);
	}

	/**
	 * Send a set request over UDP
	 *
	 * @param      String  $request  The request string preformatted
	 */
	private function setObject($request)
	{
		// Create socket
		$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

		// Send the message
		socket_sendto($socket, $request, strlen($request), 0, $this->simKnx_host ,$this->simKnx_port);

		socket_close($socket);
	}

	/**
	 * Get the type of an object
	 *
	 * @param      int  $objectNumber  The object number
	 *
	 * @return     string  The object type.
	 */
	public function getObjectType($objectNumber)
	{

		$message = "type " . $objectNumber;

		// Create socket and bind it to localhost for a response
		$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
		socket_bind($socket, "localhost");

		// Send the message and ask for the object type
		socket_sendto($socket, $message, strlen($message), 0, $this->simKnx_host ,$this->simKnx_port);

		$addr = "";
		$port = 0;
		$response = "";

		socket_recvfrom($socket, $response, 10, 0, $addr, $port);

		socket_close($socket);

		return $response;

	}

	/**
	 * Get the value for a object
	 *
	 * @param      Int  $objectNumber  The object number
	 *
	 * @return     string  The object.
	 */
	public function getObject($objectNumber)
	{
		$message = "get " . $objectNumber;

		// Create socket and bind it to localhost for a response
		$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
		socket_bind($socket, "localhost");

		// Send the message and ask for the object type
		socket_sendto($socket, $message, strlen($message), 0, $this->simKnx_host ,$this->simKnx_port);

		$addr = "";
		$port = 0;
		$response = "";

		socket_recvfrom($socket, $response, 10, 0, $addr, $port);

		socket_close($socket);

		return $response;
	}
}