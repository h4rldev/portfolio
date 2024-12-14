<script>
	import { browser } from '$app/environment';

	let uptime;
	async function fetchData() {
		if (browser) {
			const response = await fetch('/api/uptime');
			let data = await response.json();
			uptime = data.uptime;
		}
	}
	fetchData();
</script>

<div>
	<ul>
		<li>&copy; h4rl {new Date().getFullYear()}.</li>
		<li>
			This website is <a href="https://github.com/h4rldev/FLSC-portfolio">open source</a> and
			licensed under
			<a href="https://github.com/h4rldev/FLSC-portfolio/blob/main/LICENSE"
				>the BSD-3 Clause License</a
			>.
		</li>
		<li>
			This website's contents is licensed under <a
				href="https://creativecommons.org/licenses/by/4.0">CC BY 4.0</a
			>.
		</li>
		<li>Server info: <a href="/api/server-info">here</a></li>
		<li>Server uptime: {uptime}</li>
	</ul>
</div>

<style>
	div {
		@apply flex w-[80%] min-w-[360px] flex-row justify-center;
	}
	ul {
		@apply inline-flex flex-row flex-wrap gap-3;
	}
</style>
