<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import LastFM from '$components/LastFM.svelte';
	import Container from '$components/Container.svelte';
	import PausableButtonMarquee from '$components/PausableButtonMarquee.svelte';

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

	import frens from '$data/frens.json';
	import random from '$data/random.json';
</script>

<svelte:head>
	<title>Hello</title>
</svelte:head>

<Container>
	<header>
		<Nav />
	</header>
	<main>
		<section class="me-card">
			<Glass>
				<div class="me-holder">
					<enhanced:img src="/static/me.webp" alt="me" class="size-40 rounded-full object-cover" />
					<div class="greeting-cell-holder">
						<div class="greeting-cell">
							<h1 class="big-hi">{m.hi()}</h1>
							<div class="greeting">
								<p>
									{m.im()} <span class="greeting-name">h4rl</span>
								</p>
								<p>
									{m.basedin()}
									<a href="https://en.wikipedia.org/wiki/Karlstad" target="_blank">{m.located()}</a
									>.
								</p>
							</div>
						</div>
						<p>
							{m.im()}
							<span class="age-number">{age}</span>
							{m.years_old()}
							{m.birthday()}
							<span class="birthday-date">{birthday}</span>.
						</p>
						<p>{m.music()}</p>
						<div class="socials">
							{#if isEmailOpen}
								<div>
									<a href="mailto:contact@h4rl.dev" target="_blank">contact@h4rl.dev</a>
								</div>
							{:else}
								<button class="fake-link text-left" onclick={() => (isEmailOpen = !isEmailOpen)}>
									{m.email()}
								</button>
							{/if}
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
						</div>
					</div>
				</div>
			</Glass>
		</section>
		<section class="whoami">
			<Glass></Glass>
		</section>
		<section class="buttons">
			<Glass>
				<h1>{m.friends()}</h1>
				<PausableButtonMarquee list_items={frens} />

				<h1>{m.random()}</h1>
				<PausableButtonMarquee list_items={random} link={false} time="30s" />
			</Glass>
		</section>
		<section class="lastfm">
			<Glass></Glass>
		</section>
	</main>
</Container>
<footer>
	<Footer />
</footer>

<style>
	.me-holder {
		@apply my-auto inline-flex min-w-[350px] flex-row gap-4;
	}

	.socials {
		@apply flex flex-col text-left text-lg;
	}

	.buttons {
	}

	.lastfm {
		@apply col-span-3;
	}

	.socials-list {
		@apply flex flex-row gap-2;
	}

	.me-card {
		@apply col-span-4 inline-flex h-[100%] flex-col;
	}

	.whoami {
		@apply col-span-5 row-span-2 inline-flex h-[100%] flex-col;
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
		@apply flex flex-row gap-2;
	}

	.greeting-cell-holder {
		@apply my-auto flex flex-col;
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
		@apply mt-8 w-full;
	}

	main {
		@apply mb-8 mt-2 grid grid-cols-9 grid-rows-2 justify-stretch gap-8 font-afacad;
	}

	footer {
		@apply mb-8 flex w-full flex-row justify-center;
	}
</style>
