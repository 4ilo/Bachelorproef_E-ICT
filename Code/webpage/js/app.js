
var app = new Vue({

	el:"#app",
	data: {

		
	},

	methods: {

		send(object, status) {

			axios.get("script.php?object="+ object +"&status="+status).then((response) => {

				console.log(response);
			});
		},	

		dim(object, status, count) {

			axios.get("script.php?object="+ object + "&status="+status + "&count=" + count).then((response) => {

				console.log(response);
			});
		}

	},



	created: function() {

	}
})