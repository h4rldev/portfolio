<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import Container from '$components/Container.svelte';
	let { data } = $props();
</script>

<Container>
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
</Container>

<footer>
	<Footer />
</footer>

<style>
	header {
		@apply mt-8;
	}

	main {
		@apply mb-8 mt-2 font-afacad;
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
