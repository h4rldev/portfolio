<script lang="ts">
  const { type = "h1", children } = $props();

  const types = ["h1", "h2", "h3", "h4", "h5", "h6"];

  const _id = $props.id();
  const id = _id.substring(1);
</script>

{#if (types.includes(type))}
  <svelte:element this={type}>
  <a id={id} href={`#${id}`} class="anchor">#</a>
  {@render children?.()}
  </svelte:element>
{:else}
  <h1> Unknown Heading Type </h1>
{/if}


<style>
@reference 'appcss';

* {
  @apply font-bold;
}

a {
  @apply no-underline;
}

h1 {
  @apply text-3xl;
}

h2 {
  @apply text-2xl;
}

h3 {
  @apply text-xl;
}

h1,h2,h3 {
  @apply border-b-2 border-shadow-grey-800 mb-2;
}

h4 {
  @apply text-lg;
}

h5 {
  @apply text-base;
}

h6 {
  @apply text-sm;
}

</style>
