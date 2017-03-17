
var app = new Vue({

	el:"#app",
	data: {

		
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

				alert(response.data);

			});
		}

	},



	created: function() {

	}
})