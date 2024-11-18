declare module '*.svx' {
	import { SvelteComponent } from 'svelte';
	const component: typeof SvelteComponent;
	export default component;
	export const metadata: Record<string, any>;
}
