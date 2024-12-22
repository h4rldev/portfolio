<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';

	let { title, author, date, children } = $props();
</script>

<svelte:head>
	<title>{title} by {author} @ {date}</title>
</svelte:head>

<header>
	<Nav />
	<h1 class="title">{title}</h1>
	<p class="meta">
		<span class="author">{author}</span> @ <span class="date">{date}</span>
	</p>
</header>
<main>
	{@render children?.()}
</main>
<footer>
	<Footer />
</footer>

<style>
</style>
