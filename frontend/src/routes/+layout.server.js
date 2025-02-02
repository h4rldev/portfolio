import { languageTag } from '$lib/paraglide/runtime';

export const prerender = true;
export const trailingSlash = 'always';
const posts = import.meta.glob('../posts/*.svx');

/**
 * @typedef {Object} Metadata
 * @property {string} title - The title of the blog post
 * @property {(Date|string)} date - The publication date of the blog post
 * @property {*} [customField] - Any additional custom frontmatter field
 */

/**
 * @type { import("./$types").LayoutServerLoad}
 */
export async function load({ depends, url }) {
	// This tells SvelteKit to re-run this load function when the language changes
	depends('paraglide:lang');

	const postPromises = Object.entries(posts).map(async ([path, module]) => {
		return module().then(({ metadata }) => ({
			path: path.replace('.svx', ''),
			title: metadata.title,
			date: metadata.date,
			author: metadata.author
		}));
	});

	return {
		serverLang: `The language on the server is ${languageTag()}`,
		posts: await Promise.all(postPromises),
		url: url.pathname
	};
}
