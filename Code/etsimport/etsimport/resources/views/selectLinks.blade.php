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

	<h1 class="title">Selecteer de bijhorende feedback en schakel adressen voor rolluiken en dimmers</h1>
	<div class="notification">

	<form action="link" method="post">
		{{ csrf_field() }}
			
		<table class="table">
			<tr>
				<th>Naam</th>
				<th>Type</th>
				<th>Soort</th>
				<th>SchakelObject (bij dimmer)</th>
				<th>Feedback (dimmer en rolluik)</th>
			</tr>

			@foreach($objects as $object)
				{{-- <input type="hidden" name="selected[]" value="{{ $keuze }}"> --}}
				@if($object["Type"] == 3)
					<tr>
						<td>{{ $object["Naam"] }}</td>
						<td>{{ $object["Type"] }}</td>
						<td>{{ $object["Soort"] }}</td>
						<td>
							<div class="field">
								<span class="select">
									<select name="{{ $object["uname"] }}[schakel]">
										<option selected="selected" value="0">Geen Dimmer</option>
										@foreach($objects as $schakelObject)
											@if($schakelObject["Type"] == 1)
												<option value="{{ $schakelObject["uname"] }}">{{ $schakelObject["Naam"] }}</option>
											@endif
										@endforeach
									</select>
								</span>
							</div>
						</td>
						<td>
							<div class="field">
								<span class="select">
									<select name="{{ $object["uname"] }}[feedback]">
										<option selected="selected" value="0">Geen Feedback</option>
										@foreach($objects as $feedbackObject)
											@if($schakelObject["Type"] == 5)
												<option value="{{ $feedbackObject["uname"] }}">{{ $feedbackObject["Naam"] }}</option>
											@endif
										@endforeach
									</select>
								</span>
							</div>
						</td>
					</tr>
				@endif
					
			@endforeach
		</table>

		<input type="submit" value="Verder" class="button is-primary"/>

	</form>

  	</div>

@stop