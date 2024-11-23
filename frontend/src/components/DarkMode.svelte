<script>
	import { browser } from '$app/environment';

	let dark_theme;

	if (browser) {
		const stored_theme = localStorage.getItem('theme');

		if (stored_theme) {
			dark_theme = stored_theme === 'dark' ? true : false;
		} else {
			dark_theme = window.matchMedia('(prefers-color-scheme: dark)').matches;
		}
	}

	let checked = !dark_theme;

	function toggle() {
		if (browser) {
			if (checked === true) {
				localStorage.setItem('theme', 'light');
				document.documentElement.setAttribute('data-theme', 'light');
				document.querySelectorAll('.togglable').forEach((el) => {
					el.classList.add('light');
					el.classList.remove('dark');
				});
			} else {
				document.querySelectorAll('.togglable').forEach((el) => {
					localStorage.setItem('theme', 'dark');
					document.documentElement.setAttribute('data-theme', 'dark');
					el.classList.add('dark');
					el.classList.remove('light');
				});
			}
		}
	}
</script>

<label class="label">
	<input type="checkbox" class="sr-only" bind:checked onchange={toggle} />
	{#if checked}
		<div class="checkbox-on">
			<div class="nipple-on"></div>
		</div>
	{:else}
		<div class="checkbox-off">
			<div class="nipple-off"></div>
		</div>
	{/if}
	<span class="ml-3 text-sm font-medium text-gray-900 dark:text-gray-300"
		>{checked ? 'Light' : 'Dark'}</span
	>
</label>

<style>
	.label {
		@apply inline-flex relative items-center cursor-pointer;
	}

	.checkbox-on {
		@apply w-11 h-6 bg-blue-600 rounded-full relative;
	}

	.checkbox-off {
		@apply w-11 h-6 bg-gray-800 rounded-full relative;
	}

	.nipple-on {
		@apply content-[''] absolute top-[2px] right-[2px] bg-white border-gray-300 border rounded-full h-5 w-5;
	}

	.nipple-off {
		@apply content-[''] absolute top-[2px] left-[2px] bg-white border-gray-300 border rounded-full h-5 w-5;
	}
</style>
