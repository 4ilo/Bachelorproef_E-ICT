
var app = new Vue({

	el:"#app",
	data: {

		objects: {},
		Naam: "",
		Type: "0",
		SendAddr: "",
		RecvAddr: "",
		sendBlocked: true,
	},

	methods: {

		type( nummer ) {

			switch(nummer) {

				case 1: return "Bool";
				case 2: return "Dimmer";
				case 3: return "Percentage";
				case 4: return "Scene";
			}
		},

		check(){

			if(this.Naam == "" || this.Type == "0" || this.SendAddr == "") {
				this.sendBlocked = true;
				return;
			}

			this.sendBlocked = false;

		},

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

		remove(nummer) {

			axios.get("script.php?remove=" + nummer).then((response) => {
				
				this.objects = response.data.objects;
			});
		}
	},

	created: function() {

		axios.get("script.php?data=1").then((response) => {

			this.objects = response.data.objects;
		});
		
	}
})