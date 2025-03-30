<script lang="ts">
	import { getLocale, localizeHref, setLocale } from '$lib/paraglide/runtime';
	import { m } from '$lib/paraglide/messages.js';

	const currentLanguageTag = getLocale();
</script>

<nav>
	<ul>
		<li><div>h4rl</div></li>
		<li>
			<a href={localizeHref('/')}>{m.home()}</a>
		</li>
		<li>
			<a href={localizeHref('/posts')}>{m.posts()}</a>
		</li>
		<li>
			<a href={localizeHref('/portfolio')}>{m.portfolio()}</a>
		</li>
		<li>
			<a href={localizeHref('/commissions')}>{m.commissions()}</a>
		</li>
		<li class="far-right">
			{#if currentLanguageTag === 'sv'}
				<button class="fake-link" onclick={() => setLocale('en')}>🇬🇧</button>
			{:else}
				<button class="fake-link" onclick={() => setLocale('sv')}>🇸🇪</button>
			{/if}
		</li>
	</ul>
</nav>

<style>
	.far-right {
		@apply absolute xxs:bottom-0 xxs:right-0 xxs:top-[-24px] xs:right-[4px] sm:bottom-0 sm:right-0 sm:top-0 md:right-6 md:top-0;
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
