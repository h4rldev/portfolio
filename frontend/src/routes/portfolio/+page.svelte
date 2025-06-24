<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import Container from '$components/Container.svelte';
	import Icon from '@iconify/svelte';
	import Mail from '$components/Mail.svelte';

	let { data } = $props();

	let badges = $state([]);

	async function get_credly_badges() {
		const url =
			'https://cors-anywhere.herokuapp.com/www.credly.com/users/oscar-sjodin-jansson/badges';

		const headers = {
			Accept: 'application/json'
		};

		const response = await fetch(url, { headers });
		const data = await response.json();
		badges = data.data;

		console.log(badges);
	}
</script>

<Container>
	<header>
		<Nav {data} />
	</header>
	<main>
		<div class="about-and-certifications">
			<section class="about">
				<Glass>
					<h1>About me</h1>
					<div class="flex flex-col gap-2">
						<p>
							I am a Karlstad, Sweden based software developer, currently studying to get into the
							Bachelor's program at KTH Royal Institute of Technology in Stockholm during 2026, to
							then get into the Master's program in Computer Science at the same institution.
						</p>
						<p>
							My main focus is back-end development, and native software development in general, but
							I am also capable of front-end development using frameworks like Svelte, Astro, and
							React, making me essentially a full-stack developer. Currently I primarily use C, but
							I am also proficient in Rust, Go, and other languages with C similar syntax. Of
							course, I am also proficient in JavaScript, TypeScript, Python, and others.
						</p>

						<p>
							I am also proficient in Linux, and currently use it for my operating system,
							specifically NixOS, but I am very capable of using a majority of Linux distributions
							such as Debian, Ubuntu, Arch, RHEL, Fedora, Slackware, and others, being very used to
							setting up server and desktop environments manually from tty to interface
						</p>

						<p>
							<span class="font-bold">TL;DR</span>: I am a full-stack developer, proficient in C,
							Rust, JavaScript, TypeScript, Python, and other languages, and proficient in Linux,
							and currently use it for my operating system, specifically NixOS, but I am very
							capable of using a majority of Linux distributions such as Debian, Ubuntu, Arch, RHEL,
							Fedora, Slackware, and others.
						</p>

						<p>
							I'm looking for a job opportunity, so if you're interested in working with me, feel
							free to reach out to me: <Mail />
						</p>
					</div>
				</Glass>
			</section>
			<section class="certifications">
				<Glass>
					<h1>Certifications</h1>
					{#await get_credly_badges()}
						<div class="flex flex-col gap-2">
							<p>Loading badges...</p>
						</div>
					{:then}
						<div>
							<ul class="flex list-none flex-row gap-2 overflow-x-scroll">
								{#each badges as badge}
									<li class="my-2">
										<a
											href={badge.badge_template.url}
											class="flex h-full w-48 flex-col items-center gap-1 rounded-lg border border-solid border-white/10 bg-white bg-opacity-10 p-2 hover:border-cyan-400"
											target="_blank"
										>
											<img
												src={badge.image_url}
												class="max-h-16 min-h-16 min-w-16 max-w-16 rounded-lg"
												alt={badge.badge_template.name}
											/>
											<ul class="static bottom-0 left-0 w-full">
												<li class="text-sm">{badge.badge_template.name}</li>
												<li class="text-xs">
													Issued to {badge.issued_to} by {badge.issuer.entities[0].entity.name} @ {badge.issued_at_date}
												</li>
											</ul>
										</a>
									</li>
								{/each}
							</ul>
						</div>
					{/await}
				</Glass>
			</section>
		</div>

		<div class="skills-and-education">
			<section class="skills">
				<Glass>
					<h1 class="mb-2">Skills</h1>
					<div class="skills-grid">
						<div>
							<h2>Languages</h2>
							<ul class="skills-list">
								<li>
									<a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank">
										<Icon icon="simple-icons:c" class="mx-1 inline w-[1em] align-[-3px]" />
										C
									</a>
								</li>
								<li>
									<a
										href="https://en.wikipedia.org/wiki/Rust_(programming_language)"
										target="_blank"
									>
										<Icon icon="simple-icons:rust" class="mx-1 inline w-[1em] align-[-3px]" />
										Rust
									</a>
								</li>
								<li>
									<a href="https://en.wikipedia.org/wiki/JavaScript" target="_blank">
										<Icon icon="simple-icons:javascript" class="mx-1 inline w-[1em] align-[-3px]" />
										JavaScript
									</a>
								</li>
								<li>
									<a href="https://en.wikipedia.org/wiki/TypeScript" target="_blank">
										<Icon icon="simple-icons:typescript" class="mx-1 inline w-[1em] align-[-3px]" />
										TypeScript
									</a>
								</li>
								<li>
									<a
										href="https://en.wikipedia.org/wiki/Python_(programming_language)"
										target="_blank"
									>
										<Icon icon="simple-icons:python" class="mx-1 inline w-[1em] align-[-3px]" />
										Python
									</a>
								</li>
								<li>
									<a href="https://en.wikipedia.org/wiki/HTML" target="_blank">
										<Icon icon="simple-icons:html5" class="mx-1 inline w-[1em] align-[-3px]" />
										HTML
									</a>
								</li>
								<li>
									<a href="https://en.wikipedia.org/wiki/CSS" target="_blank">
										<Icon icon="simple-icons:css3" class="mx-1 inline w-[1em] align-[-3px]" />
										CSS
									</a>
								</li>
							</ul>
						</div>
						<div>
							<h2>Frameworks</h2>
							<ul class="skills-list">
								<li>
									<a href="https://svelte.dev/" target="_blank">
										<Icon icon="simple-icons:svelte" class="mx-1 inline w-[1em] align-[-3px]" />
										Svelte + SvelteKit
									</a>
								</li>
								<li>
									<a href="https://astro.build/" target="_blank">
										<Icon icon="simple-icons:astro" class="mx-1 inline w-[1em] align-[-3px]" />
										Astro
									</a>
								</li>
								<li>
									<a href="https://reactjs.org/" target="_blank">
										<Icon icon="simple-icons:react" class="mx-1 inline w-[1em] align-[-3px]" />
										React
									</a>
								</li>
								<li>
									<a href="https://ntex.rs/" target="_blank"> Ntex </a>
								</li>
								<li>
									<a href="https://h2o.examp1e.net/" target="_blank"> libh2o </a>
								</li>
							</ul>
						</div>
						<div>
							<h2>Infrastructure</h2>
							<ul class="skills-list">
								<li>
									<a href="https://en.wikipedia.org/wiki/Linux" target="_blank">
										<Icon icon="simple-icons:linux" class="mx-1 inline w-[1em] align-[-3px]" />
										Linux
									</a>
								</li>
								<li>
									<a href="https://en.wikipedia.org/wiki/Windows" target="_blank">
										<Icon icon="simple-icons:windows" class="mx-1 inline w-[1em] align-[-3px]" />
										Windows
									</a>
								</li>
								<li>
									<a href="https://nixos.org/" target="_blank">
										<Icon icon="simple-icons:nixos" class="mx-1 inline w-[1em] align-[-3px]" />
										Nix
									</a>
								</li>
								<li>
									<a href="https://www.docker.com/" target="_blank">
										<Icon icon="simple-icons:docker" class="mx-1 inline w-[1em] align-[-3px]" />
										Docker
									</a>
								</li>
								<li>
									<a href="https://www.cloudflare.com/" target="_blank">
										<Icon icon="simple-icons:cloudflare" class="mx-1 inline w-[1em] align-[-3px]" />
										Cloudflare
									</a>
								</li>
								<li>
									<a href="https://www.hetzner.com/" target="_blank">
										<Icon icon="simple-icons:hetzner" class="mx-1 inline w-[1em] align-[-3px]" />
										Hetzner
									</a>
								</li>
							</ul>
						</div>

						<div>
							<h2>Tools</h2>
							<ul class="skills-list">
								<li>
									<a href="https://neovim.io/" target="_blank">
										<Icon icon="simple-icons:neovim" class="mx-1 inline w-[1em] align-[-3px]" />
										Vim / Neovim
									</a>
								</li>
								<li>
									<a href="https://www.gnu.org/software/emacs/" target="_blank">
										<Icon icon="simple-icons:gnuemacs" class="mx-1 inline w-[1em] align-[-3px]" />
										Emacs
									</a>
								</li>
								<li>
									<a href="https://code.visualstudio.com/" target="_blank">
										<Icon icon="codicon:vscode" class="mx-1 inline w-[1em] align-[-3px]" />
										Visual Studio Code
									</a>
								</li>
								<li>
									<a href="https://git-scm.com/" target="_blank">
										<Icon icon="simple-icons:git" class="mx-1 inline w-[1em] align-[-3px]" />
										Git
									</a>
								</li>
								<li>
									<a href="https://curl.se/" target="_blank">
										<Icon icon="simple-icons:curl" class="mx-1 inline w-[1em] align-[-3px]" />
										curl
									</a>
								</li>
							</ul>
						</div>
					</div>
				</Glass>
			</section>
			<section class="education">
				<Glass>
					<h1>Education</h1>
					<div class="flex flex-col gap-2">
						<p>
							I graduated from <a href="https://ntigymnasiet.se/program/el-och-energiprogrammet/"
								>NTI Gymnasiet in IT and Networking</a
							> 2024.
						</p>
						<p>
							I am also currently studying to get into the Bachelor's program at <a
								href="https://www.kth.se/en">KTH Royal Institute of Technology in Stockholm</a
							> 2026, to then get into the Master's program in Computer Science at the same institution.
						</p>
					</div>
				</Glass>
			</section>
		</div>
	</main>
</Container>
<footer>
	<Footer />
</footer>

<style>
	header {
		@apply mt-8 w-full;
	}

	h1 {
		@apply text-xl font-bold;
	}

	h2 {
		@apply text-lg font-bold;
	}

	.skills-list {
		@apply list-inside list-disc text-lg;
		list-style-type: '> ';
	}

	li::marker {
		@apply font-bold text-pink-300;
	}

	p {
		@apply text-lg;
	}

	main {
		@apply mb-8 mt-2 flex max-w-full flex-row justify-center gap-4 font-afacad;
	}

	footer {
		@apply mb-8 flex w-full flex-row justify-center;
	}

	.about-and-certifications {
		@apply flex w-1/2 flex-col gap-4 font-afacad;
	}

	.skills-and-education {
		@apply flex w-1/2 flex-col gap-4 font-afacad;
	}

	.skills-grid {
		@apply grid grid-cols-2 justify-center gap-4;
	}

	.skills-grid > div {
		@apply rounded-lg border-2 border-gray-500 px-4 py-2;
	}
</style>
