<script>
	let { children } = $props();
</script>

<div class="glass">
	{@render children?.()}
</div>

<style>
	.glass {
		@apply min-h-[170px] rounded-xl border border-solid border-white/10 bg-white bg-opacity-10 px-6 py-4 bg-blend-normal shadow-inner backdrop-blur-sm;
	}
</style>
