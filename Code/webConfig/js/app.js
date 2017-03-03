
var app = new Vue({

	el:"#app",
	data: {

		objects: {},
		Naam: "",
		Type: "0",
		SendAddr: "",
		RecvAddr: "",
		sendBlocked: true,
		displayConfirm: false,
		deleteNr: 1,
		deleteNaam: "",
	},

	methods: {

		// Convert the Type number to the text version
		type( nummer ) {

			switch(nummer) {

				case 1: return "Bool";
				case 2: return "Dimmer";
				case 3: return "Percentage";
				case 4: return "Scene";
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
				RecvAddr: this.RecvAddr
			})
			.then((response) => {

				// Refresh al the objects
				this.objects = response.data.objects;

				// Empty the fields
				this.Naam = "";
				this.Type = "0";
				this.SendAddr = "";
				this.RecvAddr = "";

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