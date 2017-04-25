@extends("partials.master")

@section("header")

	<style type="text/css">

		.space {

			margin-bottom: 10px;
		}

		.indent {
			padding-left: 15px;
		}
		.indent2 {
			padding-left: 30px;
		}

	</style>

@stop

@section("content")

	<h1 class="title">Selecteer de te importeren groep adressen:</h1>
	<h2 class="subtitle"> Selecteer enkel stuur adressen, GEEN feedback</h2>
	<div class="notification">

	<form action="import" method="post">
		{{ csrf_field() }}
		
		@include("partials.selectForm")

		<input type="submit" value="Verder" class="button is-primary"/>

	</form>

  	</div>

@stop