<script>
	import { env } from '$env/dynamic/public';
	import { browser } from '$app/environment';
	import Icon from '@iconify/svelte';

	const api_key = '247b1a4b7dd5d6c42bb732941db23aef';
	const url = `https://ws.audioscrobbler.com/2.0/?method=user.getrecenttracks&user=h4rl3h&api_key=${api_key}&format=json`;

	let data;
	async function fetchData() {
		if (browser) {
			const response = await fetch(url);
			const retrieved_data = await response.json();
			data = retrieved_data.recenttracks.track[0];
		}
	}

	fetchData();
</script>

{#if data}
	<div class="lastfm-container">
		<div class="icon-and-image">
			<Icon icon="logos:lastfm" class="w-[2rem]" />
			<a href={data.url} target="_blank">
				<img src={data.image[1]['#text']} alt={data.name} />
			</a>
		</div>
		<ul>
			<li class="mt-3"><a href={data.url} target="_blank">{data.name}</a></li>
			<li class="text-xs">
				<a href="https://www.last.fm/music/{data.artist['#text']}" target="_blank"
					>{data.artist['#text']}</a
				>
			</li>
			<li class="text-xs">{data.album['#text']}</li>
			<li class="text-xs">{data.date['#text']}</li>
		</ul>
	</div>
{:else}
	<p>Loading...</p>
{/if}

<style>
	.icon-and-image {
		@apply flex flex-col items-center justify-center;
	}

	.lastfm-container {
		@apply flex flex-row gap-2 text-sm;
	}

	ul {
		@apply flex flex-col justify-center text-sm;
	}
</style>
