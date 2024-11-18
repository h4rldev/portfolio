<script>
	export let title, author, date;
</script>

<svelte:head>
	<title>{title} by {author} @ {date}</title>
</svelte:head>

<header>
	<h1 class="title">{title}</h1>
	<p class="meta">
		<span class="author">{author}</span> @ <span class="date">{date}</span>
	</p>
</header>
<main>
	<slot>Page empty???</slot>
</main>
<footer>
	<p>made w &lt;3 by h4rl</p>
	<a href="/posts">Return back to posts?</a>
</footer>

<style>
	header {
	}
</style>
