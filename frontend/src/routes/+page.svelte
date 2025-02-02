<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import Container from '$components/Container.svelte';
	import PausableButtonMarquee from '$components/PausableButtonMarquee.svelte';
	import LastFm from '$components/LastFM.svelte';

	import Icon from '@iconify/svelte';

	import * as m from '$lib/paraglide/messages.js';
	import { languageTag } from '$lib/paraglide/runtime';

	import frens from '$data/frens.json';
	import random from '$data/random.json';

	const birthday_date = new Date('2005-09-02');
	const age = ((Date.now() - birthday_date.getTime()) / 1000 / 60 / 60 / 24 / 365).toFixed(0);
	const birthday = birthday_date.toLocaleDateString(languageTag(), {
		year: 'numeric',
		month: 'long',
		day: 'numeric'
	});

	let isEmailOpen = $state(false);
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
						<div>
							<div class="greeting-cell">
								<h1 class="big-hi">{m.hi()}</h1>
								<div class="greeting">
									<p>
										{m.im()} <span class="greeting-name">h4rl</span>
									</p>
									<p>
										{m.basedin()}
										<a href="https://en.wikipedia.org/wiki/Karlstad" target="_blank"
											>{m.located()}</a
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
						</div>
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
								<li>
									<a href="https://steamcommunity.com/id/h4rl3h" target="_blank">
										<Icon icon="simple-icons:steam" class="inline-block h-[2rem] w-[2rem]" />
									</a>
								</li>
							</ul>
						</div>
					</div>
				</div>
			</Glass>
		</section>
		<section class="whoami">
			<Glass>
				<h1 class="text-xl font-bold">Who am I?</h1>
				<p>
					I'm a recent graduate at NTI Gymnasiet in <a
						href="https://en.wikipedia.org/wiki/Karlstad"
						target="_blank">Karlstad, Sweden</a
					>
				</p>
				<p>
					And in my free time I like to play games, work on projects, watch anime, and listen to
					music.
				</p>
				<p class="mt-4">
					My favorite genres being <a
						href="https://rateyourmusic.com/genre/breakcore/"
						target="_blank">breakcore</a
					>
					(specifically
					<a href="https://rateyourmusic.com/genre/mashcore/" target="_blank">mashcore</a>, and
					<a href="https://www.last.fm/tag/dancecore" target="_blank">dancecore</a>),
					<a href="https://rateyourmusic.com/genre/jungle/" target="_blank">jungle</a>,
					<a href="https://rateyourmusic.com/genre/hardcore-edm/" target="_blank">hardcore</a>
					(specifically
					<a href="https://rateyourmusic.com/genre/happy-hardcore/" target="_blank"
						>happy hardcore</a
					>,
					<a href="https://rateyourmusic.com/genre/digital-hardcore/" target="_blank"
						>digital hardcore</a
					>, and
					<a href="https://rateyourmusic.com/genre/uptempo-hardcore/" target="_blank"
						>uptempo hardcore</a
					>),
					<a href="https://en.wikipedia.org/wiki/Extreme_metal" target="_blank">extreme metal</a>,
					<a href="https://en.wikipedia.org/wiki/J-rock" target="_blank">jrock</a>,
					<a href="https://en.wikipedia.org/wiki/J-pop" target="_blank">jpop</a>.
				</p>
				<p class="mt-4">
					My specialties in programming are concurrent computing, networking, and web development,
					primarily using <a href="https://www.rust-lang.org/" target="_blank"
						><Icon icon="devicon:rust" class="align-center inline w-[1em] align-[-3px]" /> Rust</a
					>
					and
					<Icon icon="devicon:c" class="align-center inline w-[1em] align-[-3px]" /> C for the backend,
					and
					<a href="https://svelte.dev/" target="_blank">Svelte</a>
					and
					<a href="https://typescriptlang.org/" target="_blank">TypeScript</a> for the frontend. frontend.
				</p>
				<p class="mt-4">
					I am also interested in application development, such as in <a
						href="https://gtk.org/"
						target="_blank">GTK</a
					>, <a href="https://qt.io/" target="_blank">Qt</a>, and other cross-platform frameworks.
				</p>
				<p class="mt-4">
					For the last few years, I've been using Linux and currently use <a
						href="https://nixos.org/"
						target="_blank">NixOS</a
					>
					as my operating system, and for programming, I use
					<a href="https://neovim.io/" target="_blank">Neovim</a>, and
					<a href="https://zellij.dev/" target="_blank">Zellij</a>.
				</p>
				<p class="mt-4">
					Any of my views on the internet are my own and do not represent the opinions of any
					employer or organization.
				</p>
			</Glass>
		</section>
		<section class="buttons">
			<Glass>
				<h1>{m.friends()}</h1>
				<PausableButtonMarquee list_items={frens} />

				<h1>{m.random()}</h1>
				<PausableButtonMarquee list_items={random} link={false} />
			</Glass>
		</section>
		<section class="lastfm">
			<Glass>
				<LastFm />
			</Glass>
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

	.lastfm {
		@apply col-span-2;
	}

	.socials-list {
		@apply flex flex-row gap-2;
	}

	.buttons {
		@apply col-span-2;
	}

	.me-card {
		@apply col-span-4 inline-flex h-[100%] flex-col;
	}

	.whoami {
		@apply col-span-5 row-span-2 inline-flex h-[100%] flex-col text-lg;
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
		@apply my-auto flex flex-col gap-2;
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
