<script lang="ts">
	import Container from '$components/Container.svelte';

	import type { AvailableLanguageTag } from '$lib/paraglide/runtime';
	import { languageTag } from '$lib/paraglide/runtime';
	import { i18n } from '$lib/i18n';
	import { page } from '$app/stores';
	import { goto } from '$app/navigation';

	import * as m from '$lib/paraglide/messages.js';

	let currentLanguageTag: AvailableLanguageTag = languageTag();

	function switchToLanguage(newLanguage: AvailableLanguageTag) {
		const canonicalPath = i18n.route($page.url.pathname);
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
		@apply absolute right-4 top-0 xs:bottom-0 xs:right-0 xs:top-[-24px] sm:bottom-0 sm:right-0 sm:top-0;
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
		@apply relative z-10 flex w-full flex-row gap-3 font-afacad text-lg sm:text-base;
	}
</style>
