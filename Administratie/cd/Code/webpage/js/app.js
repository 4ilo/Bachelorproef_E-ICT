
var app = new Vue({

	el:"#app",
	data: {

		"status": { "Living": 0, "Keuken": 0},
		
	},

	methods: {

		send(object, status) {

			axios.get("script.php?object="+ object +"&status="+status).then((response) => {

			});
		},	

		dim(object, status, count) {

			axios.get("script.php?object="+ object + "&status="+status + "&count=" + count).then((response) => {

			});
		},

		scene(object, nummer) {

			axios.get("script.php?object="+ object + "&status="+ nummer).then((response) => {

			});
		},

		get(object) {

			axios.get("script.php?get=1&object="+ object).then((response) => {

				console.log(response);
				this.status.Living = response.data;
			});

		},

		getStatuses() {

			axios.get("script.php?get=1&object="+ 1).then((response) => {

				this.status.Living = response.data;
			});


			axios.get("script.php?get=1&object="+ 2).then((response) => {

				this.status.Keuken = response.data;
			});
		},

	},



	created: function() {

		//setInterval(this.getStatuses, 5000);

	}
})