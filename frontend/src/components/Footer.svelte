<script>
	import { browser } from '$app/environment';

	let uptime = 'Loading...';
	async function fetchData() {
		await new Promise((r) => setTimeout(r, 250)); // Fake waiting for data :3
		if (browser) {
			try {
				const response = await fetch('/api/uptime');
				let data = await response.json();
				uptime = data.uptime;
			} catch (error) {
				uptime = `Error`;
			}
		} else {
			uptime = 'Not available';
		}
	}

	fetchData();
</script>

<div>
	<ul>
		<li>&copy; h4rl {new Date().getFullYear()}.</li>
		<li>
			This website is <a href="https://github.com/h4rldev/FLSC-portfolio">open source</a> and
			licensed under the
			<a href="https://github.com/h4rldev/FLSC-portfolio/blob/main/LICENSE" target="_blank"
				>BSD 3-Clause License</a
			>.
		</li>
		<li>
			This website's contents is licensed under <a
				href="https://creativecommons.org/licenses/by/4.0"
				target="_blank">CC BY 4.0</a
			>.
		</li>
	</ul>
	<ul>
		<li>Uptime: {uptime}.</li>
		<li>Server info: <a href="/server-info">/server-info</a></li>
	</ul>
</div>

<style>
	div {
		@apply z-10 flex w-[80%] min-w-[360px] flex-col items-center justify-center gap-1;
	}
	ul {
		@apply inline-flex flex-row flex-wrap gap-1;
	}
</style>
