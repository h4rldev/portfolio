<script lang="ts">
	let { list_items, link = true } = $props();

	const items = list_items.length;
	const time = items * 3;
</script>

<div class="marquee-container">
	<ul class="marquee" style="animation-duration: {time}s;">
		{#each list_items as item}
			<li>
				{#if link}
					<a href={item.href} target="_blank" class="inline-block">
						<img
							class="eight-eight-ecks-thirty-one eight-eight-ecks-thirty-one-link"
							src={item.image}
							alt={item.alt}
						/>
					</a>
				{:else}
					<div>
						<img class="eighty-eight-ecks-thirty-one" src={item.image} alt={item.alt} />
					</div>
				{/if}
			</li>
		{/each}
	</ul>
	<ul class="marquee" aria-hidden="true" style="animation-duration: {time}s;">
		{#each list_items as item}
			<li>
				{#if link}
					<a href={item.href} target="_blank" class="inline-block">
						<img
							class="eight-eight-ecks-thirty-one eight-eight-ecks-thirty-one-link"
							src={item.image}
							alt={item.alt}
						/>
					</a>
				{:else}
					<div>
						<img class="eighty-eight-ecks-thirty-one" src={item.image} alt={item.alt} />
					</div>
				{/if}
			</li>
		{/each}
	</ul>
</div>

<style>
	.marquee-container {
		@apply relative flex max-w-fit select-none gap-1 overflow-hidden;
	}

	.marquee {
		@apply flex min-w-full flex-shrink-0 justify-around gap-1;
		animation: scroll-left linear infinite;
	}

	.marquee-container:hover .marquee {
		animation-play-state: paused;
	}

	.eight-eight-ecks-thirty-one {
		@apply h-[31px] w-[88px] border border-transparent;
		image-rendering: pixelated !important;
	}

	.eight-eight-ecks-thirty-one-link {
		@apply transition-colors duration-300 ease-in-out hover:border-white;
		@apply border border-transparent;
	}

	@keyframes scroll-left {
		from {
			transform: translateX(0);
		}
		to {
			transform: translateX(calc(-100% - 0.25rem));
		}
	}
</style>
