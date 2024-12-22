<script>
	let { children } = $props();
</script>

<div class="glass">
	{@render children?.()}
</div>

<style>
	.glass {
		@apply inline w-[80%] min-w-[360px] rounded-xl bg-white bg-opacity-10 px-4 py-2 outline outline-2 outline-gray-500 backdrop-blur-sm;
	}
</style>
