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
			},
			screens: {
				'xs': '360px',
				'sm': '640px',
				'md': '768px',
				'lg': '1024px',
				'xl': '1280px',
				'2xl': '1536px'
			},
			animationPlayState: {
				paused: 'paused'
			}
		}
	},

	plugins: [typography]
} satisfies Config;
