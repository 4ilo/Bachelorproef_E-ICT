
var app = new Vue({

	el:"#app",
	data: {

		
	},

	methods: {

		send(object, status) {

			axios.get("script.php?object="+ object +"&status="+status).then((response) => {

				console.log(response);
			});
		}

	},



	created: function() {

	}
})