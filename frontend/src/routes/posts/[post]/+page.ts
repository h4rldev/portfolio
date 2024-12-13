import { error } from '@sveltejs/kit';

export async function load({ params }: { params: any }) {
	try {
		const post = await import(`../../../posts/${params.post}.svx`);
		return {
			content: post.default,
			meta: { ...post.metadata, slug: params.post }
		};
	} catch (err: any) {
		error(404, err);
	}
}
