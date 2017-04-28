
var app = new Vue({

	el:"#app",
	data: {

		objects: {},
		Naam: "",
		Type: "0",
		SendAddr: "",
		homekit: 0,
		sendBlocked: true,
		displayConfirm: false,
		deleteNr: 1,
		deleteNaam: "",
	},

	methods: {

		// Convert the Type number to the text version
		type( nummer ) {

			switch(nummer) {

				case 1: return "Bool/Lamp";
				case 2: return "Dimmer relatief";
				case 3: return "Dimmer absoluut";
				case 4: return "Scene";
				case 5: return "Feedback absoluut";
				case 6: return "Rolluik absoluut";
			}
		},

		// Check if all fields are filled
		check(){

			if(this.Naam == "" || this.Type == "0" || this.SendAddr == "") {
				this.sendBlocked = true;
				return;
			}

			this.sendBlocked = false;

		},

		// Save the newly created object
		save() {
			
			axios.post("script.php",{
				Naam: this.Naam,
				Type: this.Type,
				SendAddr: this.SendAddr,
				homekit: this.homekit
			})
			.then((response) => {

				// Refresh al the objects
				this.objects = response.data.objects;

				// Empty the fields
				this.Naam = "";
				this.Type = "0";
				this.SendAddr = "";
				this.homekit = false;

			})
		},

		// Show the confirmation panel to confirm deletion
		remove(nummer) {

			this.displayConfirm = true;
			this.deleteNr = nummer;
			this.deleteNaam = this.objects[nummer-1].Naam;
		},


		// The user confirmed, delete the object
		del() {

			axios.get("script.php?remove=" + this.deleteNr).then((response) => {
			
				this.objects = response.data.objects;
			});

			this.displayConfirm = false;
		},

		// Close the confirmation panel
		close() {

			this.displayConfirm = false;
		}
	},



	created: function() {

		axios.get("script.php?data=1").then((response) => {

			this.objects = response.data.objects;
		});
		
	}
})