import { mdsvex } from 'mdsvex';
import adapter from '@sveltejs/adapter-static';
import UnoCSS from '@unocss/svelte-scoped/preprocess';

const prod = process.env.NODE_ENV !== 'development';

/** @type {import('@sveltejs/kit').Config} */
const config = {
	kit: {
		// adapter-auto only supports some environments, see https://svelte.dev/docs/kit/adapter-auto for a list.
		// If your environment is not supported, or you settled on a specific environment, switch out the adapter.
		// See https://svelte.dev/docs/kit/adapters for more information about adapters.
		adapter: adapter({
			pages: 'build',
			assets: 'build',
			fallback: undefined,
			precompress: true,
			strict: true
		}),
		alias: {
			$components: './src/components/',
			$posts: './src/routes/posts/'
		}
	},

	preprocess: [
		mdsvex({
			layout: './src/routes/posts/_layout.svelte',
			smartypants: true,
			extensions: ['.svx']
		}),
		UnoCSS({
			combine: prod
		})
	],
	extensions: ['.svelte', '.svx']
};

export default config;
