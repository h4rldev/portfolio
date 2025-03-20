<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import Container from '$components/Container.svelte';
	import PausableButtonMarquee from '$components/PausableButtonMarquee.svelte';
	import LastFm from '$components/LastFM.svelte';

	import Icon from '@iconify/svelte';
	import Mail from '$components/Mail.svelte';

	import * as m from '$lib/paraglide/messages.js';
	import { languageTag } from '$lib/paraglide/runtime';

	let { data } = $props();

	import frens from '$data/frens.json';
	import random from '$data/random.json';

	const birthday_date = new Date('2005-09-02');
	const age = Math.floor((Date.now() - birthday_date.getTime()) / 1000 / 60 / 60 / 24 / 365.25);
	const birthday = birthday_date.toLocaleDateString(languageTag(), {
		year: 'numeric',
		month: 'long',
		day: 'numeric'
	});

	let isEmailOpen = $state(false);
</script>

<svelte:head>
	<title>{m.title()}</title>
</svelte:head>

<Container>
	<header>
		<Nav {data} />
	</header>
	<main>
		<section class="me-card">
			<Glass>
				<div class="me-holder">
					<img src="/me.jpg" alt="me" class=" size-40 rounded-full object-cover" />
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
							<p class="age-holder">
								{m.im()}
								<span class="age-number">{age}</span>
								{m.years_old()}
								{m.birthday()}
								<span class="birthday-date">{birthday}</span>.
							</p>
						</div>
						<div class="socials">
							<Mail />
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
								<li>
									<a href="https://ko-fi.com/h4rl3h" target="_blank">
										<Icon icon="simple-icons:kofi" class="inline-block h-[2rem] w-[2rem]" />
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
				<h1 class="text-xl font-bold">{m.whoami()}</h1>
				<p>
					{m.recent()}
					<a href="https://en.wikipedia.org/wiki/Karlstad" target="_blank">{m.located()}</a>.
				</p>
				<p>
					{m.freetime()}
				</p>
				<p class="mt-2">
					{m.genres()}
					<a href="https://rateyourmusic.com/genre/breakcore/" target="_blank">breakcore</a>
					({m.especially()}
					<a href="https://rateyourmusic.com/genre/mashcore/" target="_blank">mashcore</a>{m.and()}
					<a href="https://www.last.fm/tag/dancecore" target="_blank">dancecore</a>),
					<a href="https://rateyourmusic.com/genre/jungle/" target="_blank">jungle</a>,
					<a href="https://rateyourmusic.com/genre/hardcore-edm/" target="_blank">hardcore</a>
					({m.especially()}
					<a href="https://rateyourmusic.com/genre/happy-hardcore/" target="_blank"
						>happy hardcore</a
					>,
					<a href="https://rateyourmusic.com/genre/digital-hardcore/" target="_blank"
						>digital hardcore</a
					>{m.and()}
					<a href="https://rateyourmusic.com/genre/uptempo-hardcore/" target="_blank"
						>uptempo hardcore</a
					>),
					<a href="https://en.wikipedia.org/wiki/Extreme_metal" target="_blank">extreme metal</a>,
					<a href="https://en.wikipedia.org/wiki/J-rock" target="_blank">jrock</a>,
					<a href="https://en.wikipedia.org/wiki/J-pop" target="_blank">jpop</a>
					{m.and()}
					{m.more()}.
				</p>
				<p class="mt-2">
					{m.specialities()}
					<a href="https://www.rust-lang.org/" target="_blank" class="whitespace-nowrap"
						><Icon icon="simple-icons:rust" class="mr-1 inline w-[1em] align-[-3px]" />Rust</a
					>
					{m.or()}
					<a
						href="https://en.wikipedia.org/wiki/C_(programming_language)"
						target="_blank"
						class="whitespace-nowrap"
						><Icon icon="simple-icons:c" class="mr-1 inline w-[1em] align-[-3px]" />C</a
					>
					{m.for_backend()}
					<a href="https://svelte.dev/" target="_blank" class="whitespace-nowrap"
						><Icon icon="simple-icons:svelte" class="mr-1 inline w-[1em] align-[-3px]" />Svelte</a
					>
					{m.or()}
					<a href="https://Astro.build/" target="_blank" class="whitespace-nowrap"
						><Icon icon="simple-icons:astro" class="mr-1 inline w-[1em] align-[-3px]" />Astro</a
					>
					{m._with()}
					<a href="https://tailwindcss.com/" target="_blank" class="whitespace-nowrap"
						><Icon
							icon="simple-icons:tailwindcss"
							class="mr-1 inline w-[1em] align-[-3px]"
						/>TailwindCSS</a
					>
					{m.and()}
					<a href="https://typescriptlang.org/" target="_blank" class="whitespace-nowrap">
						<Icon
							icon="simple-icons:typescript"
							class="mr-1 inline w-[1em] align-[-3px]"
						/>TypeScript</a
					>
					{m.or()}
					<a
						href="https://en.wikipedia.org/wiki/ECMAScript"
						target="_blank"
						class="whitespace-nowrap"
					>
						<Icon
							icon="simple-icons:javascript"
							class="mr-1 inline w-[1em] align-[-3px]"
						/>JavaScript</a
					>
					{m.for_frontend()}.
					{m.picky()}
				</p>
				<p class="mt-2">
					{m.for_the_last()}
					<a href="https://nixos.org/" target="_blank" class="whitespace-nowrap">
						<Icon icon="simple-icons:nixos" class="mr-1 inline w-[1em] align-[-3px]" />NixOS</a
					>
					{m.as_my_operating()}
					<a href="https://neovim.io/" target="_blank" class="whitespace-nowrap">
						<Icon icon="simple-icons:neovim" class="mr-1 inline w-[1em] align-[-3px]" />Neovim</a
					>
					{m.and()}
					<a href="https://zellij.dev/" target="_blank" class="whitespace-nowrap">Zellij</a>.
				</p>
				<p class="mt-2">
					{m.all_my_views()}
				</p>
			</Glass>
		</section>
		<section class="buttons">
			<Glass>
				<div class="button-marquee-container">
					<h1>{m.friends()}</h1>
					<PausableButtonMarquee list_items={frens} />

					<h1>{m.random()}</h1>
					<PausableButtonMarquee list_items={random} />
				</div>
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
	.me-card {
		@apply inline-flex h-full flex-col;
		@apply xxs:col-span-6;
		@apply md:col-span-6;
		@apply lg:col-span-6 lg:row-span-2;
		@apply xl:col-span-4 xl:row-span-1;
	}

	.me-holder {
		@apply my-auto inline-flex w-full items-center gap-4 xxs:flex-col md:flex-row;
	}

	.big-hi {
		@apply flex flex-row items-center justify-center text-5xl font-bold xxs:w-full xxs:text-center md:w-fit md:text-left;
	}

	.birthday-date {
		@apply font-bold;
	}

	.greeting-cell {
		@apply flex flex-row flex-wrap gap-2 text-wrap;
	}

	.greeting-cell-holder {
		@apply my-auto flex flex-col gap-1;
	}

	.greeting-name {
		@apply bg-gradient-to-b from-pink-600 via-purple-500 to-blue-600 bg-clip-text font-bold text-transparent;
	}

	.socials {
		@apply flex flex-col text-left text-lg;
	}

	.age-holder {
		@apply m-0;
	}

	.age-number {
		@apply font-bold;
	}

	.socials-list {
		@apply flex flex-row gap-2;
	}

	.whoami {
		@apply inline-flex h-full flex-col text-lg;
		@apply xxs:col-span-6 xxs:row-span-2;
		@apply md:col-span-6 md:row-span-2;
		@apply lg:row-span-2 xl:col-span-5;
	}

	.buttons {
		@apply inline-flex h-full flex-col;
		@apply xxs:col-span-6;
		@apply md:col-[span_1/span_3];
		@apply xl:col-span-2;
	}

	.lastfm {
		@apply inline-flex h-full flex-col;
		@apply xxs:col-span-6;
		@apply md:col-span-5;
		@apply xl:col-span-2;
	}

	.greeting {
		@apply flex flex-col justify-center;
	}

	header {
		@apply mt-8 w-full;
	}

	main {
		@apply mb-8 mt-2 grid w-full justify-center font-afacad;
		@apply xxs:grid-cols-1 xxs:grid-rows-1 xxs:gap-4;
		@apply md:grid-cols-2 md:grid-rows-1 md:gap-8;
		@apply lg:grid-rows-2 lg:gap-4;
		@apply xl:grid-cols-9 xl:grid-rows-2;
	}

	footer {
		@apply mb-8 flex w-full flex-row justify-center;
	}
</style>
