<script>
	import Nav from '$components/Nav.svelte';
	let { data } = $props();
</script>

<header>
	<Nav />
</header>

<h1>hi</h1>
<ul>
	{#each data.posts as { path, title, date, author }}
		<li><a href="../{path}">{title} @ {date} by {author}</a></li>
	{/each}
</ul>

<style>
</style>
