<script>
	import { draggable } from '@neodrag/svelte';

	let previous_position = $state(0);
	let current_position = $state(0);
	let current_direction = $state('');

	$effect(() => {
		if (current_position > previous_position) {
			current_direction = 'forward';
		} else if (current_position === previous_position) {
			current_direction = 'still';
		} else {
			current_direction = 'backward';
		}
	});

	/**
	 * @typedef {import('svelte').Snippet} Snippet
	 * @type {{ header: Snippet, handle: Snippet, forward: Snippet | undefined, still: Snippet | undefined, backward: Snippet | undefined, axis: string | undefined }}
	 */
	let {
		header,
		handle,
		forward = undefined,
		still = undefined,
		backward = undefined,
		axis = 'x'
	} = $props();
</script>

<div
	class="draggable togglable"
	use:draggable={{
		axis,
		bounds: 'body',
		onDrag: ({ offsetX, offsetY, currentNode }) => {
			const element = currentNode;
			previous_position = current_position;
			current_position = offsetX;

			element.style.transition = 'transform 0.5s ease-out';
			element.style.transform = `translate(${offsetX}px, ${offsetY}px)`;
		},
		onDragEnd: () => {
			previous_position = current_position;
		},
		handle: '.handle'
	}}
>
	{@render header()}
	{@render handle()}
	{#if current_direction === 'forward'}
		{@render forward?.()}
	{:else if current_direction === 'still'}
		{@render still?.()}
	{:else}
		{@render backward?.()}
	{/if}
</div>

<!--
	&#x219d; ->
	&#x219c; <-
-->

<style>
	.draggable {
		@apply inline-flex flex-col p0 m0;
	}
</style>
