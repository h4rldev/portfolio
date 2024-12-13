<script>
	let { content } = $props();
</script>

<div class="victim">
	<div class="inner-shell">
		{@render content()}
	</div>
</div>

<style>
	.victim {
		@apply flex flex-col;
		@apply justify-center align-middle;
	}

	.inner-shell {
		@apply backdrop-blur-xl;
	}
</style>
