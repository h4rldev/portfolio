<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import LastFM from '$components/LastFM.svelte';
	import ExpandableList from '$components/ExpandableList.svelte';

	import Icon from '@iconify/svelte';

	import * as m from '$lib/paraglide/messages.js';
	import { languageTag } from '$lib/paraglide/runtime';

	const birthday_date = new Date('2005-09-02');
	const age = ((Date.now() - birthday_date.getTime()) / 1000 / 60 / 60 / 24 / 365).toFixed(0);
	const birthday = birthday_date.toLocaleDateString(languageTag(), {
		year: 'numeric',
		month: 'long',
		day: 'numeric'
	});

	let isEmailOpen = $state(false);

	const frens = [
		{
			href: 'https://lenooby09.github.io/',
			image: '/88x31/frens/lenooby09.png',
			alt: 'lenooby09'
		},
		{
			href: 'https://onz.ee/',
			image: '/88x31/frens/onzecki.png',
			alt: 'onzecki'
		},
		{
			href: 'https://meow-d.github.io/',
			image: '/88x31/frens/meow_d.webp',
			alt: 'meow-d'
		}
	];

	const communities = [
		{
			href: 'https://github.com/h4rldev',
			image: '/88x31/frens/lenooby09.png',
			alt: 'github'
		}
	];
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
					<p>I like to listen to breakcore, mashcore, dancecore, jungle, metal, jrock, and more.</p>

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
			<div class="lastfm-container">
				<p>{m.lastfm()}</p>
				<LastFM />
			</div>
		</section>
		<section class="socials">
			<h1>{m.socials()}</h1>
			<ul class="socials-list">
				<li>
					<a href="https://github.com/h4rldev" target="_blank">
						<Icon icon="simple-icons:github" class="inline-block h-[2rem] w-[2rem]" />
					</a>
				</li>
				<li>
					<a href="https://bsky.app/profile/h4rl.dev" target="_blank">
						<Icon icon="simple-icons:bluesky" class="inline-block h-[2rem] w-[2rem]" />
					</a>
				</li>
				<li>
					<a href="https://www.last.fm/user/h4rl3h" target="_blank">
						<Icon icon="simple-icons:lastdotfm" class="inline-block h-[2rem] w-[2rem]" />
					</a>
				</li>
				<li>
					<a href="https://discord.com/users/275689969601871882" target="_blank">
						<Icon icon="simple-icons:discord" class="inline-block h-[2rem] w-[2rem]" />
					</a>
				</li>
			</ul>
			{#if isEmailOpen}
				<div class="email-container">
					<a href="mailto:contact@h4rl.dev" target="_blank">contact@h4rl.dev</a>
				</div>
			{:else}
				<button class="fake-link" onclick={() => (isEmailOpen = !isEmailOpen)}>
					{m.email()}
				</button>
			{/if}
		</section>
		<section class="friends-communities-and-lastfm">
			<div class="friends-communities">
				<div>
					<ExpandableList list_items={frens}>
						{#snippet button_text()}
							{m.friends()}
						{/snippet}
						{#snippet button_icon_open()}
							<Icon icon="iwwa:arrow-up" class="inline-block h-[1rem] w-[1rem]" />
						{/snippet}
						{#snippet button_icon_close()}
							<Icon icon="iwwa:arrow-down" class="inline-block h-[100%] w-[100%]" />
						{/snippet}
					</ExpandableList>
				</div>
				<div>
					<ExpandableList list_items={communities}>
						{#snippet button_text()}
							{m.communities()}
						{/snippet}
						{#snippet button_icon_open()}
							<Icon icon="iwwa:arrow-up" class="inline-block h-[1rem] w-[1rem]" />
						{/snippet}
						{#snippet button_icon_close()}
							<Icon icon="iwwa:arrow-down" class="inline-block h-[100%] w-[100%]" />
						{/snippet}
					</ExpandableList>
				</div>
			</div>
			<div class="my-banner">
				<p>My 88x31</p>
				<img src="/88x31/me.png" class="eight-eight-ecks-thirty-one" alt="me" />
				<p>Feel free to copy it if you want.</p>
			</div>
		</section>
		<section></section>
	</Glass>
</main>
<footer>
	<Footer />
</footer>

<style>
	.socials {
		@apply my-8 flex flex-col items-center justify-center text-lg;
	}

	.socials-list {
		@apply flex flex-row flex-wrap items-center justify-center gap-2;
	}

	.my-banner {
		@apply mt-8 flex flex-col items-center justify-center text-center;
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

	.lastfm-container {
		@apply mt-8;
	}

	.greeting {
		@apply flex flex-col justify-center;
	}

	.greeting p {
		@apply m-0 p-0 leading-5;
	}

	header {
		@apply my-8 w-full;
	}

	.friends-communities-and-lastfm {
		@apply my-8 flex flex-col items-center;
	}

	.friends-communities {
		@apply flex flex-row flex-wrap items-center gap-10;
	}

	.eight-eight-ecks-thirty-one {
		@apply h-[31px] w-[88px] border border-transparent;
		@apply transition-colors duration-300 ease-in-out hover:border-white;
		image-rendering: pixelated !important;
	}

	.intro {
		@apply flex w-full flex-col content-center items-center justify-center;
	}

	main {
		@apply mb-8 mt-4 flex w-full flex-row justify-center font-afacad;
	}

	footer {
		@apply mb-8 flex w-full flex-row justify-center;
	}
</style>
