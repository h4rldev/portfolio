<script lang="ts">
	let { children } = $props();
</script>

<div class="container">
	{@render children?.()}
</div>

<style>
	.container {
		@apply mx-auto my-auto w-[70%] min-w-[330px] xs:w-[100%] xs:min-w-[360px] sm:w-[90%] sm:min-w-[360px] md:flex md:h-full md:flex-col md:items-center md:justify-center;
	}
</style>
