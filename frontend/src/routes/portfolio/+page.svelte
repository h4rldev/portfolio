<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
	import Glass from '$components/Glass.svelte';

	let { data } = $props();
</script>

<header>
	<Nav {data} />
</header>
<main>
	<section class="qualifications">
		<Glass>
			<h1>Qualifications</h1>
			<p>
				I have experience with front-end development, and back-end development, primarily using
				Svelte, Astro, and TailwindCSS, and for backend I can use Node.js, Express, but prefer using
				compiled languages like C, Rust, Go and other that may be more suitable for my and your
				needs.
			</p>

			<p>
				I have experience with Linux and currently use it for my operating system, specifically
				NixOS, but I am very capable of using a majority of Linux distributions such as Debian,
				Ubuntu, Arch, RHEL, Fedora, Slackware, and others.
			</p>

			<p>
				I have experience with the following programming languages: C, C++, Rust, Go, JavaScript,
				TypeScript, Python, and others. Emacs, and other editors.
			</p>
		</Glass>
	</section>

	<section class="experience">
		<Glass>
			<h1>Experience</h1>
			<p>
				I've been working with a variety of languages and frameworks, and I have experience with the
				following:
			</p>
			<ul>
				<li>Front-end development using Svelte, Astro, and TailwindCSS.</li>
				<li>Back-end development using Rust, C, and Node.js.</li>
				<li>Linux, and Windows</li>
				<li>Git on GitHub, Forgejo, and Codeberg</li>
			</ul>
		</Glass>
	</section>

	<section class="education">
		<Glass>
			<h1>Education</h1>
			<p>
				I graduated from NTI Gymnasiet in IT and Networking in 2024, and I am currently studying to
				get into the Bachelor's program at KTH Royal Institute of Technology in Stockholm, to then
				get into a Master's program in Computer Science at the same institution.
			</p>
		</Glass>
	</section>

	<section class="certifications">
		<Glass>
			<h1>Certifications</h1>
		</Glass>
	</section>
</main>
<footer>
	<Footer />
</footer>

<style>
	header {
		@apply mt-8 w-full;
	}

	main {
		@apply mb-8 mt-2 grid w-full justify-center font-afacad;
	}

	footer {
		@apply mb-8 flex w-full flex-row justify-center;
	}
</style>
