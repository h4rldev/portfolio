import typography from '@tailwindcss/typography';
import type { Config } from 'tailwindcss';

export default {
	content: ['./src/**/*.{html,js,svelte,ts}'],

	theme: {
		extend: {
			fontFamily: {
				'nova': ['"Nova Mono"', 'monospace'],
				'akshar': ['"Akshar"', 'sans-serif'],
				'afacad': ['"Afacad"', 'sans-serif']
			},
			listStyleType: {
				square: 'square'
			}
		}
	},

	plugins: [typography]
} satisfies Config;
