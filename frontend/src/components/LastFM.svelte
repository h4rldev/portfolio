<script>
	import { env } from '$env/dynamic/public';
	import { browser } from '$app/environment';
	import { getLocale } from '$lib/paraglide/runtime';
	import { onDestroy } from 'svelte';

	import Icon from '@iconify/svelte';
	import { m } from '$lib/paraglide/messages.js';

	let data = $state('');
	let dataPromise = $state(0);
	let time = $state(null);
	let intervalId = $state(Promise.resolve(null));

	intervalId = setInterval(async () => {
		dataPromise = fetchData();
	}, 1000 * 30);

	const fetchData = async () => {
		if (!browser) return;

		const api_key = '247b1a4b7dd5d6c42bb732941db23aef';
		const url = `https://ws.audioscrobbler.com/2.0/?method=user.getrecenttracks&user=h4rl3h&api_key=${api_key}&format=json`;

		try {
			const response = await fetch(url);
			const retrieved_data = await response.json();
			const track = retrieved_data.recenttracks.track[0];

			if (!track) {
				time = m.not_available();
				data = 'No data';
				return;
			}

			if (track.error === 29) {
				time = m.not_available();
				data = 'Ratelimited';
				return;
			}

			if (track['@attr']?.nowplaying === 'true') {
				data = track;
			} else {
				let time_gmt = new Date(track.date['#text']);
				let time_offset = -time_gmt.getTimezoneOffset();
				let time_local = new Date(time_gmt.getTime() + time_offset * 60 * 1000).toLocaleTimeString(
					getLocale(),
					{
						hour: 'numeric',
						minute: 'numeric'
					}
				);
				data = track;
				time = time_local;
			}
		} catch (error) {
			console.error('Error fetching data:', error);
			throw error;
		}
	};

	onDestroy(() => {
		clearInterval(intervalId);
	});
</script>

{#await fetchData()}
	<p>{m.loading()}</p>
{:then}
	{#if data == 'Ratelimited'}
		<p>{m.error()}: {m.LastFM_ratelimited()}</p>
	{:else}
		{#if data['@attr']?.nowplaying === 'true'}
			<div class="text">
				{m.now_playing()}
				<a href="https://last.fm" target="_blank"
					><Icon icon="simple-icons:lastdotfm" class="w-[1em]" /></a
				>
			</div>
		{:else}
			<div class="text">
				{m.last_listened()}
				<a href="https://last.fm" target="_blank"
					><Icon icon="simple-icons:lastdotfm" class="w-[1em]" /></a
				>
			</div>
		{/if}
		<div class="lastfm-container">
			<div class="image">
				<a href={data.url} target="_blank">
					<img src={data.image[3]['#text']} class="image-thumbnail" alt={data.name} />
				</a>
			</div>
			<ul>
				<li><a href={data.url} target="_blank">{data.name}</a></li>
				<li>
					<a href="https://www.last.fm/music/{data.artist['#text']}" target="_blank"
						>{data.artist['#text']}</a
					>
				</li>
				<li class="text-xs">
					<a
						href="https://www.last.fm/music/{data.artist['#text']}/{data.album['#text']}"
						target="_blank">{data.album['#text']}</a
					>
				</li>
				{#if !data['@attr']?.nowplaying}
					<li>
						{m.time_of_listening()}: {time}
					</li>
				{/if}
			</ul>
		</div>
	{/if}
{:catch error}
	<p class="text-red-500">{error.message}</p>
{/await}

<style>
	.text {
		@apply flex flex-row items-center gap-1 text-sm;
	}

	.image {
		@apply flex max-h-28 min-h-28 min-w-28 max-w-28 flex-col items-center justify-center p-0;
	}

	.image-thumbnail {
		@apply rounded-lg border-2 border-transparent hover:border-blue-400;
		@apply transition-colors duration-300 ease-in-out;
	}

	.lastfm-container {
		@apply flex flex-row items-center gap-4 text-sm xl:text-xs 2xl:text-sm;
	}

	ul {
		@apply flex flex-col justify-center;
	}

	li {
		@apply inline xl:w-[90px] 2xl:w-fit;
	}
</style>
