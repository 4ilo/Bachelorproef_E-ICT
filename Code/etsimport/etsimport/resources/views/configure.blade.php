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

	<h1 class="title">Welke objecten moeten ingenomen worden in homeKit?</h1>
	<div class="notification">

	<form action="save" method="post">
		{{ csrf_field() }}
			
		<table class="table">
			<tr>
				<th>Naam</th>
				<th>Type</th>
				<th>Homekit naam</th>
				<th>Homekit</th>
				<th>Soort</th>
			</tr>

			@foreach($selected as $keuze => $type)
				<input type="hidden" name="selected[]" value="{{ $keuze }}">
				<tr>
					<td>{{ $keuze }}</td>
					<td>{{ $type }}</td>
					<td>
						<input type="text" name="{{ $keuze }}[homekitname]" value="{{ str_replace("_", " ", $keuze) }}">
					</td>
					<td>
						@if($type == "DPST-1-1" || $type == "DPST-5-1")
							<div class="field">
							  <p class="control">
							    <label class="checkbox">
							      	<input type="checkbox" name="{{ $keuze }}[homekit]" value='true'/>
							    </label>
							  </p>
							</div>
						@endif
					</td>
					<td>
						<div class="field">
						  <p class="control">
						    <span class="select">
						      <select name="{{ $keuze }}[Soort]">
						        <option value="0">Soort</option>
						        @if($type == "DPST-1-1")
						        	<option value="Lamp">Lamp</option>
						        @elseif($type == "DPST-5-1")
						        	<option value="Dimmer">Dimmer</option>
						        	<option value="Rolluik">Rolluik</option>
						        @endif
						      </select>
						    </span>
						  </p>
						</div>
				</tr>
			@endforeach
		</table>

		<input type="submit" value="Verder" class="button is-primary"/>

	</form>

  	</div>

@stop