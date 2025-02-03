import { languageTag } from '$lib/paraglide/runtime';

export const prerender = true;
export const trailingSlash = 'always';
const posts = import.meta.glob('../posts/*.svx');

export async function load({ depends, url }) {
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
