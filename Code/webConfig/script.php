<?php


	$configfile = "config.json";
	
	// Open de json file
	$json_file = file_get_contents($configfile);
	$json = json_decode($json_file,true);


	if(isset($_GET["data"]))
	{
		send_json($json);
	}
	elseif (isset($_GET["remove"])) 
	{
		unset($json["objects"][$_GET["remove"] -1 ]);
		$json["objects"] = array_values($json["objects"]);
		save_json($json,$configfile);
		send_json($json);
	}
	else
	{
		$data = json_decode(file_get_contents("php://input"),true);

		if(!(isset($data["Naam"]) && isset($data["Type"]) && isset($data["SendAddr"]) && isset($data["RecvAddr"])))
		{
			return "error";
		}

		if($data["Type"] == "0")	return "error";

		array_push($json["objects"], 
			[
				"Naam" => $data["Naam"],
				"Type" => intval($data["Type"]),
				"SendAddr" => $data["SendAddr"],
				"RecvAddr" => $data["RecvAddr"]
			]);

		send_json($json);
		save_json($json,$configfile);

	}


	function send_json($data)
	{
		// We sturen alle json naar de webpagina
		header("Content-Type: application/json");
		echo json_encode($data);
	}

	function save_json($data, $filename)
	{
		file_put_contents($filename, json_encode($data,JSON_PRETTY_PRINT));
	}

	