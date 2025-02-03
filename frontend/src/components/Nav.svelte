<script lang="ts">
	import Container from '$components/Container.svelte';

	import type { AvailableLanguageTag } from '$lib/paraglide/runtime';
	import { languageTag } from '$lib/paraglide/runtime';
	import { i18n } from '$lib/i18n';
	import { goto } from '$app/navigation';

	let { data } = $props();

	import * as m from '$lib/paraglide/messages.js';

	let currentLanguageTag: AvailableLanguageTag = languageTag();

	function switchToLanguage(newLanguage: AvailableLanguageTag) {
		const canonicalPath = i18n.route(data.url);
		const localisedPath = i18n.resolveRoute(canonicalPath, newLanguage);
		goto(localisedPath);
	}
</script>

<nav>
	<ul>
		<li><div>h4rl</div></li>
		<li>
			<a href="/">{m.home()}</a>
		</li>
		<li>
			<a href="/posts">{m.posts()}</a>
		</li>
		<li>
			<a href="/portfolio">{m.portfolio()}</a>
		</li>
		<li>
			<a href="/commissions">{m.commissions()}</a>
		</li>
		<li class="far-right">
			{#if currentLanguageTag === 'sv'}
				<button class="fake-link" onclick={() => switchToLanguage('en')}>🇬🇧</button>
			{:else}
				<button class="fake-link" onclick={() => switchToLanguage('sv')}>🇸🇪</button>
			{/if}
		</li>
	</ul>
</nav>

<style>
	.far-right {
		@apply absolute xxs:bottom-0 xxs:right-0 xxs:top-[-24px] sm:bottom-0 sm:right-0 sm:top-0 md:right-6 md:top-0;
	}

	nav {
		@apply flex flex-row;
	}

	li:nth-child(1) {
		@apply mx-6;
	}

	a {
		@apply h-[24px];
	}

	ul {
		@apply relative z-10 flex w-full flex-row gap-3 font-afacad text-lg xxs:text-base;
	}
</style>
