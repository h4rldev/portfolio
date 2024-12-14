<script>
	import { page } from '$app/stores';
	import Nav from '$components/Nav.svelte';
</script>

<header>
	<Nav />
</header>

<main>
	<section class="main">
		<h1>Error!</h1>
		<p>Couldn't find route!</p>
		<div class="error-message-cell">
			<p class="error-corner">Error Message:</p>
			<code class="error-content">
				{$page.status}
				{$page.error?.message}
			</code>
		</div>
	</section>
</main>

<footer>
	<section class="footer">
		<p>
			Return back to
			<a href="/">home</a>?
		</p>
	</section>
</footer>

<style>
	header {
		@apply mb-12 mt-8;
	}

	main {
		@apply mb-0 mt-4 flex flex-row justify-center;
	}

	footer {
		@apply flex flex-row justify-center;
	}

	h1 {
		@apply text-xl;
	}

	.main {
		@apply px-4 pt-4 font-akshar;
		@apply inline w-[80%] min-w-[360px] rounded-t-xl border-l-2 border-r-2 border-t-2 border-gray-500 bg-white bg-opacity-10 backdrop-blur-sm;
	}

	.footer {
		@apply px-4 pb-4 font-akshar;
		@apply inline w-[80%] min-w-[360px] rounded-b-xl border-b-2 border-l-2 border-r-2 border-gray-500 bg-white bg-opacity-10 backdrop-blur-sm;
	}

	.error-message-cell {
		@apply relative my-4 inline-flex rounded-bl-xl rounded-br-xl rounded-tr-xl border-2 border-red-400 bg-red-600 bg-opacity-40 px-6 pb-4 pt-6;
	}

	.error-content {
		@apply m-0 p-0 text-[14px] leading-none;
	}

	.error-corner {
		@apply absolute left-1 top-0 m-0 p-0 font-mono text-[12px];
	}
</style>
