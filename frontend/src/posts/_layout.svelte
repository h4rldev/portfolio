<script>
	import Nav from '$components/Nav.svelte';

	export let title, author, date;
</script>

<svelte:head>
	<title>{title} by {author} @ {date}</title>
</svelte:head>

<header>
	<Nav />

	<h1 class="title togglable">{title}</h1>
	<p class="meta togglable">
		<span class="author">{author}</span> @ <span class="date">{date}</span>
	</p>
</header>
<main class="togglable">
	<slot>Page empty???</slot>
</main>
<footer class="togglable">
	<p>made w &lt;3 by h4rl</p>
	<a href="/posts">Return back to posts?</a>
</footer>

<style>
	header {
	}
</style>
