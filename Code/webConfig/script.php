<?php


	$configfile = "config.json";
	
	// Open de json file
	$json_file = file_get_contents($configfile);
	$json = json_decode($json_file,true);


	if(isset($_GET["data"]))
	{
		// Ze vragen om de json data, deze sturen we terug
		send_json($json);
	}

	elseif (isset($_GET["remove"])) 
	{
		// we verwijderen het object uit de array en slagen de changes op
		unset($json["objects"][$_GET["remove"] -1 ]);
		$json["objects"] = array_values($json["objects"]);		// De indexen van de array zijn opgefuckt, dus herindexen we alles
		save_json($json,$configfile);
		send_json($json);
	}

	else
	{
		// Ze willen een nieuw object aanmaken
		$data = json_decode(file_get_contents("php://input"),true);		// Json data ophalen

		if(!(isset($data["Naam"]) && isset($data["Type"]) && isset($data["SendAddr"]) && isset($data["homekit"])))
		{
			// Niet alle data is er
			return "error";
		}

		if($data["Type"] == "0")	return "error";			// Het type is niet ingevuld

		array_push($json["objects"], 
			[
				"Naam" => $data["Naam"],
				"Type" => intval($data["Type"]),		// We maken het nieuwe object
				"SendAddr" => $data["SendAddr"],
				"homekit" => $data["homekit"]
			]);

		send_json($json);
		save_json($json,$configfile);

	}


	//
	//	Stuur de json data terug naar de client
	//
	function send_json($data)
	{
		// We sturen alle json naar de webpagina
		header("Content-Type: application/json");
		echo json_encode($data);
	}

	//
	//	Slaag de json data terug op in de file
	//
	function save_json($data, $filename)
	{
		file_put_contents($filename, json_encode($data,JSON_PRETTY_PRINT));
	}

	