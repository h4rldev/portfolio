<script>
	import { i18n } from '$lib/i18n';
	import { ParaglideJS } from '@inlang/paraglide-sveltekit';
	let { children } = $props();
</script>

<div class="wallpaper-image"></div>
<div class="wallpaper-color"></div>
<div class="rest">
	<ParaglideJS {i18n}>
		{@render children()}
	</ParaglideJS>
</div>

<style>
	.wallpaper-color {
		@apply absolute top-0 left-0 w-[100%] h-[100%] bg-gray-900 z--1 opacity-90;
	}
	.wallpaper-image {
		@apply absolute top-0 left-0 w-[100%] h-[100%] bg-[url(/noise.png)] z--2 opacity-70;
	}
	.rest {
		@apply z-1 relative;
	}
</style>
