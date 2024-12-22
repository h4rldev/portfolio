<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import LastFM from '$components/LastFM.svelte';

	import Icon from '@iconify/svelte';

	import * as m from '$lib/paraglide/messages.js';
	import { languageTag } from '$lib/paraglide/runtime';

	import { slide } from 'svelte/transition';

	const birthday_date = new Date('2005-09-02');
	const age = ((Date.now() - birthday_date.getTime()) / 1000 / 60 / 60 / 24 / 365).toFixed(0);
	const birthday = birthday_date.toLocaleDateString(languageTag(), {
		year: 'numeric',
		month: 'long',
		day: 'numeric'
	});

	let isOpen = false;
</script>

<svelte:head>
	<title>Hello</title>
</svelte:head>

<header>
	<Nav />
</header>
<main>
	<Glass>
		<section class="intro">
			<div class="text-holder">
				<div class="greeting-cell">
					<h1 class="big-hi">{m.hi()}</h1>
					<div class="greeting">
						<p>
							{m.im()} <span class="greeting-name">h4rl</span>
						</p>
						<p>
							{m.basedin()}
							<a href="https://en.wikipedia.org/wiki/Karlstad" target="_blank">{m.located()}</a>.
						</p>
					</div>
				</div>
				<div>
					<p class="age">
						{m.im()}
						<span class="age-number">{age}</span>
						{m.years_old()}
						{m.birthday()}
						<span class="birthday-date">{birthday}</span>.
					</p>

					<div class="specialize">
						<p>{m.specialize()} {m.environments()}, {m.ilikeusing()}</p>
						<p>C, Rust, Bash, Javascript, TypeScript, ... {m.andmore()}</p>
					</div>
					<div class="frameworks">
						<p>{m.ilikeframeworks()}:</p>
						<p>{m.frameworks()}</p>
					</div>
					<p>{m.interests()}</p>
				</div>
			</div>
		</section>
		<hr />
		<section class="friends-communities-and-lastfm">
			<div class="friends-communities">
				<div>
					{#if isOpen}
						<button on:click={() => (isOpen = !isOpen)}>
							<span class="font-bold>">&wedge;</span> {m.friends()}</button
						>
					{:else}
						<button on:click={() => (isOpen = !isOpen)}>
							<span class="font-bold">&vee;</span> {m.friends()}</button
						>
					{/if}

					{#if isOpen}
						<ul transition:slide>
							<li>
								<a href="https://lenooby09.github.io/" target="_blank">
									<img class="eight-eight-ecks-thirty-one" src="/lenooby09.png" alt="lenooby09" />
								</a>
							</li>
						</ul>
					{/if}
				</div>
				<div><h1>{m.communities()}</h1></div>
			</div>
			<div>
				<p>{m.lastfm()}</p>
				<LastFM />
			</div>
		</section>
	</Glass>
</main>
<footer>
	<Footer />
</footer>

<style>
	hr {
		@apply mx-auto my-8 w-[10%] rounded-full border-2 border-gray-200;
	}

	.age {
		@apply mb-8 text-center;
	}

	.specialize {
		@apply mb-8 flex flex-col text-lg;
	}

	.frameworks {
		@apply flex flex-col text-lg;
	}

	.age-number {
		@apply font-bold;
	}

	.birthday-date {
		@apply font-bold;
	}

	.greeting-cell {
		@apply mt-8 flex flex-row items-center justify-center gap-2;
	}

	.greeting-name {
		@apply bg-gradient-to-b from-pink-600 via-purple-500 to-blue-600 bg-clip-text font-bold text-transparent;
	}

	.big-hi {
		@apply flex flex-row items-center justify-center text-5xl font-bold;
	}

	.greeting {
		@apply flex flex-col justify-center;
	}

	.greeting p {
		@apply m-0 p-0 leading-5;
	}

	header {
		@apply mb-8 mt-8;
	}

	.friends-communities-and-lastfm {
		@apply flex flex-col items-center;
	}

	.friends-communities {
		@apply flex flex-row items-center justify-center gap-32;
	}

	.eight-eight-ecks-thirty-one {
		@apply h-[31px] w-[88px] border border-transparent;
		@apply transition-colors duration-300 ease-in-out hover:border-white;
		image-rendering: pixelated !important;
	}

	section.intro {
		@apply flex w-full flex-col content-center items-center justify-center;
	}

	main {
		@apply mb-8 mt-4 flex flex-row justify-center font-afacad;
	}

	footer {
		@apply flex flex-row justify-center;
	}
</style>
