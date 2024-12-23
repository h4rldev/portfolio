<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	let { data } = $props();
</script>

<header>
	<Nav />
</header>

<main>
	<Glass>
		<section class="posts">
			<h1>Posts</h1>
			<input type="text" placeholder="Search..." />
			<ul>
				{#each data.posts as { path, title, date, author }}
					<li><a href="../{path}">{title} @ {date} by {author}</a></li>
				{/each}
			</ul>
			<p>Return back to <a href="/">home</a>?</p>
		</section>
	</Glass>
</main>

<footer>
	<Footer />
</footer>

<style>
	header {
		@apply my-8;
	}

	.posts {
		@apply flex h-full w-full flex-col content-center items-center justify-center;
	}

	ul {
		@apply flex flex-col flex-wrap items-center justify-center gap-4 p-0;
	}

	footer {
		@apply my-8 flex flex-row justify-center;
	}
</style>
