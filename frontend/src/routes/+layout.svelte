<script lang="ts">
	import Particles, { particlesInit } from '@tsparticles/svelte';
	import { loadSlim } from '@tsparticles/slim';
	import { fly } from 'svelte/transition';

	import { page } from '$app/state';
	import { localizeHref, locales } from '$lib/paraglide/runtime';

	import '../app.css';
	let { children, data } = $props();

	let linkedparticles: any = {
		particles: {
			number: {
				value: 120,
				density: {
					enable: true,
					value_area: 800
				}
			},
			color: {
				value: '#ffffff'
			},
			shape: {
				type: 'circle',
				style: {
					animation: 'pulse 1s infinite',
					width: 2,
					height: 2
				}
			},
			opacity: {
				value: 0.5,
				random: true
			},
			tilt: {
				random: true,
				enable: true,
				limit: 15
			},
			move: {
				enable: true,
				speed: 3,
				direction: 'bottom',
				random: false,
				straight: false,
				outMode: 'out',
				attract: {
					enable: false,
					speed: 2
				},
				bounded: false,
				diagonal: false,
				saturation: 180,
				freeze: true,
				shift: 0
			}
		}
	};

	let onParticlesLoaded = (event: any) => {
		const particlesContainer = event.detail.particles;

		// you can use particlesContainer to call all the Container class
		// (from the core library) methods like play, pause, refresh, start, stop
		particlesContainer.start();
	};

	void particlesInit(async (engine) => {
		// call this once per app
		// you can use main to customize the tsParticles instance adding presets or custom shapes
		// this loads the tsparticles package bundle, it's the easiest method for getting everything ready
		// starting from v2 you can add only the features you need reducing the bundle size
		//await loadFull(engine);
		await loadSlim(engine);
	});
</script>

<div class="linked-particles">
	<Particles id="tsparticles" options={linkedparticles} on:particlesLoaded={onParticlesLoaded} />
</div>

<div style="display:none">
	{#each locales as locale}
		<a href={localizeHref(page.url.pathname, { locale })}>{locale}</a>
	{/each}
</div>

{#key data.url}
	<div class="rest" in:fly={{ y: 10, duration: 500 }}>
		{@render children?.()}
	</div>
{/key}

<style>
	:global(body::before) {
		content: '';
		@apply fixed left-0 top-0 h-[100vh] w-[100vw] select-none bg-[url(/haunted-house.jpg)] bg-cover bg-no-repeat;
	}

	:global(body) {
		@apply text-white;
	}

	:global(a) {
		@apply text-cyan-400 underline decoration-transparent underline-offset-4;
		@apply transition-colors duration-300 ease-in-out hover:text-cyan-300 hover:decoration-cyan-500 active:text-cyan-200;
	}

	:global(.fake-link) {
		@apply text-cyan-400 underline decoration-transparent underline-offset-4;
		@apply transition-colors duration-300 ease-in-out hover:text-cyan-300 hover:decoration-cyan-500 active:text-cyan-200;
	}

	.rest {
		@apply z-[1];
	}

	.linked-particles {
		@apply z-[-1] w-full select-none;
	}
</style>
