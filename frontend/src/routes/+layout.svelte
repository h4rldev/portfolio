<script>
	import { i18n } from '$lib/i18n';
	import { browser } from '$app/environment';
	import { ParaglideJS } from '@inlang/paraglide-sveltekit';
	let { children } = $props();

	if (browser) {
		let dark_theme;
		const stored_theme = localStorage.getItem('theme');

		if (stored_theme) {
			dark_theme = stored_theme === 'dark' ? true : false;
		} else {
			dark_theme = window.matchMedia('(prefers-color-scheme: dark)').matches;
		}

		if (dark_theme == true) {
			document.querySelectorAll('.togglable').forEach((el) => {
				el.classList.add('dark');
				el.classList.remove('light');
			});
		} else {
			document.querySelectorAll('.togglable').forEach((el) => {
				el.classList.add('light');
				el.classList.remove('dark');
			});
		}
	}
</script>

<div class="wallpaper-image"></div>
<div class="wallpaper-color togglable"></div>
<div class="rest">
	<ParaglideJS {i18n}>
		{@render children()}
	</ParaglideJS>
</div>

<style>
	:global(.dark.wallpaper-color) {
		@apply absolute top-0 left-0 w-[100%] h-[100%] bg-gradient-to-br from-gray-900 via-blue-900 to-cyan-900 z--1 opacity-90;
	}

	:global(.light.wallpaper-color) {
		@apply absolute top-0 left-0 w-[100%] h-[100%] bg-gradient-to-br from-gray-400 via-blue-600 to-cyan-700 z--1 opacity-90;
	}

	:global(.light) {
		@apply text-black;
	}

	:global(.dark) {
		@apply text-white;
	}

	.wallpaper-image {
		@apply absolute top-0 left-0 w-[100%] h-[100%] bg-[url(/noise.png)] z--2 opacity-30;
	}
	.rest {
		@apply z-1 relative;
	}
</style>
