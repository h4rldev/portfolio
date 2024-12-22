<script lang="ts">
	import Glass from '$components/Glass.svelte';

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
	<Glass>
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
			<li class="far-right">
				{#if currentLanguageTag === 'sv'}
					<button class="fake-link" onclick={() => switchToLanguage('en')}>🇬🇧</button>
				{:else}
					<button class="fake-link" onclick={() => switchToLanguage('sv')}>🇸🇪</button>
				{/if}
			</li>
		</ul>
	</Glass>
</nav>

<style>
	.far-right {
		@apply absolute right-5 top-2;
	}

	nav {
		@apply flex flex-row justify-center;
	}

	li:nth-child(1) {
		@apply mx-6;
	}

	a {
		@apply h-[24px];
	}

	ul {
		@apply flex flex-row gap-3 font-nova;
	}
</style>
