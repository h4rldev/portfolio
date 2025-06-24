<script>
	import { browser } from '$app/environment';
	import * as m from '$lib/paraglide/messages.js';
</script>

<div>
	<ul>
		<li>&copy; h4rl {new Date().getFullYear()}.</li>
		<li>
			{m.this_websites_code_is()}
			<a href="https://github.com/h4rldev/portfolio">{m.open_source()}</a>{m.and()}
			{m.licensed_under()}
			<a href="https://github.com/h4rldev/portfolio/blob/main/LICENSE" target="_blank"
				>BSD 3-Clause {m.license()}</a
			>, {m.it_s_contents_is()}
			{m.licensed_under()}
			<a href="https://creativecommons.org/licenses/by/4.0" target="_blank">CC BY 4.0</a>.
		</li>
	</ul>
	<ul class="special-list mt-2">
		<li>{m.feel_free_to_save()}</li>
		<li>
			<img src="/88x31/me.png" class="eight-eight-ecks-thirty-one mx-auto mt-1" alt="me" />
		</li>
	</ul>
</div>

<style>
	div {
		@apply z-10 flex w-[80%] min-w-[330px] flex-col items-center justify-center gap-1 text-center;
	}
	ul {
		@apply inline-flex flex-row flex-wrap justify-center gap-1 text-sm;
	}
	.special-list {
		@apply flex flex-col items-center justify-center gap-1;
	}
</style>
