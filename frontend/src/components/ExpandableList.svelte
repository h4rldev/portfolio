<script>
	import { browser } from '$app/environment';
	import { getContext } from 'svelte';
	import { slide } from 'svelte/transition';

	let { button_text, button_icon_open, button_icon_close, list_items } = $props();

	let isOpen = $state(false);
</script>

<div class="container {isOpen ? 'container-open' : 'container-closed'}">
	{#if isOpen}
		<button class="button button-open" onclick={() => (isOpen = !isOpen)}>
			<div class="button-text">{@render button_text?.()}</div>
			<div class="icon-placement">
				{@render button_icon_open?.()}
			</div>
		</button>
	{:else}
		<button class="button button-closed" onclick={() => (isOpen = !isOpen)}>
			<div class="button-text">{@render button_text?.()}</div>
			<div class="icon-placement">
				{@render button_icon_close?.()}
			</div>
		</button>
	{/if}

	{#if isOpen}
		<ul class="button-list" transition:slide>
			{#each list_items as item}
				<li>
					<a href={item.href} target="_blank" class="inline-block">
						<img class="eight-eight-ecks-thirty-one" src={item.image} alt={item.alt} />
					</a>
				</li>
			{/each}
		</ul>
	{/if}
</div>

<style>
	.container {
		@apply m-0 w-[256px] min-w-[128px] max-w-[256px] bg-white bg-opacity-10 p-0;
		@apply rounded-lg border-2 border-transparent transition-all duration-300 ease-in-out;
	}

	.container-open {
		@apply border-white;
	}

	.container-closed {
		@apply border-black hover:border-white;
	}

	.button {
		@apply relative m-0 w-full border-2 border-transparent p-0 text-center transition-all duration-300 ease-in-out;
	}

	.button-closed {
		@apply rounded-xl border-b-transparent;
	}

	.button-open {
		@apply rounded-tl-xl rounded-tr-xl hover:border-b-white;
	}

	.button-text {
		@apply mx-2;
	}

	.icon-placement {
		@apply absolute -top-1 right-2 inline-block;
	}

	.button-list {
		@apply mx-2 my-0 flex list-none flex-row flex-wrap justify-center gap-2 pb-4;
	}

	li {
		@apply inline-block h-[31px] w-[88px];
	}
</style>
