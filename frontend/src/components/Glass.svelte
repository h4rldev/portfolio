<script>
	let { children } = $props();
</script>

<div class="glass">
	{@render children?.()}
</div>

<style>
	.glass {
		@apply inline w-[50%] min-w-[360px] rounded-xl bg-white bg-opacity-10 px-4 py-2 outline outline-1 outline-gray-600 backdrop-blur-md;
	}
</style>
