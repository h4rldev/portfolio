<script lang="ts">
  import { page } from "$app/stores";
  import FuzzyFinder from "$components/FuzzyFinder.svelte";

  interface ListBlogItem {
    title: string;
    summary?: string;
    author: string;
    time: string | Date;
    tags?: string[];
  }

  const listBlogItems: ListBlogItem[] = [
    {
      title: "Lorem ipsum dolor sit amet",
      author: "h4rl",
      tags: ["lorem", "ipsum", "dolor", "sit", "amet"],
      time: "2023-01-01",
    },
  ];
</script>

<FuzzyFinder items={listBlogItems} placeholder="Search" />
