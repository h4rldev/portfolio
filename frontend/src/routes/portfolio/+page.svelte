<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';
	import Container from '$components/Container.svelte';
	import Icon from '@iconify/svelte';
	import Mail from '$components/Mail.svelte';

	let { data } = $props();
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
							<ul>
								<li>
									<Icon icon="simple-icons:c" class="mx-1 inline w-[1em] align-[-3px]" />
									C
								</li>
								<li>
									<Icon icon="simple-icons:rust" class="mx-1 inline w-[1em] align-[-3px]" />
									Rust
								</li>
								<li>
									<Icon icon="simple-icons:javascript" class="mx-1 inline w-[1em] align-[-3px]" />
									JavaScript
								</li>
								<li>
									<Icon icon="simple-icons:typescript" class="mx-1 inline w-[1em] align-[-3px]" />
									TypeScript
								</li>
								<li>
									<Icon icon="simple-icons:python" class="mx-1 inline w-[1em] align-[-3px]" />
									Python
								</li>
								<li>
									<Icon icon="simple-icons:html5" class="mx-1 inline w-[1em] align-[-3px]" />
									HTML
								</li>
								<li>
									<Icon icon="simple-icons:css3" class="mx-1 inline w-[1em] align-[-3px]" />
									CSS
								</li>
							</ul>
						</div>
						<div>
							<h2>Frameworks</h2>
							<ul>
								<li>
									<Icon icon="simple-icons:svelte" class="mx-1 inline w-[1em] align-[-3px]" />
									Svelte + SvelteKit
								</li>
								<li>
									<Icon icon="simple-icons:astro" class="mx-1 inline w-[1em] align-[-3px]" />
									Astro
								</li>
								<li>
									<Icon icon="simple-icons:react" class="mx-1 inline w-[1em] align-[-3px]" />
									React
								</li>
								<li>Ntex</li>
								<li>libh2o</li>
							</ul>
						</div>
						<div>
							<h2>Infrastructure</h2>
							<ul>
								<li>
									<Icon icon="simple-icons:linux" class="mx-1 inline w-[1em] align-[-3px]" />
									Linux
								</li>
								<li>
									<Icon icon="simple-icons:windows" class="mx-1 inline w-[1em] align-[-3px]" />
									Windows
								</li>
								<li>
									<Icon icon="simple-icons:nixos" class="mx-1 inline w-[1em] align-[-3px]" />
									Nix
								</li>
								<li>
									<Icon icon="simple-icons:docker" class="mx-1 inline w-[1em] align-[-3px]" />
									Docker
								</li>
								<li>
									<Icon icon="simple-icons:cloudflare" class="mx-1 inline w-[1em] align-[-3px]" />
									Cloudflare
								</li>
								<li>
									<Icon icon="simple-icons:hetzner" class="mx-1 inline w-[1em] align-[-3px]" />
									Hetzner
								</li>
							</ul>
						</div>

						<div>
							<h2>Tools</h2>
							<ul>
								<li>
									<Icon icon="simple-icons:neovim" class="mx-1 inline w-[1em] align-[-3px]" />
									Vim / Neovim
								</li>
								<li>
									<Icon icon="simple-icons:gnuemacs" class="mx-1 inline w-[1em] align-[-3px]" />
									Emacs
								</li>
								<li>
									<Icon icon="codicon:vscode" class="mx-1 inline w-[1em] align-[-3px]" />
									Visual Studio Code
								</li>
								<li>
									<Icon icon="simple-icons:git" class="mx-1 inline w-[1em] align-[-3px]" />
									Git
								</li>
								<li>
									<Icon icon="simple-icons:curl" class="mx-1 inline w-[1em] align-[-3px]" />
									curl
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
						<p>I graduated from NTI Gymnasiet in IT and Networking during 2024.</p>
						<p>
							I am also currently studying to get into the Bachelor's program at KTH Royal Institute
							of Technology in Stockholm, to then get into the Master's program in Computer Science
							at the same institution.
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

	ul {
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
		@apply mb-8 mt-2 flex flex-row justify-center gap-4 font-afacad;
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
