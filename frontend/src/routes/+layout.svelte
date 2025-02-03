<script lang="ts">
	import { i18n } from '$lib/i18n';
	import { ParaglideJS } from '@inlang/paraglide-sveltekit';
	import Particles, { particlesInit } from '@tsparticles/svelte';
	import { loadSlim } from '@tsparticles/slim';
	import { fly } from 'svelte/transition';

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

{#key data.url}
	<div class="rest" in:fly={{ y: 10, duration: 500 }}>
		<ParaglideJS {i18n}>
			{@render children?.()}
		</ParaglideJS>
	</div>
{/key}

<style>
	:global(html) {
		@apply bg-[url(/noise2.png)] text-white;
	}

	:global(a) {
		@apply text-blue-500 underline decoration-transparent underline-offset-4;
		@apply transition-colors duration-300 ease-in-out hover:text-blue-300 hover:decoration-blue-500 active:text-blue-200;
	}

	:global(.fake-link) {
		@apply text-blue-500 underline decoration-transparent underline-offset-4;
		@apply transition-colors duration-300 ease-in-out hover:text-blue-300 hover:decoration-blue-500 active:text-blue-200;
	}

	.rest {
		@apply z-[1];
	}

	.linked-particles {
		@apply z-[-1] w-full;
	}
</style>
