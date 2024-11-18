<script module>
	/**
	 * @typedef {Object} Metadata
	 * @property {string} [title] - The title of the blog post
	 * @property {(Date|string)} [date] - The publication date of the blog post
	 * @property {*} [customField] - Any additional custom frontmatter field
	 */
</script>

<script>
	let { data } = $props();
</script>

<h1>hi</h1>
<ul>
	{#each data.posts as { path, title, date, author }}
		<li><a href="../{path}">{title} @ {date} by {author}</a></li>
	{/each}
</ul>
