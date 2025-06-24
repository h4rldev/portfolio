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
		const most_recent_url = `https://api.listenbrainz.org/1/user/h4rl/listens?count=1`;
		const now_playing_url = `https://api.listenbrainz.org/1/user/h4rl/playing-now`;

		try {
			const now_playing_response = await fetch(now_playing_url);
			const now_playing_retrieved_data = await now_playing_response.json();

			if (now_playing_retrieved_data.payload.listens.length > 0) {
				if (!now_playing_retrieved_data.error === 429) {
					time = m.not_available();
					data = 'Ratelimited';
					return;
				}

				if (!now_playing_retrieved_data.payload.listens[0]) {
					time = m.not_available();
					data = 'No data';
					return;
				}

				data = now_playing_retrieved_data.payload.listens[0];
				time = m.now_playing();
				return;
			}

			const response = await fetch(most_recent_url);
			const retrieved_data = await response.json();
			const track = retrieved_data.payload.listens[0];

			if (!track) {
				time = m.not_available();
				data = 'No data';
				return;
			}

			if (retrieved_data.error === 429) {
				time = m.not_available();
				data = 'Ratelimited';
				return;
			}

			const options = {
				hour: 'numeric',
				minute: 'numeric'
			};

			const formatter = new Intl.DateTimeFormat(getLocale(), options);
			const timestamp = 1750788295;
			const date = new Date(timestamp * 1000);
			const time_local = formatter.format(date);

			data = track;
			time = time_local;
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
		<p>{m.error()}: {m.ListenBrainz_ratelimited()}</p>
	{:else}
		{#if time == m.now_playing()}
			<div class="text">
				{m.currently_scrobbling()}
			</div>
		{:else}
			<div class="text">
				{m.last_scrobbled()}
			</div>
		{/if}
		<div class="lastfm-container">
			<div class="image">
				{#if time == m.now_playing()}
					<a
						href="https://musicbrainz.org/recording/{data.track_metadata.additional_info
							.recording_mbid}"
						target="_blank"
					>
						<img
							src="https://coverartarchive.org/release/{data.track_metadata.additional_info
								.release_mbid}/front"
							class="image-thumbnail"
							alt={data.track_metadata.release_name}
						/>
					</a>
				{:else}
					<a
						href="https://musicbrainz.org/recording/{data.track_metadata.mbid_mapping
							.recording_mbid}"
						target="_blank"
					>
						<img
							src="https://coverartarchive.org/release/{data.track_metadata.mbid_mapping
								.release_mbid}/front"
							class="image-thumbnail"
							alt={data.track_metadata.release_name}
						/>
					</a>
				{/if}
			</div>
			<ul>
				<li>
					{#if time == m.now_playing()}
						<a
							href="https://musicbrainz.org/recording/{data.track_metadata.additional_info
								.track_mbid}"
							target="_blank">{data.track_metadata.track_name}</a
						>
					{:else}
						<a
							href="https://musicbrainz.org/recording/{data.track_metadata.mbid_mapping.track_mbid}"
							target="_blank">{data.track_metadata.track_name}</a
						>
					{/if}
				</li>
				<li>
					{#if time == m.now_playing()}
						<a
							href="https://musicbrainz.org/artist/{data.track_metadata.additional_info
								.artist_mbids[0]}"
							target="_blank">{data.track_metadata.artist_name}</a
						>
					{:else}
						<a
							href="https://musicbrainz.org/artist/{data.track_metadata.mbid_mapping
								.artist_mbids[0]}"
							target="_blank">{data.track_metadata.artist_name}</a
						>
					{/if}
				</li>
				<li class="text-xs">
					{#if time == m.now_playing()}
						<a
							href="https://musicbrainz.org/release/{data.track_metadata.additional_info
								.release_mbid}"
							target="_blank">{data.track_metadata.release_name}</a
						>
					{:else}
						<a
							href="https://musicbrainz.org/release/{data.track_metadata.mbid_mapping.release_mbid}"
							target="_blank">{data.track_metadata.release_name}</a
						>
					{/if}
				</li>
				{#if time != m.now_playing()}
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
		@apply flex flex-row items-center gap-1 pt-2 text-sm;
	}

	.image {
		@apply flex max-h-24 min-h-24 min-w-24 max-w-24 flex-col items-center justify-center p-0;
	}

	.image-thumbnail {
		@apply rounded-lg border-2 border-transparent hover:border-blue-400;
		@apply transition-colors duration-300 ease-in-out;
	}

	.lastfm-container {
		@apply flex flex-row gap-4 pt-2 text-sm xl:text-xs 2xl:text-sm;
	}

	ul {
		@apply flex flex-col justify-center;
	}

	li {
		@apply inline xl:w-[90px] 2xl:w-fit;
	}
</style>
