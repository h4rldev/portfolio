<script>
	import { page } from '$app/stores';
</script>

<header>
	<h1>Error {$page.status}</h1>
</header>

<main>
	<p>Couldn't find post route :3</p>
	<div class="error-message-cell">
		<p class="error-corner">Error Message:</p>
		<code class="error-content">
			{$page.error.message}
		</code>
	</div>
</main>

<footer>
	<div>
		<p>
			Return back to
			<a href="/posts"><code>/posts</code></a>?
		</p>
	</div>
</footer>

<style>
	p {
	}
	.error-message-cell {
		@apply bg-red-400 p6 inline-flex my4 relative;
	}

	.error-corner {
		@apply absolute left-1 top-0 p0 m0 text-[12px];
	}

	.error-content {
		@apply text-md;
	}
</style>
