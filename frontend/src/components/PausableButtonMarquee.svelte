<script lang="ts">
	let { list_items } = $props();
</script>

<div class="marquee-container">
	<ul class="marquee">
		{#each list_items as item}
			<li>
				<a href={item.href} target="_blank" class="inline-block">
					<img class="eight-eight-ecks-thirty-one" src={item.image} alt={item.alt} />
				</a>
			</li>
		{/each}
	</ul>
	<ul class="marquee" aria-hidden="true">
		{#each list_items as item}
			<li>
				<a href={item.href} target="_blank" class="inline-block">
					<img class="eight-eight-ecks-thirty-one" src={item.image} alt={item.alt} />
				</a>
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
		animation: scroll-left 10s linear infinite;
	}

	.marquee-container:hover .marquee {
		animation-play-state: paused;
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
