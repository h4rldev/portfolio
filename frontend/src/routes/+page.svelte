<script>
	import Nav from '$components/Nav.svelte';
	import Draggable from '$components/Draggable.svelte';
</script>

<svelte:head>
	<title>Hello</title>
</svelte:head>

<header>
	<Nav />
	<Draggable>
		{#snippet header()}
			<h1>Hi, I'm h4rl</h1>
		{/snippet}
		{#snippet handle()}
			<div class="handle"></div>
		{/snippet}
		{#snippet forward()}
			<sub>drag me &#x219d;</sub>
		{/snippet}
		{#snippet backward()}
			<sub>&#x219c; drag me</sub>
		{/snippet}
		{#snippet still()}
			<sub>drag me</sub>
		{/snippet}
	</Draggable>
</header>
<main></main>
<footer>
	<p>made with &lt;3</p>
</footer>

<style>
	header {
		@apply p4 m0;
	}

	.introduction {
		@apply inline-flex flex-col p0 m0;
	}

	h1 {
		@apply inline text-2xl p0 m0;
	}

	sub {
		@apply inline text-center;
	}

	.handle {
		@apply cursor-grab bg-blue-400 rounded-full p2;
	}
</style>
