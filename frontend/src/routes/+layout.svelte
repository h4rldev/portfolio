<script lang="ts">
	import { i18n } from '$lib/i18n';
	import { ParaglideJS } from '@inlang/paraglide-sveltekit';
	import Particles, { particlesInit } from '@tsparticles/svelte';
	import { loadSlim } from '@tsparticles/slim';

	import '../app.css';
	let { children } = $props();

	let particlesConfig = {
		particles: {
			number: {
				value: 80,
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
				speed: 0.1,
				direction: 'right',
				random: false,
				straight: false,
				outMode: 'out',
				attract: {
					enable: false,
					speed: 1
				},
				bounded: true,
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

<div class="color-background"></div>
<div class="star-particles">
	<Particles id="tsparticles" options={particlesConfig} on:particlesLoaded={onParticlesLoaded} />
</div>
<div class="rest">
	<ParaglideJS {i18n}>
		{@render children()}
	</ParaglideJS>
</div>

<style>
	* {
		@apply text-white;
	}

	.rest {
		@apply z-[0];
	}

	.star-particles {
		@apply z-[-2];
	}

	.color-background {
		@apply absolute left-0 top-0 z-[-1] h-[100%] w-[100%] bg-black;
	}
</style>
