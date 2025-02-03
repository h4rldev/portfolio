<script>
	import { browser } from '$app/environment';
	import { page } from '$app/stores';

	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import Container from '$components/Container.svelte';

	import * as m from '$lib/paraglide/messages.js';

	const api_url = 'https://api.thecatapi.com/v1/images/search';

	let cat = $state();

	async function getCat() {
		if (!browser) {
			cat = m.not_available();
			return;
		}

		const response = await fetch(api_url, {
			method: 'GET',
			headers: {
				'Content-Type': 'application/json'
			}
		});

		const retrieved_data = await response.json();
		cat = retrieved_data[0].url;
	}
</script>

<Container>
	<header>
		<Nav />
	</header>

	<main>
		<section class="error">
			<Glass>
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
			</Glass>
		</section>
		<section class="cats">
			<Glass>
				<div class="cats-holder">
					<p>Accept this cat as an apology for the error!</p>
					{#await getCat()}
						<p>Loading...</p>
					{:then}
						<img src={cat} alt="cat" class="object-cover" />
					{:catch error}
						<p style="text-red-500">{error.message}</p>
					{/await}
				</div>
			</Glass>
		</section>
		<section class="explode">
			<Glass>
				<p>Explode!</p>
			</Glass>
		</section>
	</main>
</Container>

<footer>
	<Footer />
</footer>

<style>
	header {
		@apply mt-8 w-full;
	}

	main {
		@apply mb-8 mt-2 grid w-full justify-center font-afacad text-lg;
		@apply grid-cols-3 gap-4;
	}

	footer {
		@apply mb-8 flex w-full flex-row justify-center;
	}

	h1 {
		@apply text-xl;
	}

	.error {
		@apply col-span-1;
	}

	.cats {
		@apply col-span-1;
	}

	.cats-holder {
		@apply flex flex-col items-center justify-center;
	}

	.explode {
		@apply col-span-1;
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
