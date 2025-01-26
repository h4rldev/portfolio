<script>
	let { children } = $props();
</script>

<div class="glass">
	{@render children?.()}
</div>

<style>
	.glass {
		@apply max-h-[512px] min-h-[144px] rounded-xl bg-white bg-opacity-10 px-6 py-4 outline outline-1 outline-gray-600 backdrop-blur-sm;
	}
</style>
