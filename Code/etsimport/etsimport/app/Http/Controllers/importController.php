<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Session;

class ImportController extends Controller
{

    /**
     * Show the index view to upload the file
     *
     * @return     view  The home view
     */
    public function index()
    {
        return view("home");
    }

    /**
     * Save the file the user tries to upload
     *
     * @param      \Illuminate\Http\Request  $request  The request
     */
    public function upload(Request $request)
    {
        $this->validate($request, [
            "etsconfig" => "required|file"
        ]);

        $file = $request->file("etsconfig");
        $file->move( storage_path("app"), "config.xml");

        return redirect("/import");
    }

    /**
     * Show al the adresses to the user, so he can select wat he needs
     *
     * @return     view
     */
    public function showAdressen()
    {
        $configfile = storage_path("app") . "/config.xml";

        if(!file_exists($configfile))
        {
            return redirect("/");
        }

        $hoofdGroepen = $this->getHoofdGroepen();

         // dd($hoofdGroepen);

        return view("select",compact("hoofdGroepen"));
    }

    public function saveAddr(Request $request)
    {
        $selected = $request->except(["_token"]);
        $subsubgroepen = $this->getSubSubGroepen();

        return view("configure",compact("selected","subsubgroepen"));
    }

    public function generateJsonconfig(Request $request)
    {
        //dd($request->all());
        $selected = $request->selected;
        $subsubgroepen = $this->getsubsubgroepen();

        $objects = ["objects" => []];

        foreach ($selected as $object) 
        {   
            $naam = str_replace("_"," ", $object);
            $homekitNaam = $request[$object]["homekitname"];
            // Zoek het object in de oorspronkelijke config
            $objectNummer = array_search($naam, array_column($subsubgroepen, "Name")); 
            $dpt = $subsubgroepen[$objectNummer]["Type"];

            $SendAddr = $subsubgroepen[$objectNummer]["Address"];

            $homekit = false;
            if(isset($request[$object]["homekit"])) $homekit = true;

            $soort = $request[$object]["Soort"];
            
            switch ($dpt) 
            {
                case 'DPST-1-1':        // Boolean
                    $type = 1;
                    break;

                case 'DPST-1-8':        // Rolluik step
                    $type = 1;
                    break;

                case 'DPST-1-7':        // Rolluik stop
                    $type = 1;
                    break;

                case 'DPST-3-7':        // Dimmer relatief
                    $type = 2;
                    break;
                
                case 'DPST-5-1':        // Dimmer absoluut
                    $type = 3;
                    break;

                default:
                    $type = 1;
                    break;
            }

            $uname = strtolower(str_replace(" ", "", $naam));       // We maken een unieke naam in formaat naam_type_sendaddr
            $uname .= "_" . $type;
            $uname .= "_" . str_replace("/", "", $SendAddr);

            array_push($objects["objects"], 
                [
                    "Naam" => $naam,
                    "Type" => $type,        // We maken het nieuwe object
                    "SendAddr" => $SendAddr,
                    "homekit" => $homekit,
                    "homekitNaam" => $homekitNaam,
                    "uname" => $uname,
                    "Soort" => $soort
                ]);
        }

        $this->save_json($objects, "config.json");

        Session::flash('message', 'De configuratie is succesvol opgeslagen in config.json');
        return redirect("/");

    }

    //
    //  Slaag de json data terug op in de file
    //
    function save_json($data, $filename)
    {
        file_put_contents($filename, json_encode($data,JSON_PRETTY_PRINT));
    }

    /**
     * Get al groep adresses
     *
     * @return     Array  The hoofd groepen.
     */
    public function getHoofdGroepen()
    {
        $configfile = storage_path("app") . "/config.xml";

        $xml = simplexml_load_file($configfile);
        $tmp_json = json_encode($xml);
        $configdata = json_decode($tmp_json,TRUE);

        $hoofdGroepen = $configdata["GroupRange"];

        return $hoofdGroepen;
    }

    public function getSubSubGroepen()
    {
        $hoofdGroepen = $this->getHoofdGroepen();
        $subsubgroepen = [];

        foreach ($hoofdGroepen as $hoofdgroep) 
        {
            foreach ($hoofdgroep["GroupRange"] as $subgroep) 
            {
                foreach ($subgroep["GroupAddress"] as $subsubgroep) 
                {
                    if(isset($subsubgroep["@attributes"]))
                    {
                        $groep = $subsubgroep["@attributes"];
                    }
                    else
                    {
                        $groep = $subsubgroep;
                    }


                    $nummer = array_push($subsubgroepen, [
                        "Name" => $groep["Name"],
                        "Address" => $groep["Address"],
                        "Type" => "",
                    ]);

                    if(isset($groep["DPTs"]))
                    {   
                        $subsubgroepen[$nummer-1]["Type"] = $groep["DPTs"];
                    }
                }
            }
        }

        return $subsubgroepen;
    }
}
