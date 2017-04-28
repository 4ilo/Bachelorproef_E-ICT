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

	<h1 class="title">Selecteer de feedback adressen (Niet nodig voor boolean objecten):</h1>
	<h2 class="subtitle"> Selecteer GEEN schakeladressen.</h2>
	<div class="notification">

	<form action="feedback" method="post">
		{{ csrf_field() }}
		
		<ul>
			@foreach($hoofdGroepen as $hoofdGroep)

				<li>
					{{ $hoofdGroep["@attributes"]["Name"] }}
					<ul>
						@foreach($hoofdGroep["GroupRange"] as $subgroep)

							<li class="indent">
								{{ $subgroep["@attributes"]["Name"] }}

								<ul>

									@foreach($subgroep["GroupAddress"] as $subsubgroep)
										@if(isset($subsubgroep["@attributes"]))
											<?php $object = $subsubgroep["@attributes"]; ?>
										@else
											<?php $object = $subsubgroep; ?>
										@endif

										<li class="indent2">
											<div class="field">
											  <p class="control">
											    <label class="checkbox">
											      @if(isset($object["DPTs"]))
											      	<input type="checkbox" name="{{ $object["Name"] }}" value='{{ $object["Address"] }}'>
											      @endif
											      {{ $object["Name"] }}
											    </label>
											  </p>
											</div>
										</li>
									@endforeach
								</ul>
							</li>

						@endforeach
					</ul>
				</li>

			@endforeach
		</ul>

		<input type="submit" value="Verder" class="button is-primary"/>

	</form>

  	</div>

@stop