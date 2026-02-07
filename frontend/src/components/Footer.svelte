<script lang="ts">
  const current_year = new Date().getFullYear();
  const commit_hash = __GIT_COMMIT_HASH__;
  const repo_url = __REPO_URL__;
  const commit_url = __COMMIT_URL__;
</script>

<p> &copy; h4rl - {current_year}, all meows reserved. [<a href="{commit_url}" target="_blank">{commit_hash}</a>]</p>
<p>Made with <span class="text-magenta-bloom-300">&lt;3</span> in Sweden</p>
<p>Content is licensed under <a href="{repo_url}/LICENSE_CONTENT" target="_blank">CC BY 4.0</a></p>
<p>Code is licensed under <a href="{repo_url}/LICENSE" target="_blank">BSD-3 Clause</a></p>

<style>
  @reference 'appcss';

  p {
    @apply text-center text-shadow-grey-300;
  }
</style>
