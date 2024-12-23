<script>
	import { page } from '$app/stores';
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
</script>

<header>
	<Nav />
</header>

<main>
	<Glass>
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
			<p>
				Return back to
				<a href="/">home</a>?
			</p>
		</section>
	</Glass>
</main>

<footer>
	<Footer />
</footer>

<style>
	header {
		@apply mb-8 mt-8;
	}

	main {
		@apply flex flex-row justify-center text-lg;
	}

	footer {
		@apply my-8 flex flex-row justify-center;
	}

	h1 {
		@apply text-xl;
	}

	.main {
		@apply px-4 pt-4 font-akshar;
	}

	.footer {
		@apply px-4 pb-4 font-akshar;
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
