@extends("partials.master")

@section("header")

	<style type="text/css">

		.space {

			margin-bottom: 10px;
		}

	</style>

@stop

@section("content")

	@if(Session::has('message'))
		<div class="notification is-primary">
		  {{-- <button class="delete"></button> --}}
		  {{ Session::get("message") }}
		</div>
	@endif

	<h1 class="title">Importeer</h1>
	<div class="notification">
    	
		<form method="POST" action="/upload" enctype="multipart/form-data">

			{{ csrf_field() }}
			
			<div class="field">
			  <label class="label">Groep addressen:</label>
			  <p class="control space">
			    	<input type="file" class="input" name="etsconfig" accept=".xml">
			  </p>
			</div>

			<p class="control">
				<input type="submit" value="Importeer" name="submit" class="button is-primary">
			</p>

		</form>

  	</div>

@stop