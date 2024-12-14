import typography from '@tailwindcss/typography';
import type { Config } from 'tailwindcss';

export default {
	content: ['./src/**/*.{html,js,svelte,ts}'],

	theme: {
		extend: {
			fontFamily: {
				'nova': ['"Nova Mono"', 'monospace'],
				'akshar': ['"Akshar"', 'sans-serif']
			}
		}
	},

	plugins: [typography]
} satisfies Config;
