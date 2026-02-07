<script lang="ts">
  const { items, placeholder } = $props();

  interface ListBlogItem {
    title: string;
    summary: string;
    author: string;
    time: string | Date;
    tags: string[];
  }

  let query: string = $state("");
  let author = $state("");
  let tag = $state("");
  let [from, to] = $state([0, 0]);

  function fuzzySearch(query: string, item: ListBlogItem): boolean {
    if (!query) return false;
    const q = query.toLowerCase();
    return (
      item.title.toLowerCase().includes(q) ||
      item.summary.toLowerCase().includes(q) ||
      item.tags.some((tag: string) => tag.toLowerCase().includes(q))
    );
  }

  let results = $derived(
    items.filter((item: ListBlogItem) => fuzzySearch(query, item)),
  );
  let authors = $derived([
    ...new Set(items.map((i: ListBlogItem) => i.author)),
  ] as string[]);
  let tags = $derived([
    ...new Set(items.flatMap((i: ListBlogItem) => i.tags)),
  ] as string[]);

  $effect(() => {
    console.log(results);
    console.log(tags);
    console.log(authors);
  });
</script>

<div class="search-body">
  <input type="text" bind:value={query} placeholder={placeholder} />
  <select bind:value={author}>
    <option value="">All Authors</option>
    {#each authors as author}
      <option value={author}>{author}</option>
    {/each}
  </select>
  <select bind:value={tag} multiple>
    <option value="">All Tags</option>
    {#each tags as tag}
      <option value={tag}>#{tag}</option>
    {/each}
  </select>
</div>

