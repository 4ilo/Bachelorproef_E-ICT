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
									      	<input type="checkbox" name="{{ $object["Name"] }}" value='{{ $object["DPTs"] }}'>
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