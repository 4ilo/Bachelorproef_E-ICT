<?php

	echo "<pre>";
	var_dump($_FILES);
	echo "</pre>";

	$target_file = "uploads/config.xml";

	if(isset($_POST["submit"]))
	{
		if(isset($_FILES["etsconfig"]))
		{
			if($_FILES["etsconfig"]["type"] != "text/xml")
			{
				echo "Gelieve een xml bestand te uploaden.";
				exit();
			}

			if(move_uploaded_file($_FILES["etsconfig"]["tmp_name"], $target_file) === false)
			{
				echo "Er was een fout bij het uploaden van uw file.";
				exit();
			}
		}
	}