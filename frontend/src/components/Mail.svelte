<script>
	import * as m from '$lib/paraglide/messages.js';

	let isEmailOpen = $state(false);
</script>

{#if isEmailOpen}
	<div>
		<a href="mailto:contact@h4rl.dev" target="_blank">contact@h4rl.dev</a>
	</div>
{:else}
	<button class="fake-link text-left" onclick={() => (isEmailOpen = !isEmailOpen)}>
		{m.email()}
	</button>
{/if}

<style>
	button {
		@apply w-fit;
	}
	div {
		@apply inline-block;
	}
</style>
