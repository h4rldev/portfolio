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
			{$page.error?.message}
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
	.error-message-cell {
		@apply relative my-4 inline-flex bg-red-400 p-4;
	}

	.error-corner {
		@apply absolute left-1 top-0 m-0 p-0 text-[12px];
	}
</style>
